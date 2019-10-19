#include "uclientservice.h"
#include "trans_protocol.h"
#include "dbconnector.h"
#include "mainwindow.h"
#include <QVector>
#include <QDateTime>
extern DBConnector dbConnector;

static QVector<double> DEPOSIT_VIP_DISCOUNT = {1.0, 0.8, 0.6, 0.4, 0.2, 0};      //根据vip等级决定押金费用，最高vip5免押金
static QVector<double> PRICE_VIP_DISCOUNT = {1.0, 0.95, 0.90, 0.85, 0.80, 0.75}; //根据vip等级决定收费费用，最高vip5打0.75折
static constexpr int CREDIT_MIN_THRESHOLD = 60;                                     //信誉积分的最低阈值，低于此值不可租车
QString UClient::debug()
{
    return "debug";
}
QString UClient::handleLogin(const QVector<QString> &info, QString &userId, QString &userName)
{
    /*取出用户输入的账号密码*/
    QString id = info[0];
    QString password = info[1];

    /*从数据库中获取该账户的密码*/
    QVector<UserInfo>vec = dbConnector.getUserInfo(id, MODE::QUERY_USER_BY_UID);

    /*判断*/
    QString reply;
    if(vec.isEmpty())                            //未找到账号
    {
        reply.append("no account");
        MainWindow::addLog(id, QString("用户账号不存在"));
    }
    else if(vec[0].U_PASSWORD == password)       //匹配
    {
        userId = id;
        userName = vec[0].U_NAME;
        reply.append("login success\n");
        MainWindow::addLog(userId+"_"+userName,QString("登录成功"));
    }
    else                                         //不匹配
    {
        reply.append("login defeat");
        MainWindow::addLog(userId+"_"+userName,QString("错误密码：%1").arg(password));
    }
    return reply;
}

QString UClient::handleRegist(const QVector<QString> &info)
{
    QString reply;
    /*取出用户注册信息*/
    UserInfo user;
    user.U_ID = info[0];
    user.U_PASSWORD = info[1];
    user.U_PHONE_NUM = info[2];
    user.U_NAME = info[3];
    user.U_SEX = info[4];
    user.U_BIRTHDAY = info[5];
    user.U_VIP = info[6];
    user.U_CREDIT = info[7];
    user.U_BALANCE = info[8];
    user.U_REGISTDATE = info[9];
    user.U_SECRET_QUESTION = info[10];
    user.U_SECRET_ANSWER = info[11];

    /*向数据库库中添加一条记录*/
    int status = dbConnector.insertUserInfo(user);
    if(status == INSERT_SUCCESS)     //插入成功
    {
        reply.append("regist success");
        MainWindow::addLog("server", QString("用户%1注册成功").arg(user.U_ID));
    }
    else if(status == INSERT_ALREADY_EXIST){
        reply.append("account already exist");
    }
    else
    {
        reply.append("regist defeat");
    }
    return reply;
}

QString UClient::handleGetQuestion(const QVector<QString> &info)
{
    QString id = info[0];
    QString phone = info[1];
    QString name = info[2];
    UserInfo user;
    QVector<UserInfo>vec = dbConnector.getUserInfo(id, MODE::QUERY_USER_BY_UID);
    if(vec.size()==1)
    {
        user = vec[0];
        if(user.U_NAME == name && user.U_PHONE_NUM == phone)
            return "get question success\n" + user.U_SECRET_QUESTION;
    }
    return "get question defeat\nno msg";
}

QString UClient::handleFindPwd(const QVector<QString> &info)
{
    QString id = info[0];
    QString answer = info[1];
    QString password = info[2];
    UserInfo user;
    QVector<UserInfo>vec = dbConnector.getUserInfo(id, MODE::QUERY_USER_BY_UID);
    if(vec.size()==1)
    {
        user = vec[0];
        if(answer == user.U_SECRET_ANSWER)
        {
            if(dbConnector.updateUserPassword(id, password) == true)
                return "find password success";
        }
    }
    return "find password defeat";
}

