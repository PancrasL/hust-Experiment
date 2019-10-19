#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dbconnector.h"
#include "addnewcar.h"
#include "addnewemployee.h"
#include "vipdiscountdialog.h"
#include "statisticswindow.h"
#include <QMainWindow>
class QTcpServer;
class QTcpSocket;
class QTableWidget;
class QTableWidgetItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    static void addLog(const QString &obj, const QString &msg);     //添加日志
    ~MainWindow();

private slots:
    void handleUserItemChanged(QTableWidgetItem *item);
    void handleCarItemChanged(QTableWidgetItem *item);
    void handleEmployeeItemChanged(QTableWidgetItem *item);
    void handleRentItemChanged(QTableWidgetItem *item);
    void handleRecordItemChanged(QTableWidgetItem *item);
    void handleBrokenItemChanged(QTableWidgetItem *item);
private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    bool itemIsNew;                                         //用于标识点击查询按钮时的item更新，不进行处理
    QVector<UserInfo> userVec;
    QVector<EmployeeInfo> employeeVec;
    QVector<CarInfo> carVec;
    QVector<RentInfo> rentVec;
    QVector<BrokenInfo> brokenVec;
    QVector<RecordInfo> recordVec;
    AddNewCar newCar;
    AddNewEmployee newEmployee;
    VipDiscountDialog vip;
    StatisticsWindow statisticsWindow;
    static QTableWidget* log;
    static QString getCurrentDateTime();                    //获取当前日期时间
    void initDataBase();                                    //连接数据库
    bool initNetwork();                                     //服务器监听
    void initUI();                                          //初始化UI界面
    void initTimer();                                       //初始化计时器
    void closeNetwork();                                    //关闭TCP连接
    void setWidgetItemUneditable(QTableWidgetItem *item);   //设置QTableWidgetItem为不可编辑
private slots:
    void newConnection();
    void handleTimeout();
    void on_pushBtnFindUser_clicked();
    void on_pushBtnFindEmployee_clicked();
    void on_pushBtnFindCar_clicked();
    void on_pushBtnFindRent_clicked();
    void on_pushBtnBrokenInfo_clicked();
    void on_pushBtnRecordInfo_clicked();
    void on_actionVIP_triggered();
    void on_actionNewCar_triggered();
    void on_actionNewEmployee_triggered();
    void on_actionIncome_triggered();
};
#endif // MAINWINDOW_H
