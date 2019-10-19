#include "mainwindow.h"
#include "myStruct.h"
#include "ui_mainwindow.h"
#include "rentdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QDateTime>
#include <QLabel>
#include <QTimer>
#include <QInputDialog>
#include <QSpinBox>
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


RentInfo MainWindow::splitToRentInfo(const QString &msg)
{
    QStringList strList = msg.split("#");
    RentInfo rent;
    rent.RT_ID = strList[0];
    rent.U_ID = strList[1];
    rent.E_ID = strList[2];
    rent.C_ID = strList[3];
    rent.RT_TIME = strList[4];
    rent.OUT_TIME = strList[5];
    rent.BACK_TIME = strList[6];
    rent.EXPENSE = strList[7];
    rent.DEPOSIT = strList[8];
    rent.PROGRESS = strList[9];
    rent.RENTAL_TIME = strList[10];
    return rent;
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
    ui->tableWidgetCarInfo->setSortingEnabled(false);
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
    ui->tableWidgetCarInfo->setSortingEnabled(true);
}

void MainWindow::handleGetUserInfoReply(const QVector<QString> &info)
{
    user.U_ID = info[0];
    user.U_NAME = info[1];
    user.U_CREDIT = info[2];
    user.U_BALANCE = info[3];
    ui->labelShowId->setText(user.U_ID);
    ui->labelShowName->setText(user.U_NAME);
    ui->labelShowCredit->setText(user.U_CREDIT);
    ui->labelShowBalance->setText(user.U_BALANCE);
}

void MainWindow::handleRentCarReply(const QVector<QString> &info)
{
    rentdlg.initUI(info);
    int status = rentdlg.exec();
    if(status == QDialog::Accepted)
    {
        QString msg = QString("%1\n%2\n%3\n%4\n%5").arg(user.U_ID).arg(info[0]).arg(info[5]).arg(info[6]).arg(info[7]);
        emit confirmRentCar(msg);
    }
}

void MainWindow::handleConfirmRentCarReply(const QString &msg)
{
    QMessageBox::information(this, "租车信息", msg);
    emit tryGetRentCarInfo(user.U_ID);
}

void MainWindow::handleGetHistoryOrderReply(const QVector<QString> &info)
{
    QVector<RentInfo> rentVec;
    for(auto str:info)
    {
        rentVec.push_back(splitToRentInfo(str));
    }
    ui->tableWidgetRentInfo->clearContents();
    ui->tableWidgetRentInfo->setSortingEnabled(false);
    ui->tableWidgetRentInfo->setRowCount(rentVec.size());
    for(int i=0;i<rentVec.size();i++)
    {
        ui->tableWidgetRentInfo->setItem(i,0,new QTableWidgetItem(rentVec[i].RT_ID));
        ui->tableWidgetRentInfo->setItem(i,1,new QTableWidgetItem(rentVec[i].E_ID));
        ui->tableWidgetRentInfo->setItem(i,2,new QTableWidgetItem(rentVec[i].C_ID));
        ui->tableWidgetRentInfo->setItem(i,3,new QTableWidgetItem(rentVec[i].RT_TIME));
        ui->tableWidgetRentInfo->setItem(i,4,new QTableWidgetItem(rentVec[i].OUT_TIME));
        ui->tableWidgetRentInfo->setItem(i,5,new QTableWidgetItem(rentVec[i].BACK_TIME));
        ui->tableWidgetRentInfo->setItem(i,6,new QTableWidgetItem(rentVec[i].EXPENSE));
        ui->tableWidgetRentInfo->setItem(i,7,new QTableWidgetItem(rentVec[i].DEPOSIT));
        ui->tableWidgetRentInfo->setItem(i,8,new QTableWidgetItem(rentVec[i].PROGRESS));
        ui->tableWidgetRentInfo->setItem(i,9,new QTableWidgetItem(rentVec[i].RENTAL_TIME));
    }
    ui->tableWidgetRentInfo->setSortingEnabled(true);
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
    emit tryGetUserInfo(user.U_ID);
}

void MainWindow::initUI()
{
    /*设置图标*/
    ui->actionRentCar->setIcon(QIcon(":/images/car.png"));
    ui->actionHistoryOrder->setIcon(QIcon(":/images/history.png"));

    /*设置可租车辆tableWidget*/
    ui->tableWidgetCarInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetRentInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /*设置状态栏*/
    curTimeLabel = new QLabel(this);
    curTimeLabel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->statusBar->addPermanentWidget(curTimeLabel);
    ui->stackedWidget->setCurrentIndex(0);

    /*设置工具栏*/
    ui->mainToolBar->addAction(ui->actionUserInfo);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionRentCar);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionHistoryOrder);

}

void MainWindow::on_actionUserInfo_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    emit tryGetUserInfo(user.U_ID);
}

void MainWindow::on_actionRentCar_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    emit tryGetRentCarInfo(user.U_ID);
}

void MainWindow::on_actionHistoryOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionSheet_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushBtnrentCar_clicked()
{
    if(ui->tableWidgetCarInfo->currentRow()==-1)
        return;
    bool isOK;
    QInputDialog dlg;
    int value = dlg.getInt(this, "租车时长", "请填写租车时长", 1, 1, 365, 1, &isOK);
    if(isOK)
    {
        QString C_ID;
        int row = ui->tableWidgetCarInfo->currentRow();
        C_ID = ui->tableWidgetCarInfo->item(row, 0)->text();
        QString msg = QString("%1\n%2\n%3").arg(user.U_ID).arg(C_ID).arg(QString::number(value));
        emit tryRentCar(msg);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString msg = QString("%1\n%2\n%3").arg(user.U_ID).arg(ui->dateEditStart->text()).arg(ui->dateEditClosing->text());
    emit getHistoryOrder(msg);
}