QString UClient::handleGetRentCarInfo(const QVector<QString> &info)
{
    QString reply;
    QString id = info[0];
    UserInfo user;
    QVector<UserInfo> userVec;
    QVector<CarInfo> carVec;

    userVec = dbConnector.getUserInfo(id, MODE::QUERY_USER_BY_UID);
    if(userVec.size() == 1)
    {
        if(userVec[0].U_CREDIT.toInt() < CREDIT_MIN_THRESHOLD)      //信誉积分不足
            reply = "credit too low";
        else
        {
            reply = "rent car info\n";
            carVec = dbConnector.getCarInfo("空闲", MODE::QUERY_CAR_BY_STATUS);
            for(auto car:carVec)
            {
                reply.append(QString("%1#%2#%3#%4#%5#%6#%7\n")
                             .arg(car.C_ID)
                             .arg(car.C_TYPE)
                             .arg(car.C_BRAND)
                             .arg(car.C_DEPOSIT)
                             .arg(car.C_PRICE)
                             .arg(car.C_TIMEOUT_PRICE)
                             .arg(car.C_STATUS));
            }
        }
    }
    return reply;
}

QString UClient::handleGetUserInfo(const QString &uid)
{
    QString reply;
    QVector<UserInfo> userVec;

    userVec = dbConnector.getUserInfo(uid, MODE::QUERY_USER_BY_UID);
    if(userVec.size() == 1)
    {
        reply.append(userVec[0].U_ID);
        reply.push_back('\n');
        reply.append(userVec[0].U_NAME);
        reply.push_back('\n');
        reply.append(userVec[0].U_CREDIT);
        reply.push_back('\n');
        reply.append(userVec[0].U_BALANCE);
    }
    return reply;
}

void UClient::setVipDepositDiscount(const QVector<double> &vec)
{
    DEPOSIT_VIP_DISCOUNT = vec;
}

void UClient::setVipPriceDiscount(const QVector<double> &vec)
{
    PRICE_VIP_DISCOUNT = vec;
}

QVector<double> UClient::getVipDepositDiscount()
{
    return DEPOSIT_VIP_DISCOUNT;
}

QVector<double> UClient::getVipPriceDiscount()
{
    return PRICE_VIP_DISCOUNT;
}

QString UClient::handleRentCar(const QVector<QString> &info)
{
    int rentalDay = info[2].toInt();
    QVector<UserInfo> userVec = dbConnector.getUserInfo(info[0], MODE::QUERY_USER_BY_UID);
    if(userVec.size() != 1)
        return "";
    QVector<CarInfo> carVec = dbConnector.getCarInfo(info[1], MODE::QUERY_CAR_BY_CID);
    if(carVec.size()!= 1)
        return "";
    UserInfo user =userVec[0];
    CarInfo car =carVec[0];
    double deposit = car.C_DEPOSIT.toDouble();
    double pricePerDay = car.C_PRICE.toDouble();
    int vip = user.U_VIP.toInt();

    double price = pricePerDay * rentalDay;
    double realDeposit = deposit * DEPOSIT_VIP_DISCOUNT[vip];
    double realPrice = price * PRICE_VIP_DISCOUNT[vip];
    QString reply = QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8")
            .arg(car.C_ID).arg(car.C_TYPE).arg(car.C_BRAND).arg(deposit).arg(price).arg(realDeposit).arg(realPrice).arg(rentalDay);
    return reply;
}


QString UClient::generateRentOrder(const QVector<QString> &info)
{
    RentInfo rent;
    rent.RT_ID = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz").append("01");//订单号：时间+01
    rent.U_ID = info[0];
    rent.C_ID = info[1];
    rent.RT_TIME = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    rent.DEPOSIT = info[2];
    rent.EXPENSE = info[3];
    rent.PROGRESS = "在租";
    rent.RENTAL_TIME = info[4];
    QVector<UserInfo> userVec = dbConnector.getUserInfo(info[0], MODE::QUERY_USER_BY_UID);
    if(userVec.size() != 1)
        return "";
    UserInfo user = userVec[0];
    if(user.U_BALANCE.toDouble() < rent.EXPENSE.toDouble()+rent.DEPOSIT.toDouble())
    {
        return "balance is not enough";
    }
    else if(user.U_CREDIT.toInt() < CREDIT_MIN_THRESHOLD)
    {
        return "credit too low";
    }
    int status = dbConnector.insertRentInfo(rent);
    if(status == INSERT_ALREADY_EXIST)
        return "car is already rented";
    else if(status == INSERT_SUCCESS)
        return  "rent car success";
    else return "rent car defeat";
}

QString UClient::getHistoryOrder(const QVector<QString> &info)
{
    if(dbConnector.getUserInfo(info[0], MODE::QUERY_USER_BY_UID).size()!=0)
    {
        QVector<RentInfo> rentVec = dbConnector.getRentInfo(info[0], MODE::QUERY_RENT_BY_UID, info[1], info[2]);
        QString reply = "get history order success\n";
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
    return "";
}
