#ifndef SELLMAINWINDOW_H
#define SELLMAINWINDOW_H

#include <QMainWindow>
#include "myStruct.h"
struct RentOrder
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
    QString C_STATUS;           //车辆状态
    QString C_TIMEOUT_PRICE;    //超时价格
};

namespace Ui {
class SellMainWindow;
}

class SellMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SellMainWindow(QWidget *parent = nullptr);
    QString EID;
    ~SellMainWindow();
    void initUI(bool isSellEmployee);
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionPickCar_triggered();

    void on_actionBackCar_triggered();

    void on_actionHistoryOrder_triggered();

    void on_actionRecord_triggered();

    void on_actionBroken_triggered();

    void on_pushBtnFindPickOrder_clicked();

    void on_pushBtnFindBackOrder_clicked();

    void on_pushBtnFindHistoryOrder_clicked();

    void on_pushBtnCancelPickOrder_clicked();

    void on_pushBtnConfirmPickOrder_clicked();

    void on_pushBtnConfirmBackOrder_clicked();

    void on_pushButtonConfirmRecord_clicked();

    void on_pushBtnBrokenCfm_clicked();

    void on_pushBtnRepairCfm_clicked();

    void on_pushBtnFindUnrepaired_clicked();
    //通信槽函数
    void handleGetOrderReply(const QVector<QString> &info);
    void handleCancelOrConfirmOrder(const QVector<QString> &info);
    void handleBackCarReply(const QVector<QString> &info);         //还车操作回复
    void handleBrokenReply(const QVector<QString> &info);       //损坏记录的相关回复
    void handleRecordReply(const QVector<QString> &info);
private:
    Ui::SellMainWindow *ui;
    RentInfo splitToRentInfo(const QString &msg);           //从msg中拆分出订单的各个属性字段
    BrokenInfo splitToBrokenInfo(const QString &msg);       //从msg中拆分出损坏记录的各个字段
    void updateDate();
    void showPickOrder(const QVector<RentInfo> &rentVec);
    void showBackOrder(const QVector<RentInfo> &rentVec);
    void showHistoryOrder(const QVector<RentInfo> &rentVec);
    void showSpareCar(const QVector<QString> &cidVec);
    void showBrokenInfo(const QVector<BrokenInfo> &brokenVec);
signals:
    void getOrder(const QString &msg);                  //获取订单
    void cancelOrConfirmOrder(const QString &msg);      //处理取车订单（取消订单/确认订单）
    void backCar(const QString &msg);                   //归还车辆
    void brokenRecord(const QString &msg);              //损坏记录的相关信息
    void record(const QString &msg);                //违章登记
    void quitApp();                                     //按下叉号时退出程序

};

#endif // SELLMAINWINDOW_H
