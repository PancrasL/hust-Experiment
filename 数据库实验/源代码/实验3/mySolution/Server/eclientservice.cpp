#include "eclientservice.h"
#include "dbconnector.h"
#include "mainwindow.h"
#include <QDateTime>
extern DBConnector dbConnector;
QString EClient::handleELogin(const QVector<QString> &info, QString &userId, QString &userName)
{
    /*取出用户输入的账号密码*/
    QString id = info[0];
    QString password = info[1];

    /*从数据库中获取该账户的密码*/
    QVector<EmployeeInfo> vec = dbConnector.getEmployeeInfo(id, MODE::QUERY_EP_BY_EID);

    /*判断*/
    QString reply;
    if(vec.isEmpty())                            //未找到账号
    {
        reply.append("no account\nno account");
        MainWindow::addLog(id, QString("员工账号不存在"));
    }
    else if(vec[0].E_PASSWORD == password)       //匹配
    {
        userId = id;
        userName = vec[0].E_NAME;
        reply.append("login success\n");
        if(vec[0].E_TYPE == "普通")
            reply.append("level0");
        else if(vec[0].E_TYPE == "高级")
            reply.append("level1");
        MainWindow::addLog(userId+"_"+userName,QString("登录成功"));
    }
    else                                         //不匹配
    {
        reply.append("login defeat\nlogin defeat");
        MainWindow::addLog(vec[0].E_ID+"_"+vec[0].E_NAME,QString("错误密码：%1").arg(password));
    }
    return reply;
}

QString EClient::handleRentOrder(bool isCancel, const QString &EID, const QString &RT_ID, const QString &OUT_TIME)
{
    QString reply;
    if(isCancel)    //取消订单
    {
        bool status = dbConnector.cancelRentOrder(EID, RT_ID, OUT_TIME);
        reply = status?"success":"defeat";
    }
    else {          //确认订单
        bool status = dbConnector.confirmRentOrder(EID, RT_ID, OUT_TIME);
        reply = status?"success":"defeat";
    }
    return reply;
}

