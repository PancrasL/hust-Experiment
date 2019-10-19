#ifndef STRUCT_H
#define STRUCT_H
#include <QString>

struct UserInfo
{
    QString U_ID;               //身份证号码
    QString U_PASSWORD;         //登录密码
    QString U_PHONE_NUM;        //用户电话
    QString U_NAME;             //用户姓名
    QString U_SEX;              //用户性别
    QString U_BIRTHDAY;         //用户生日
    QString U_VIP;              //会员等级
    QString U_CREDIT;             //信誉等级
    QString U_BALANCE;          //账户余额
    QString U_REGISTDATE;       //注册日期
    QString U_SECRET_QUESTION;  //密保问题
    QString U_SECRET_ANSWER;    //密保答案

};

struct EmployeeInfo
{
    QString E_ID;               //员工编号
    QString E_PASSWORD;         //登陆密码
    QString E_NAME;             //员工姓名
    QString E_SEX;              //员工性别
    QString E_PHONE_NUM;        //电话号码
    QString E_ENTRYDATE;        //入职日期
    QString E_TYPE;             //员工类别
};

struct CarInfo
{
    QString C_ID;               //车牌号
    QString C_TYPE;             //车辆型号
    QString C_BRAND;            //车辆品牌
    QString C_BUYTIME;          //购车日期
    QString C_DEPOSIT;          //车辆押金
    QString C_PRICE;            //出租价格/日
    QString C_TIMEOUT_PRICE;    //超时价格/日
    QString C_STATUS;           //车辆状态
};

struct BrokenInfo
{
    QString B_ID;               //损坏编号
    QString C_ID;               //车牌号
    QString U_ID;               //身份证号码
    QString B_TIME;             //损坏日期
    QString B_SITUATION;        //损坏概况
    QString B_DEGREE;           //损坏程度
    QString B_REPAIRED;         //是否已经修复
    QString B_PRICE;            //维修价格
};

struct RecordInfo
{
    QString R_ID;               //罚单编号
    QString U_ID;               //身份证号码
    QString R_SITUATION;        //违章情况
    QString R_FINE;             //违规罚金
    QString R_TIME;             //违规日期
};

struct RentInfo
{
    QString RT_ID;              //订单编号
    QString U_ID;               //身份证号码
    QString E_ID;               //员工编号
    QString C_ID;               //车牌号
    QString RT_TIME;            //订单日期
    QString OUT_TIME;           //出库日期
    QString BACK_TIME;          //还车日期
    QString EXPENSE;            //订单费用
    QString DEPOSIT;            //实缴押金
    QString PROGRESS;           //订单状态
    QString RENTAL_TIME;        //租车时长(日）
};

struct Income
{
    QString date;               //date
    int year;
    int month;
    int season;
    int week;
    int day;
    double income;
};

#endif // STRUCT_H
