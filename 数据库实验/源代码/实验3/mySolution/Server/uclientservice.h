#ifndef UCLIENTSERVICE_H
#define UCLIENTSERVICE_H
#include <QString>
#include <QVector>
namespace UClient {
QString debug();
/*用户登录相关*/
QString handleLogin(const QVector<QString> &info, QString &userId, QString &userName);//判断用户是否登录成功，如果成功则将账号和姓名存放到userId和userName中
QString handleRegist(const QVector<QString> &info);                                   //处理用户注册账号的请求
QString handleGetQuestion(const QVector<QString> &info);                              //处理用户获取密保问题的请求
QString handleFindPwd(const QVector<QString> &info);                                  //处理用户找回密码的请求

/*用户服务相关*/
QString handleGetRentCarInfo(const QVector<QString> &info);
QString handleGetUserInfo(const QString &uid);
QString handleRentCar(const QVector<QString> &info);

QString generateRentOrder(const QVector<QString> &info);
QString getHistoryOrder(const QVector<QString> &info);
/*会员服务相关*/
void setVipDepositDiscount(const QVector<double> &vec);                 //设置会员押金折扣
void setVipPriceDiscount(const QVector<double> &vec);                   //设置会员租车价格折扣
QVector<double> getVipDepositDiscount();
QVector<double> getVipPriceDiscount();
}
#endif // UCLIENTSERVICE_H
