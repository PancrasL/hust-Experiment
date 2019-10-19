#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myStruct.h"
#include "rentdialog.h"
class QLabel;
class QTableWidgetItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    UserInfo user;           //当前用户的信息
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showWelcome();
    void updateUI();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;

    QLabel *curTimeLabel;       //显示当前时间
    QVector<CarInfo> carVec;    //从服务器获取的可租车辆信息
    RentDialog rentdlg;         //租车对话框
    void initUI();
    void initTimer();
    CarInfo splitToCarInfo(const QString &msg);             //从msg中拆分出汽车的各个属性字段
    RentInfo splitToRentInfo(const QString &msg);           //从msg中拆分出订单的各个属性字段
    void setWidgetItemUneditable(QTableWidgetItem *item);   //设置QTableWidgetItem为不可编辑
private slots:
    void handleTimeout();

    void handleGetRentCarInfoReply(bool success, const QVector<QString> &info);

    void handleGetUserInfoReply(const QVector<QString> &info);

    void handleRentCarReply(const QVector<QString> &info);

    void handleConfirmRentCarReply(const QString &msg);

    void handleGetHistoryOrderReply(const QVector<QString> &info);

    void on_actionUserInfo_triggered();

    void on_actionRentCar_triggered();

    void on_actionSheet_triggered();

    void on_actionHistoryOrder_triggered();

    void on_pushBtnrentCar_clicked();

    void on_pushButton_clicked();

signals:
    void tryGetRentCarInfo(const QString &msg);         //请求获取可租车辆信息

    void tryGetUserInfo(const QString &uid);            //请求获取用户信息(姓名、账户余额、信誉积分)

    void tryGetRentCarPrice(const QString &uid);        //获取租车费用

    void tryRentCar(const QString &msg);                //请求租用车辆

    void confirmRentCar(const QString &msg);            //确认租用车辆

    void getHistoryOrder(const QString &msg);           //获取历史订单

    void quitApp();                                     //按下叉号时退出程序
};

#endif // MAINWINDOW_H
