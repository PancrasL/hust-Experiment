#ifndef ECLIENTSERVICE_H
#define ECLIENTSERVICE_H
#include <QVector>
#include <QString>
namespace EClient {
QString handleELogin(const QVector<QString> &info, QString &userId, QString &userName);
QString handleGetOrder(const QVector<QString> &info);
QString handleRentOrder(bool isCancel, const QString &EID, const QString &RT_ID, const QString &OUT_TIME);
QString handleBackCar(const QString &EID, const QString &RT_ID, const QString &BACK_TIME);
QString handleCclOrCfm(const QString &cmd, const QString &EID, const QString &OUT_TIME, const QString &RT_ID);
QString handleBroken(const QVector<QString> &info);
QString handleRecord(const QVector<QString> &info);
}

#endif // ECLIENTSERVICE_H