QString EClient::handleBackCar(const QString &EID, const QString &RT_ID, const QString &BACK_TIME)
{

    QString reply;
    /*开始事务*/
    dbConnector.startTransaction();
    /*获取相关信息*/
    QVector<RentInfo> rent = dbConnector.getRentInfo(RT_ID, MODE::QUERY_RENT_BY_RTID);
    if(rent.size() !=1) return reply;
    QVector<UserInfo> user = dbConnector.getUserInfo(rent[0].U_ID, MODE::QUERY_USER_BY_UID);
    if(user.size() !=1) return reply;
    QVector<CarInfo> car = dbConnector.getCarInfo(rent[0].C_ID, MODE::QUERY_CAR_BY_CID);
    if(car.size() != 1) return reply;
    if(rent[0].PROGRESS != "在租")
        return "订单已完成";
    /*计算租车时长及补交或退款金额*/
    QDateTime pickTime = QDateTime::fromString(rent[0].OUT_TIME, "yyyy-MM-dd hh:mm:ss");
    QDateTime backTime = QDateTime::fromString(BACK_TIME, "yyyy/M/d H:mm");
    auto interval = pickTime.daysTo(backTime) + 1;                                  //实际租车时长，不足24小时按照24小时算
    int rentalTime = rent[0].RENTAL_TIME.toInt();                                   //预计租车时长（已缴费）
    double balance = user[0].U_BALANCE.toDouble();                                  //用户的账户余额
    double deposit = rent[0].DEPOSIT.toDouble();                                    //实缴押金
    double supplement;                                                              //小于0为补交金额，大于0为退款金额
    double realPay;                                                                 //用户实缴金额
    if(interval > rentalTime)//超时
    {
        supplement = -car[0].C_TIMEOUT_PRICE.toDouble()*(interval - rentalTime);//计算出补交金额
        realPay = rent[0].EXPENSE.toDouble() - supplement;
    }
    else                     //退款
    {
        supplement = (1 - interval*1.0/rentalTime)*rent[0].EXPENSE.toDouble();
        realPay = rent[0].EXPENSE.toDouble() - supplement;
    }
    double newBalance = supplement+balance+deposit;                                 //完成订单后的用户余额
    if(newBalance < 0)//余额不足
    {
        reply = "balance is not enough\n";
        reply.append(QString("预计租车时长/日：%1\n").arg(rentalTime));
        reply.append(QString("实际租车时长/日：%1\n").arg(interval));
        reply.append(QString("超时时长/日：%1\n").arg(interval - rentalTime));
        reply.append(QString("超时价格/日：%1\n").arg(car[0].C_TIMEOUT_PRICE));
        reply.append(QString("补交金额/元：%1\n").arg(-supplement));
        reply.append(QString("当前账户余额/元：%1\n").arg(user[0].U_BALANCE));
    }
    else
    {
        int credit = 0;
        int ascend = 0;
        if(interval > rentalTime)//超时扣除信誉积分
        {
            credit = -1 * static_cast<int>((interval - rentalTime) + 1);//超时扣除1积分，此外每超时1天多扣1信誉积分
        }
        else
            ascend = static_cast<int>(realPay/500 + 1);//每租一次车增加1积分，此外每消费500元增加1分
        credit +=ascend;
        bool status = true;
        //修改用户余额
        status &=dbConnector.updateUserInfo(user[0].U_ID, "U_BALANCE", QString::number(newBalance));
        //修改用户信誉分
        status &=dbConnector.updateUserInfo(user[0].U_ID, "U_CREDIT",QString::number(user[0].U_CREDIT.toInt() + credit));
        //修改车辆状态
        status &=dbConnector.updateCarInfo(car[0].C_ID, "C_STATUS", "空闲");
        //修改订单状态
        status &=dbConnector.updateRentInfo(rent[0].RT_ID, "PROGRESS", "已完成");
        status &=dbConnector.updateRentInfo(rent[0].RT_ID, "BACK_TIME", BACK_TIME);
        status &=dbConnector.updateRentInfo(rent[0].RT_ID, "EXPENSE", QString::number(realPay));
        status &=dbConnector.updateRentInfo(rent[0].RT_ID, "RENTAL_TIME", QString::number(interval));
        if(status)
        {
            //提交事务
            dbConnector.commit();
            reply = "back car success\n";
            reply.append(QString("实际租车时长/日：%1\n").arg(interval));
            reply.append(QString("实缴金额/元：%1\n").arg(realPay));
            reply.append(QString("信誉积分变化：%1\n").arg(credit));
            if(supplement > 0)
                reply.append(QString("退款金额/元：%1\n").arg(supplement));
            else reply.append(QString("超时补交金额/元：%1\n").arg(-supplement));
            reply.append(QString("退回押金/元：%1\n").arg(deposit));
            reply.append(QString("用户当前账户余额/元：%1\n").arg(newBalance));
        }
        else
        {
            //撤回事务
            dbConnector.rollBack();
            reply = "back car defeat";
        }
    }
    return reply;
}

QString EClient::handleGetOrder(const QVector<QString> &info)
{
    QVector<RentInfo> rentVec;
    QString reply;
    if(info[0] == "find pick order")
    {
        if(info.size()!=3) return "";
        rentVec = dbConnector.getPickInfo(info[1], info[2]);
        reply = "pick order reply\n";
    }
    else if(info[0] == "find back order")
    {
        rentVec = dbConnector.getBackInfo(info[1], info[2]);
        reply = "back order reply\n";
    }
    else if(info[0] == "find history order")
    {
        if(info.size()!=4) return "";
        rentVec = dbConnector.getRentInfo(info[1], MODE::QUERY_RENT_BY_EID, info[2], info[3]);
        reply = "history order reply\n";
    }

    for(auto element:rentVec)
    {
        reply.append(QString("%1#%2#%3#%4#%5#%6#%7#%8#%9#%10#%11\n")
                     .arg(element.RT_ID)
                     .arg(element.U_ID)
                     .arg(element.E_ID)
                     .arg(element.C_ID)
                     .arg(element.RT_TIME)
                     .arg(element.OUT_TIME)
                     .arg(element.BACK_TIME)
                     .arg(element.EXPENSE)
                     .arg(element.DEPOSIT)
                     .arg(element.PROGRESS)
                     .arg(element.RENTAL_TIME)
                     );
    }
    return reply;
}

