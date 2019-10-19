#include "dbconnector.h"
#include "config.h"
#include <QDebug>
#include <QDateTime>
DBConnector dbConnector;           //实例的全局DBConnector对象
DBConnector::DBConnector()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        database = QSqlDatabase::database("qt_sql_default_connection");
    else
        database = QSqlDatabase::addDatabase(Config::dataBase);
    database.setHostName(Config::hostName);
    database.setDatabaseName(Config::dataBaseName);
    database.setUserName(Config::databaseUserName);
    database.setPassword(Config::databasePassword);
    database.open();
}

DBConnector::~DBConnector()
{
    database.close();
    qDebug()<<database<<"is closed";
}

bool DBConnector::isOpen()
{
    return database.isOpen();
}

void DBConnector::startTransaction()
{
    QString sql = "begin";
    QSqlQuery query(database);
    query.exec(sql);
    qDebug()<<sql;
}

void DBConnector::rollBack()
{
    QString sql = "ROLLBACK";
    QSqlQuery query(database);
    query.exec(sql);
    qDebug()<<sql;
}

void DBConnector::commit()
{
    QString sql = "commit";
    QSqlQuery query(database);
    query.exec(sql);
    qDebug()<<sql;
}
QVector<UserInfo> DBConnector::getUserInfo(const QString &value, const int type)
{
    QVector<UserInfo> userVec;
    UserInfo user;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_USER_BY_NAME:
        sql = QString("select * from users where U_NAME like '%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_USER_BY_UID:
        sql = QString("select * from users where U_ID like '%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_USER_BY_PHONE:
        sql = QString("select * from users where U_PHONE_NUM like '%%1%';").arg(value);
        query.exec(sql);
        break;
    default:
        break;
    }
    qDebug()<<sql;
    while(query.next())
    {
        user.U_ID = query.value("U_ID").toString().trimmed();
        user.U_PASSWORD = query.value("U_PASSWORD").toString();
        user.U_PHONE_NUM = query.value("U_PHONE_NUM").toString();
        user.U_NAME = query.value("U_NAME").toString().trimmed();
        user.U_SEX = query.value("U_SEX").toString().trimmed();
        user.U_BIRTHDAY = query.value("U_BIRTHDAY").toDateTime().toString("yyyy-MM-dd");
        user.U_VIP = query.value("U_VIP").toString();
        user.U_CREDIT = query.value("U_CREDIT").toString();
        user.U_BALANCE = query.value("U_BALANCE").toString();
        user.U_REGISTDATE = query.value("U_REGISTDATE").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        user.U_SECRET_QUESTION = query.value("U_SECRET_QUESTION").toString();
        user.U_SECRET_ANSWER = query.value("U_SECRET_ANSWER").toString();
        userVec.push_back(user);
    }
    return userVec;
}

QVector<EmployeeInfo> DBConnector::getEmployeeInfo(const QString &value, const int type)
{
    QVector<EmployeeInfo> employeeVec;
    EmployeeInfo employee;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_EP_BY_NAME:
        sql = QString("select * from employees where E_NAME like '%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_EP_BY_EID:
        sql = QString("select * from employees where E_ID like '%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_EP_BY_PHONE:
        sql = QString("select * from employees where E_PHONE_NUM like '%%1%';").arg(value);
        query.exec(sql);
        break;
    default:
        break;
    }
    qDebug()<<sql;
    while(query.next())
    {
        employee.E_ID = query.value("E_ID").toString().trimmed();
        employee.E_PASSWORD = query.value("E_PASSWORD").toString();
        employee.E_NAME = query.value("E_NAME").toString().trimmed();
        employee.E_SEX = query.value("E_SEX").toString().trimmed();
        employee.E_PHONE_NUM = query.value("E_PHONE_NUM").toString();
        employee.E_ENTRYDATE = query.value("E_ENTRYDATE").toDateTime().toString("yyyy-MM-dd");
        employee.E_TYPE = query.value("E_TYPE").toString().trimmed();
        employeeVec.push_back(employee);
    }
    return employeeVec;
}

QVector<CarInfo> DBConnector::getCarInfo(const QString &value, const int type)
{
    QVector<CarInfo> carVec;
    CarInfo car;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_CAR_BY_CID:
        sql = QString("select * from cars where C_ID like '%%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_CAR_BY_TYPE:
        sql = QString("select * from cars where C_TYPE like '%1%';").arg(value);
        query.exec(sql);
        break;
    case MODE::QUERY_CAR_BY_STATUS:
        sql = QString("select * from cars where C_STATUS like '%1'").arg(value);
        break;
    default:
        break;
    }
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        car.C_ID = query.value("C_ID").toString().trimmed();
        car.C_TYPE = query.value("C_TYPE").toString().trimmed();
        car.C_BRAND = query.value("C_BRAND").toString().trimmed();
        car.C_BUYTIME = query.value("C_BUYTIME").toDateTime().toString("yyyy-MM-dd");
        car.C_DEPOSIT = query.value("C_DEPOSIT").toString();
        car.C_PRICE = query.value("C_PRICE").toString();
        car.C_TIMEOUT_PRICE = query.value("C_TIMEOUT_PRICE").toString();
        car.C_STATUS = query.value("C_STATUS").toString().trimmed();
        carVec.push_back(car);
    }
    return carVec;
}

QVector<RentInfo> DBConnector::getRentInfo(const QString &value, const int type, const QString &startDate, const QString &closingDate)
{
    QVector<RentInfo> rentVec;
    RentInfo rent;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_RENT_BY_RTID:
        sql = QString("select * from rent where RT_ID like '%1%' and RT_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_RENT_BY_UID:
        sql = QString("select * from rent where U_ID like '%%1%' and RT_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_RENT_BY_EID:
        sql = QString("select * from rent where E_ID like '%1%' and RT_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_RENT_BY_CID:
        sql = QString("select * from rent where C_ID like '%%1%' and RT_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    default:
        break;
    }
    qDebug()<<sql;
    while(query.next())
    {
        rent.RT_ID = query.value("RT_ID").toString();
        rent.U_ID = query.value("U_ID").toString();
        rent.E_ID = query.value("E_ID").toString();
        rent.C_ID = query.value("C_ID").toString();
        rent.RT_TIME = query.value("RT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.OUT_TIME = query.value("OUT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.PROGRESS = query.value("PROGRESS").toString();
        rent.BACK_TIME = query.value("BACK_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.EXPENSE = query.value("EXPENSE").toString();
        rent.DEPOSIT = query.value("DEPOSIT").toString();
        rent.PROGRESS = query.value("PROGRESS").toString().trimmed();
        rent.RENTAL_TIME = query.value("RENTAL_TIME").toString().trimmed();
        rentVec.push_back(rent);
    }
    return rentVec;
}

QVector<BrokenInfo> DBConnector::getBrokenInfo(const QString &value, const int type, const QString &startDate, const QString &closingDate)
{
    QVector<BrokenInfo> brokenVec;
    BrokenInfo broken;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_BROKEN_BY_BID:
        sql = QString("select * from broken where B_ID like '%1%' and B_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_BROKEN_BY_CID:
        sql = QString("select * from broken where C_ID like '%1%' and B_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_BROKEN_BY_UID:
        sql = QString("select * from broken where U_ID like '%1%' and B_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    default:
        break;
    }
    qDebug()<<sql;
    while(query.next())
    {
        broken.B_ID = query.value("B_ID").toString();
        broken.C_ID = query.value("C_ID").toString();
        broken.U_ID = query.value("U_ID").toString();
        broken.B_TIME = query.value("B_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        broken.B_SITUATION = query.value("B_SITUATION").toString();
        broken.B_DEGREE = query.value("B_DEGREE").toString();
        broken.B_REPAIRED = query.value("B_REPAIRED").toString();
        broken.B_PRICE = query.value("B_PRICE").toString();
        qDebug()<<broken.B_PRICE;
        brokenVec.push_back(broken);
    }
    return brokenVec;
}

QVector<RecordInfo> DBConnector::getRecordInfo(const QString &value, const int type, const QString &startDate, const QString &closingDate)
{
    QVector<RecordInfo> recordVec;
    RecordInfo record;
    QSqlQuery query(database);
    QString sql;
    switch (type) {
    case MODE::QUERY_RECORD_BY_RID:
        sql = QString("select * from record where R_ID like '%1%' and R_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    case MODE::QUERY_RECORD_BY_UID:
        sql = QString("select * from record where U_ID like '%1%' and R_TIME between '%2' and '%3';")
                .arg(value).arg(startDate).arg(closingDate);
        query.exec(sql);
        break;
    default:
        break;
    }
    qDebug()<<sql;
    while(query.next())
    {
        record.R_ID = query.value("R_ID").toString();
        record.U_ID = query.value("U_ID").toString();
        record.R_SITUATION = query.value("R_SITUATION").toString();
        record.R_FINE = query.value("R_FINE").toString();
        record.R_TIME = query.value("R_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        recordVec.push_back(record);
    }
    return recordVec;
}

QVector<RentInfo> DBConnector::getBackInfo(const QString &EID, const QString &CID)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("select * from rent where C_ID = '%1' and PROGRESS = '在租';").arg(CID);
    QVector<RentInfo> rentVec;
    RentInfo rent;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        rent.RT_ID = query.value("RT_ID").toString();
        rent.U_ID = query.value("U_ID").toString();
        rent.E_ID = query.value("E_ID").toString();
        rent.C_ID = query.value("C_ID").toString();
        rent.RT_TIME = query.value("RT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.OUT_TIME = query.value("OUT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.PROGRESS = query.value("PROGRESS").toString();
        rent.BACK_TIME = query.value("BACK_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.EXPENSE = query.value("EXPENSE").toString();
        rent.DEPOSIT = query.value("DEPOSIT").toString();
        rent.PROGRESS = query.value("PROGRESS").toString().trimmed();
        rent.RENTAL_TIME = query.value("RENTAL_TIME").toString().trimmed();
        rentVec.push_back(rent);
    }
    return rentVec;
}

QVector<RentInfo> DBConnector::getPickInfo(const QString &EID, const QString &CID)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("select * from rent where C_ID = '%1' and PROGRESS = '待取车';").arg(CID);
    QVector<RentInfo> rentVec;
    RentInfo rent;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        rent.RT_ID = query.value("RT_ID").toString();
        rent.U_ID = query.value("U_ID").toString();
        rent.E_ID = query.value("E_ID").toString();
        rent.C_ID = query.value("C_ID").toString();
        rent.RT_TIME = query.value("RT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.OUT_TIME = query.value("OUT_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.PROGRESS = query.value("PROGRESS").toString();
        rent.BACK_TIME = query.value("BACK_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        rent.EXPENSE = query.value("EXPENSE").toString();
        rent.DEPOSIT = query.value("DEPOSIT").toString();
        rent.PROGRESS = query.value("PROGRESS").toString().trimmed();
        rent.RENTAL_TIME = query.value("RENTAL_TIME").toString().trimmed();
        rentVec.push_back(rent);
    }
    return rentVec;
}

QVector<BrokenInfo> DBConnector::getUnrepairedBroken()
{
    QVector<BrokenInfo> brokenVec;
    BrokenInfo broken;
    QSqlQuery query(database);
    QString sql = "select * from broken where B_REPAIRED = '否';";
    qDebug()<<sql;
    query.exec(sql);
    while(query.next())
    {
        broken.B_ID = query.value("B_ID").toString();
        broken.C_ID = query.value("C_ID").toString();
        broken.U_ID = query.value("U_ID").toString();
        broken.B_TIME = query.value("B_TIME").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        broken.B_SITUATION = query.value("B_SITUATION").toString();
        broken.B_DEGREE = query.value("B_DEGREE").toString();
        broken.B_REPAIRED = query.value("B_REPAIRED").toString();
        broken.B_PRICE = query.value("B_PRICE").toString();
        brokenVec.push_back(broken);
    }
    return brokenVec;
}

QVector<Income> DBConnector::getYearStatistics()
{
    QString sql = "SELECT YEAR(BACK_TIME) as m_year, sum(expense) as income "
                  "FROM rent "
                  "WHERE PROGRESS = '已完成' "
                  "GROUP BY YEAR(BACK_TIME) "
                  "ORDER BY YEAR(BACK_TIME) ASC;";
    QSqlQuery query(database);
    QVector<Income> incomeVec;
    Income income;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        income.year = query.value("m_year").toInt();
        income.income = query.value("income").toDouble();

        incomeVec.push_back(income);
    }
    return incomeVec;
}

QVector<Income> DBConnector::getSeasonStatistics(int year)
{

    QString sql = QString("SELECT "
                          "YEAR(BACK_TIME) m_year, "
                          "QUARTER(BACK_TIME) m_season, "
                          "sum(expense) income "
                          "FROM rent "
                          "WHERE YEAR(BACK_TIME) = '%1' "
                          "AND PROGRESS = '已完成' "
                          "GROUP BY "
                          "YEAR(BACK_TIME), "
                          "QUARTER(BACK_TIME) "
                          "ORDER BY "
                          "YEAR(BACK_TIME) ASC, "
                          "QUARTER(BACK_TIME) ASC;").arg(year);
    QSqlQuery query(database);
    QVector<Income> incomeVec(4);
    for(int i = 0;i < incomeVec.size();i++)
    {
        incomeVec[i].season = i+1;
        incomeVec[i].year = year;
    }
    Income income;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        income.year = query.value("m_year").toInt();
        income.season = query.value("m_season").toInt();
        income.income = query.value("income").toDouble();
        incomeVec[income.season - 1] = income;
    }
    return incomeVec;
}

QVector<Income> DBConnector::getMonthStatistics(int year)
{
    QString sql = QString("SELECT YEAR(BACK_TIME) as m_year, "
                          "MONTH(BACK_TIME) as m_month, "
                          "sum(expense) as income "
                          "FROM rent "
                          "WHERE YEAR(BACK_TIME) = '%1' "
                          "AND PROGRESS = '已完成' "
                          "GROUP BY "
                          "YEAR(BACK_TIME), MONTH(BACK_TIME) "
                          "ORDER BY "
                          "YEAR(BACK_TIME) ASC, "
                          "MONTH(BACK_TIME) ASC;").arg(year);
    QSqlQuery query(database);
    QVector<Income> incomeVec(12);
    for(int i=0;i<incomeVec.size();i++)
    {
        incomeVec[i].month = i+1;
        incomeVec[i].date = QString("%1年%2月").arg(year).arg(i+1);
    }
    Income income;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        income.year = query.value("m_year").toInt();
        income.month = query.value("m_month").toInt();
        income.income = query.value("income").toDouble();
        incomeVec[income.month +1].income = income.income;
    }
    return incomeVec;
}

QVector<Income> DBConnector::getDayStatistics(int year, int month)
{
    QString sql = QString("SELECT "
                          "DATE(BACK_TIME) m_date, "
                          "DAY(BACK_TIME) m_day, "
                          "sum(expense) income "
                          "FROM "
                          "rent "
                          "WHERE "
                          "YEAR(BACK_TIME) = '%1' "
                          "AND MONTH(BACK_TIME) = '%2' "
                          "AND PROGRESS = '已完成' "
                          "GROUP BY "
                          "DATE(BACK_TIME), "
                          "DAY(BACK_TIME) "
                          "ORDER BY "
                          "DATE(BACK_TIME) ASC;").arg(year).arg(month);
    QSqlQuery query(database);
    QDate date;
    date.setDate(year, month, 1);
    QVector<Income> incomeVec(date.daysInMonth());
    for(int i=0;i<incomeVec.size();i++)
    {
        incomeVec[i].day = i+1;
        incomeVec[i].date = QString("%1日").arg(i+1);
    }
    Income income;
    query.exec(sql);
    qDebug()<<sql;
    while(query.next())
    {
        income.day = query.value("m_day").toInt();
        income.date = QString("%1日").arg(income.day);
        income.income = query.value("income").toDouble();
        incomeVec[income.day - 1]=income;
    }
    return incomeVec;
}

bool DBConnector::updateUserPassword(const QString &id, const QString &password)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update users set U_PASSWORD = '%1' where U_ID = '%2';").arg(password).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateUserInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update users set %1 = '%2' where U_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateCarInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update cars set %1 = '%2' where C_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateEmployeeInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update employees set %1 = '%2' where E_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateRentInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update rent set %1 = '%2' where RT_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateRecordInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update record set %1 = '%2' where R_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::updateBrokenInfo(const QString &id, const QString &attribute, const QString &value)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("update broken set %1 = '%2' where B_ID = '%3'").arg(attribute).arg(value).arg(id);
    qDebug()<<sql;
    return query.exec(sql);
}

bool DBConnector::cancelRentOrder(const QString &EID, const QString &RT_ID, const QString &OUT_TIME)
{
    QSqlQuery query(database);
    QVector<RentInfo> rentVec = getRentInfo(RT_ID, MODE::QUERY_RENT_BY_RTID);
    if(rentVec.size()!=1)
        return false;
    if(rentVec[0].PROGRESS!="待取车")
        return false;
    QVector<UserInfo> userVec = getUserInfo(rentVec[0].U_ID, MODE::QUERY_USER_BY_UID);
    if(userVec.size()!=1)
        return false;
    //修改订单信息
    updateRentInfo(RT_ID, "E_ID", EID);
    updateRentInfo(RT_ID, "PROGRESS", "已取消");
    updateRentInfo(RT_ID, "OUT_TIME", OUT_TIME);

    updateCarInfo(rentVec[0].C_ID, "C_STATUS", "空闲");
    //退还金额
    double backDeposit = rentVec[0].DEPOSIT.toDouble();
    double backBalance = rentVec[0].EXPENSE.toDouble() + backDeposit;
    double curBalance = userVec[0].U_BALANCE.toDouble();
    curBalance += backBalance;
    updateUserInfo(userVec[0].U_ID, "U_BALANCE", QString::number(curBalance));
    return true;
}

bool DBConnector::confirmRentOrder(const QString &EID, const QString &RT_ID, const QString &OUT_TIME)
{
    QSqlQuery query(database);
    QVector<RentInfo> rentVec = getRentInfo(RT_ID, MODE::QUERY_RENT_BY_RTID);
    if(rentVec.size()!=1)
        return false;
    if(rentVec[0].PROGRESS!="待取车")
        return false;
    QVector<CarInfo> carVec = getCarInfo(rentVec[0].C_ID, MODE::QUERY_CAR_BY_CID);
    if(carVec.size() != 1)
        return false;
    if(carVec[0].C_STATUS != "待取车")
        return false;
    updateRentInfo(RT_ID, "E_ID", EID);
    updateRentInfo(RT_ID, "PROGRESS", "在租");
    updateRentInfo(RT_ID, "OUT_TIME", OUT_TIME);
    updateCarInfo(carVec[0].C_ID, "C_STATUS", "在租");
    return true;
}

int DBConnector::insertUserInfo(const UserInfo &user)
{
    /*首先查询该用户是否已经存在*/
    QSqlQuery query(database);
    QString sql;
    sql = QString("SELECT U_ID FROM USERS WHERE U_ID = '%1';").arg(user.U_ID);
    query.exec(sql);
    if(query.next()==true)                                  //用户已存在
        return INSERT_ALREADY_EXIST;

    /*该用户不存在再执行插入操作*/
    sql = QString("INSERT INTO `USERS` VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12');")
            .arg(user.U_ID)
            .arg(user.U_PASSWORD)
            .arg(user.U_PHONE_NUM)
            .arg(user.U_NAME)
            .arg(user.U_SEX)
            .arg(user.U_BIRTHDAY)
            .arg(user.U_VIP)
            .arg(user.U_CREDIT)
            .arg(user.U_BALANCE)
            .arg(user.U_REGISTDATE)
            .arg(user.U_SECRET_QUESTION)
            .arg(user.U_SECRET_ANSWER);
    if(query.exec(sql)==false)                              //插入失败
        return INSERT_DEFEAT;
    return INSERT_SUCCESS;                                  //插入成功
}

int DBConnector::insertCarInfo(const CarInfo &car)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("SELECT C_ID FROM CARS WHERE C_ID = '%1';").arg(car.C_ID);
    query.exec(sql);
    qDebug()<<sql;
    if(query.next() == true)
        return INSERT_ALREADY_EXIST;
    sql = QString("INSERT INTO `CARS` VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');")
            .arg(car.C_ID)
            .arg(car.C_TYPE)
            .arg(car.C_BRAND)
            .arg(car.C_BUYTIME)
            .arg(car.C_DEPOSIT)
            .arg(car.C_PRICE)
            .arg(car.C_TIMEOUT_PRICE)
            .arg(car.C_STATUS);
    qDebug()<<sql;
    if(query.exec(sql)==false)
        return INSERT_DEFEAT;
    return INSERT_SUCCESS;
}

int DBConnector::insertEmployeeInfo(const EmployeeInfo &employee)
{
    QSqlQuery query(database);
    QString sql;
    sql = QString("SELECT E_ID FROM EMPLOYEES WHERE E_ID = '%1';").arg(employee.E_ID);
    query.exec(sql);
    if(query.next()==true)
        return INSERT_ALREADY_EXIST;
    sql = QString("INSERT INTO `EMPLOYEES` VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7');")
            .arg(employee.E_ID)
            .arg(employee.E_PASSWORD)
            .arg(employee.E_NAME)
            .arg(employee.E_SEX)
            .arg(employee.E_PHONE_NUM)
            .arg(employee.E_ENTRYDATE)
            .arg(employee.E_TYPE);
    if(query.exec(sql)==false)
        return INSERT_DEFEAT;
    return INSERT_SUCCESS;
}

int DBConnector::insertRentInfo(const RentInfo &rent)
{
    CarInfo car = getCarInfo(rent.C_ID, MODE::QUERY_CAR_BY_CID)[0];
    if(car.C_STATUS == "空闲")
    {
        QString sql;
        QSqlQuery query(database);
        bool success = true;
        /*开启事务*/
        sql = "begin;";
        success &=query.exec(sql);
        /*插入租车记录*/
        sql=(QString("INSERT INTO `rent` VALUES ('%1', '%2', NULL, '%3', '%4', NULL, NULL, %5, %6, '待取车', %7);")
             .arg(rent.RT_ID).arg(rent.U_ID).arg(rent.C_ID).arg(rent.RT_TIME).arg(rent.EXPENSE).arg(rent.DEPOSIT).arg(rent.RENTAL_TIME));
        success &=query.exec(sql);
        qDebug()<<sql;
        /*修改用户余额*/
        double totalPrice = rent.EXPENSE.toDouble() + rent.DEPOSIT.toDouble();
        double balance = getUserInfo(rent.U_ID, MODE::QUERY_USER_BY_UID)[0].U_BALANCE.toDouble();
        sql=(QString("update users set U_BALANCE = %1 where U_ID = '%2';").arg(balance - totalPrice).arg(rent.U_ID));
        success &= query.exec(sql);
        qDebug()<<sql;
        /*修改车辆状态*/
        sql=(QString("update cars set C_STATUS = '%1' where C_ID = '%2' and C_STATUS = '空闲';").arg("待取车").arg(rent.C_ID));
        success &= query.exec(sql);
        qDebug()<<sql;
        /*执行事务*/
        if(success)
            query.exec("commit;");
        else query.exec("ROLLBACK;");
        if(success)
            return INSERT_SUCCESS;
        else return INSERT_DEFEAT;
    }
    else return INSERT_ALREADY_EXIST;
}

int DBConnector::insertBrokenInfo(const BrokenInfo &broken)
{
    QSqlQuery query(database);
    QString sql;
    QVector<CarInfo> carVec = getCarInfo(broken.C_ID, MODE::QUERY_CAR_BY_CID);
    if(carVec.size() == 1 && carVec[0].C_STATUS == "损坏")
    {
        return INSERT_ALREADY_EXIST;
    }
    else if(carVec.size() == 1 &&carVec[0].C_STATUS == "空闲")
    {
        updateCarInfo(broken.C_ID, "C_STATUS", "损坏");
        sql = QString("INSERT INTO `broken` VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');")
                .arg(broken.B_ID)
                .arg(broken.C_ID)
                .arg(broken.U_ID)
                .arg(broken.B_TIME)
                .arg(broken.B_SITUATION)
                .arg(broken.B_DEGREE)
                .arg(broken.B_REPAIRED)
                .arg(broken.B_PRICE);
        query.exec(sql);
        qDebug()<<sql;
        return INSERT_SUCCESS;
    }
    return INSERT_DEFEAT;
}

int DBConnector::insertRecordInfo(const RecordInfo &record)
{
    QSqlQuery query(database);
    QString sql = QString("INSERT INTO `record` VALUES ('%1', '%2', '%3', '%4', '%5');")
            .arg(record.R_ID)
            .arg(record.U_ID)
            .arg(record.R_SITUATION)
            .arg(record.R_FINE)
            .arg(record.R_TIME);
    if(query.exec(sql))
        return INSERT_SUCCESS;
    else return INSERT_DEFEAT;
}
