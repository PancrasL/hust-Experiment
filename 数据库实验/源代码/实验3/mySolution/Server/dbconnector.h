#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include "myStruct.h"
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QDebug>

#define INSERT_SUCCESS 0
#define INSERT_ALREADY_EXIST -1
#define INSERT_DEFEAT -2
namespace MODE {
enum mode{
    QUERY_USER_BY_NAME,
    QUERY_USER_BY_UID,
    QUERY_USER_BY_PHONE,

    QUERY_EP_BY_NAME,
    QUERY_EP_BY_EID,
    QUERY_EP_BY_PHONE,

    QUERY_CAR_BY_CID,
    QUERY_CAR_BY_TYPE,
    QUERY_CAR_BY_STATUS,

    QUERY_RENT_BY_RTID,
    QUERY_RENT_BY_UID,
    QUERY_RENT_BY_EID,
    QUERY_RENT_BY_CID,

    QUERY_BROKEN_BY_BID,
    QUERY_BROKEN_BY_CID,
    QUERY_BROKEN_BY_UID,

    QUERY_RECORD_BY_RID,
    QUERY_RECORD_BY_UID,

    UPDATE_USER_INFO
};
}
class DBConnector : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase database;
    int requestCount;

public:
    DBConnector();
    ~DBConnector();
    bool isOpen();
    void startTransaction();
    void rollBack();
    void commit();
    /*查询相关*/
    QVector<UserInfo> getUserInfo(const QString &value, const int type);
    QVector<EmployeeInfo> getEmployeeInfo(const QString &value, const int type);
    QVector<CarInfo> getCarInfo(const QString &value, const int type);
    QVector<RentInfo> getRentInfo(const QString &value, const int type, const QString &startDate = "1970-01-01", const QString &closingDate = "2200-01-01");
    QVector<BrokenInfo> getBrokenInfo(const QString &value, const int type, const QString &startDate, const QString &closingDate);
    QVector<RecordInfo> getRecordInfo(const QString &value, const int type, const QString &startDate, const QString &closingDate);
    QVector<RentInfo> getBackInfo(const QString &EID, const QString &CID);
    QVector<RentInfo> getPickInfo(const QString &EID, const QString &CID);
    QVector<BrokenInfo> getUnrepairedBroken();
    QVector<Income> getYearStatistics();
    QVector<Income> getSeasonStatistics(int year);
    QVector<Income> getMonthStatistics(int year);
    QVector<Income> getDayStatistics(int year, int month);
    /*更新相关*/
    bool updateUserPassword(const QString &id, const QString &password);
    bool updateUserInfo(const QString &id, const QString &attribute, const QString &value);
    bool updateCarInfo(const QString &id, const QString &attribute, const QString &value);
    bool updateEmployeeInfo(const QString &id, const QString &attribute, const QString &value);
    bool updateRentInfo(const QString &id, const QString &attribute, const QString &value);
    bool updateRecordInfo(const QString &id, const QString &attribute, const QString &value);
    bool updateBrokenInfo(const QString &id, const QString &attribute, const QString &value);
    bool cancelRentOrder(const QString &EID, const QString &RT_ID, const QString &OUT_TIME);
    bool confirmRentOrder(const QString &EID, const QString &RT_ID, const QString &OUT_TIME);
    bool backCarOrder(const QString &EID, const QString &RT_ID, const QString &BACK_TIME);
    /*插入相关*/
    int insertUserInfo(const UserInfo &user);
    int insertCarInfo(const CarInfo &car);
    int insertEmployeeInfo(const EmployeeInfo &employee);
    int insertRentInfo(const RentInfo &rent);
    int insertBrokenInfo(const BrokenInfo &broken);
    int insertRecordInfo(const RecordInfo &record);
};

extern DBConnector dbConnector;
#endif // DBCONNECTOR_H
