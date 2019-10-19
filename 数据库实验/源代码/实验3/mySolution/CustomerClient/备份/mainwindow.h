#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myStruct.h"
class QLabel;
class QTableWidgetItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    UserInfo curUser;           //当前用户的信息
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
    void initUI();
    void initTimer();
    CarInfo splitToCarInfo(const QString &msg);        //从msg中拆分出汽车的各个属性字段
    void setWidgetItemUneditable(QTableWidgetItem *item);   //设置QTableWidgetItem为不可编辑
private slots:
    void handleTimeout();

    void handleGetRentCarInfoReply(bool success, const QVector<QString> &info);

    void on_actionRentCar_triggered();

    void on_actionSheet_triggered();

    void on_actionHistoryOrder_triggered();

signals:
    void tryGetRentCarInfo(const QString &msg);         //请求获取可租车辆信息

    void quitApp();                                     //按下叉号时退出程序
};

#endif // MAINWINDOW_H
