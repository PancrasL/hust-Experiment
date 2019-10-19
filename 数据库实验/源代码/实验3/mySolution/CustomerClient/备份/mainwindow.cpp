#include "mainwindow.h"
#include "myStruct.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QDateTime>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"MainWindow's destructor";
}

void MainWindow::initTimer()
{
    QTimer *pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    pTimer->start(500);
}

CarInfo MainWindow::splitToCarInfo(const QString &msg)
{
    QStringList strList = msg.split("#");
    CarInfo car;
    car.C_ID = strList[0];
    car.C_TYPE = strList[1];
    car.C_BRAND = strList[2];
    car.C_DEPOSIT = strList[3];
    car.C_PRICE = strList[4];
    car.C_TIMEOUT_PRICE = strList[5];
    return car;
}

void MainWindow::setWidgetItemUneditable(QTableWidgetItem *item)
{
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
}

void MainWindow::handleTimeout()
{
    QDateTime dt = QDateTime::currentDateTime();
    curTimeLabel->setText(dt.toString(Qt::SystemLocaleLongDate));
}

void MainWindow::handleGetRentCarInfoReply(bool success, const QVector<QString> &info)
{
    if(success == false)
    {
        QMessageBox::information(this, "获取车辆信息失败", "信誉积分不足，无法租车。");
        return;
    }
    carVec.clear();
    for(int i = 1;i < info.size();i++)
    {
        carVec.push_back(splitToCarInfo(info[i]));
    }
    ui->tableWidgetCarInfo->clearContents();
    ui->tableWidgetCarInfo->setRowCount(carVec.size());
    for(int i=0;i<carVec.size();i++)
    {
        qDebug()<<carVec[i].C_ID;
        ui->tableWidgetCarInfo->setItem(i,0,new QTableWidgetItem(carVec[i].C_ID));
        ui->tableWidgetCarInfo->setItem(i,1,new QTableWidgetItem(carVec[i].C_TYPE));
        ui->tableWidgetCarInfo->setItem(i,2,new QTableWidgetItem(carVec[i].C_BRAND));
        ui->tableWidgetCarInfo->setItem(i,3,new QTableWidgetItem(carVec[i].C_DEPOSIT));
        ui->tableWidgetCarInfo->setItem(i,4,new QTableWidgetItem(carVec[i].C_PRICE));
        ui->tableWidgetCarInfo->setItem(i,5,new QTableWidgetItem(carVec[i].C_TIMEOUT_PRICE));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,0));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,1));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,2));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,3));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,4));
        setWidgetItemUneditable(ui->tableWidgetCarInfo->item(i,5));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int status = QMessageBox::information(nullptr, "退出程序", "确认退出程序？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(status == QMessageBox::Yes)
    {
        emit quitApp();
    }
    else
        event->ignore();
}

void MainWindow::showWelcome()
{
    ui->statusBar->showMessage(tr("欢迎您，%1").arg("user name"),5000);
}

void MainWindow::updateUI()
{
    emit tryGetRentCarInfo(curUser.U_ID);
}

void MainWindow::initUI()
{
    /*设置图标*/
    ui->actionRentCar->setIcon(QIcon(":/images/car.png"));
    ui->actionSheet->setIcon(QIcon(":/images/statistics.png"));
    ui->actionHistoryOrder->setIcon(QIcon(":/images/history.png"));

    /*设置tableWidget*/
    ui->tableWidgetCarInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /*设置状态栏*/
    curTimeLabel = new QLabel(this);
    curTimeLabel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->statusBar->addPermanentWidget(curTimeLabel);
    ui->stackedWidget->setCurrentIndex(0);

    /*设置工具栏*/

}

void MainWindow::on_actionRentCar_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    emit tryGetRentCarInfo(curUser.U_ID);
}

void MainWindow::on_actionHistoryOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionSheet_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}