QString EClient::handleCclOrCfm(const QString &cmd, const QString &EID, const QString &OUT_TIME, const QString &RT_ID)
{
    QString reply;
    if(cmd == "cancel order")    //取消订单
    {
        bool status = dbConnector.cancelRentOrder(EID, RT_ID, OUT_TIME);
        reply = "cancel order reply\n";
        reply.append(status?"success":"defeat");
    }
    else if(cmd == "confirm order"){          //确认订单
        bool status = dbConnector.confirmRentOrder(EID, RT_ID, OUT_TIME);
        reply = "confirm order reply\n";
        reply.append(status?"success":"defeat");
    }
    return reply;
}

QString EClient::handleBroken(const QVector<QString> &info)
{
    QString reply;
    if(info[0] == "get spare car")
    {
        reply = "get spare car reply\n";
        QVector<CarInfo> carVec;
        carVec = dbConnector.getCarInfo("空闲", MODE::QUERY_CAR_BY_STATUS);
        for(int i=0;i<carVec.size();i++)
        {
            reply.append(carVec[i].C_ID);
            reply.push_back('\n');
        }
    }
    else if(info[0] == "regist broken")
    {
        reply = "regist broken reply\n";
        BrokenInfo broken;
        broken.B_ID = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz").append("02");//损坏编号：时间+02;
        broken.C_ID = info[1];
        broken.U_ID = info[2];
        broken.B_TIME = info[3];
        broken.B_SITUATION = info[4];
        broken.B_DEGREE = info[5];
        broken.B_REPAIRED = "否";
        broken.B_PRICE = info[6];
        QVector<UserInfo> userVec = dbConnector.getUserInfo(broken.U_ID, MODE::QUERY_USER_BY_UID);
        QVector<CarInfo> carVec = dbConnector.getCarInfo(broken.C_ID, MODE::QUERY_CAR_BY_CID);

        if(userVec.size() != 1)
            reply.append("用户不存在");
        else if(carVec.size() != 1)
            reply.append("车辆不存在");
        else if(carVec[0].C_STATUS == "在租")
            reply.append("请先归还车辆后再登记");
        else if(carVec[0].C_STATUS == "损坏")
            reply.append("损坏记录已经插入");
        else
        {
            int status = dbConnector.insertBrokenInfo(broken);
            if(status == INSERT_DEFEAT)
            {
                reply.append("损坏记录插入失败");
            }
            else if(status == INSERT_ALREADY_EXIST)
            {
                reply.append("损坏记录已经插入");
            }
            else if(status == INSERT_SUCCESS)
            {
                reply.append("损坏记录插入成功");
            }
        }

    }
    else if(info[0] == "get broken info")
    {
        reply = "get broken info reply\n";
        QVector<BrokenInfo> brokenVec = dbConnector.getUnrepairedBroken();
        for(int i=0;i<brokenVec.size();i++)
        {
            reply.append(QString("%1#%2#%3#%4#%5#%6#%7#%8")
                         .arg(brokenVec[i].B_ID)
                         .arg(brokenVec[i].C_ID)
                         .arg(brokenVec[i].U_ID)
                         .arg(brokenVec[i].B_TIME)
                         .arg(brokenVec[i].B_SITUATION)
                         .arg(brokenVec[i].B_DEGREE)
                         .arg(brokenVec[i].B_REPAIRED)
                         .arg(brokenVec[i].B_PRICE));
            reply.push_back('\n');
        }
    }
    else if(info[0] == "repair car")
    {
        reply = "repair car reply\n";
        if(dbConnector.updateBrokenInfo(info[1], "B_REPAIRED", "是"))
        {
            dbConnector.updateCarInfo(info[2], "C_STATUS", "空闲");
            reply.append("更新成功");
        }
        else reply.append("更新失败");
    }
    return reply;
}

QString EClient::handleRecord(const QVector<QString> &info)
{
    if(info[0] != "record")
        return "error";
    QString reply;
    reply = "record reply\n";
    RecordInfo record;
    record.U_ID = info[1];
    record.R_SITUATION = info[2];
    record.R_FINE = info[3];
    record.R_TIME = info[4];
    record.R_ID = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz").append("03");//损坏编号：时间+03;
    int status = dbConnector.insertRecordInfo(record);
    if(status == INSERT_SUCCESS)
        reply.append("违章记录插入成功");
    else
        reply.append("违章记录插入失败");
    return reply;
}
