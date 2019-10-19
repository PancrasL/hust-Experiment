#include "sellmainwindow.h"
#include "ui_sellmainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
SellMainWindow::SellMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SellMainWindow)
{
    ui->setupUi(this);
    ui->tableWidgetBack->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetPick->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetBrokenInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
}

SellMainWindow::~SellMainWindow()
{
    delete ui;
}

void SellMainWindow::initUI(bool isSellEmployee)
{

    ui->mainToolBar->addAction(ui->actionPickCar);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionBackCar);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionHistoryOrder);
    ui->mainToolBar->addSeparator();
    if(!isSellEmployee)
    {
        ui->mainToolBar->addAction(ui->actionRecord);
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addAction(ui->actionBroken);
    }
}

void SellMainWindow::closeEvent(QCloseEvent *event)
{
    int status = QMessageBox::information(nullptr, "退出程序", "确认退出程序？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(status == QMessageBox::Yes)
    {
        emit quitApp();
    }
    else
        event->ignore();
}

void SellMainWindow::on_actionPickCar_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->dateTimeEditPick->setDateTime(QDateTime::currentDateTime());
}

void SellMainWindow::on_actionBackCar_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->dateTimeEditBack->setDateTime(QDateTime::currentDateTime());
}

void SellMainWindow::on_actionHistoryOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void SellMainWindow::on_actionRecord_triggered()
{
    ui->dateTimeEditRecord->setDateTime(QDateTime::currentDateTime());
    ui->stackedWidget->setCurrentIndex(3);
}

void SellMainWindow::on_actionBroken_triggered()
{
    emit brokenRecord("get spare car");
    ui->dateTimeEditBrokenDate->setDateTime(QDateTime::currentDateTime());
    ui->stackedWidget->setCurrentIndex(4);
}

void SellMainWindow::on_pushBtnFindPickOrder_clicked()
{
    if(ui->lineEditPickCID->text().isEmpty())
    {
        QMessageBox::information(this, "错误", "请输入正确的车牌号");
        return;
    }
    QString msg;
    msg.append("find pick order\n");
    msg.append(this->EID);
    msg.push_back('\n');
    msg.append(ui->lineEditPickCID->text());
    emit getOrder(msg);
}

void SellMainWindow::on_pushBtnFindBackOrder_clicked()
{
    if(ui->lineEditBackCar->text().isEmpty())
    {
        QMessageBox::information(this, "错误", "请输入正确的车牌号");
        return;
    }
    QString msg;
    msg.append("find back order\n");
    msg.append(this->EID);
    msg.push_back('\n');
    msg.append(ui->lineEditBackCar->text());
    emit getOrder(msg);
}

void SellMainWindow::on_pushBtnFindHistoryOrder_clicked()
{
    QString msg;
    msg.append("find history order\n");
    msg.append(this->EID);
    msg.push_back('\n');
    msg.append(ui->dateEdit->text());
    msg.push_back('\n');
    msg.append(ui->dateEdit_2->text());
    emit getOrder(msg);
}

void SellMainWindow::on_pushBtnCancelPickOrder_clicked()
{
    int row = ui->tableWidgetPick->currentRow();
    if(row != -1)
    {
        QString msg;
        msg = "cancel order\n";
        msg.append(EID);
        msg.append('\n');
        msg.append(ui->dateTimeEditPick->text());
        msg.append('\n');
        msg.append(ui->tableWidgetPick->item(row, 0)->text());
        emit cancelOrConfirmOrder(msg);
    }

}

void SellMainWindow::on_pushBtnConfirmPickOrder_clicked()
{
    int row = ui->tableWidgetPick->currentRow();
    if(row != -1)
    {
        QString msg;
        msg = "confirm order\n";
        msg.append(EID);
        msg.append('\n');
        msg.append(ui->dateTimeEditPick->text());
        msg.append('\n');
        msg.append(ui->tableWidgetPick->item(row, 0)->text());
        emit cancelOrConfirmOrder(msg);
    }
}

void SellMainWindow::on_pushBtnConfirmBackOrder_clicked()
{
    int row = ui->tableWidgetBack->currentRow();
    if(row != -1)
    {
        QString msg;
        msg.append(EID);
        msg.append('\n');
        msg.append(ui->tableWidgetBack->item(row, 0)->text());
        msg.append('\n');
        msg.append(ui->dateTimeEditBack->text());
        qDebug()<<msg;
        emit backCar(msg);
    }
}

void SellMainWindow::on_pushButtonConfirmRecord_clicked()
{
    if(ui->lineEditRecordUid->text().isEmpty() || ui->lineEditRecordSituation->text().isEmpty())
    {
        QMessageBox::information(this, "错误", "请填写完整的信息");
        return;
    }
    QString msg = "record\n";
    msg.append(ui->lineEditRecordUid->text());
    msg.push_back('\n');
    msg.append(ui->lineEditRecordSituation->text());
    msg.push_back('\n');
    msg.append(ui->spinBoxRecord->text());
    msg.push_back('\n');
    msg.append(ui->dateTimeEditRecord->text());
    emit record(msg);
}

void SellMainWindow::on_pushBtnBrokenCfm_clicked()
{
    QString msg = "regist broken\n";
    if(ui->lineEditBrokenUid->text().isEmpty())
    {
        QMessageBox::information(this, "请输入身份证号", "请输入身份证号");
        return;
    }
    if(ui->lineEditBrokenSituation->text().isEmpty())
    {
        QMessageBox::information(this, "请填写损坏概况", "请填写损坏概况");
        return;
    }
    if(ui->comboBoxCID->currentIndex() == -1)
        return;
    msg.append(ui->comboBoxCID->currentText());
    msg.push_back('\n');
    msg.append(ui->lineEditBrokenUid->text());
    msg.push_back('\n');
    msg.append(ui->dateTimeEditBrokenDate->text());
    msg.push_back('\n');
    msg.append(ui->lineEditBrokenSituation->text());
    msg.push_back('\n');
    msg.append(ui->comboBoxBroken->currentText());
    msg.push_back('\n');
    msg.append(ui->doubleSpinBoxBrokenPrice->text());
    emit brokenRecord(msg);
}

void SellMainWindow::on_pushBtnRepairCfm_clicked()
{
    QString msg = "repair car\n";
    int row = ui->tableWidgetBrokenInfo->currentRow();
    if(row == -1)
        return;
    msg.append(ui->tableWidgetBrokenInfo->item(row, 0)->text());
    msg.push_back('\n');
    msg.append(ui->tableWidgetBrokenInfo->item(row, 1)->text());
    emit brokenRecord(msg);
}

void SellMainWindow::handleGetOrderReply(const QVector<QString> &info)
{
    QVector<RentInfo> rentVec;
    for(int i=1;i<info.size();i++)
        rentVec.push_back(splitToRentInfo(info[i]));
    if(info[0] == "pick order reply")
    {
        showPickOrder(rentVec);
    }
    else if(info[0] == "back order reply")
    {
        showBackOrder(rentVec);
    }
    else if(info[0] == "history order reply")
    {
        showHistoryOrder(rentVec);
    }
}

void SellMainWindow::handleCancelOrConfirmOrder(const QVector<QString> &info)
{
    if(info[0] == "cancel order reply")
    {
        QMessageBox::information(this, "取消订单", info[1]);
    }
    else if(info[0] == "confirm order reply")
    {
        QMessageBox::information(this, "确认取车", info[1]);
    }
    emit on_pushBtnFindPickOrder_clicked();
}

void SellMainWindow::handleBackCarReply(const QVector<QString> &info)
{
    if(info[0] == "balance is not enough")
    {
        QString msg;
        for(int i=1;i<info.size();i++)
        {
            msg.append(info[i]);
            msg.push_back('\n');
        }
        QMessageBox::information(this, "余额不足", msg);
    }
    else if(info[0] == "back car success")
    {
        QString msg;
        for(int i=1;i<info.size();i++)
        {
            msg.append(info[i]);
            msg.push_back('\n');
        }
        QMessageBox::information(this, "还车成功", msg);
    }
    else if(info[0] == "back car defeat")
        QMessageBox::information(this, "还车失败", "还车失败");
}

void SellMainWindow::handleBrokenReply(const QVector<QString> &info)
{
    if(info[0] == "get spare car reply")
    {
        showSpareCar(info);
    }
    else if(info[0] == "regist broken reply")
    {
        QString msg;
        for(int i=1;i<info.size();i++)
        {
            msg.append(info[i]);
            msg.push_back('\n');
        }
        QMessageBox::information(this, "损坏登记", msg);
        emit brokenRecord("get spare car");
        ui->lineEditBrokenUid->clear();
        ui->lineEditBrokenSituation->clear();
    }
    else if(info[0] == "get broken info reply")
    {
        QVector<BrokenInfo> brokenVec;
        for(int i=1;i<info.size();i++)
        {
            brokenVec.push_back(splitToBrokenInfo(info[i]));
        }
        showBrokenInfo(brokenVec);

    }
    else if(info[0] == "repair car reply")
    {
        QString msg;
        for(int i=1;i<info.size();i++)
        {
            msg.append(info[i]);
            msg.push_back('\n');
        }
        QMessageBox::information(this, "维修登记", msg);
        emit brokenRecord("get broken info");
    }
}

void SellMainWindow::handleRecordReply(const QVector<QString> &info)
{
    if(info[0] == "record reply")
    {
        QString msg;
        for(int i=1;i<info.size();i++)
        {
            msg.append(info[i]);
            msg.push_back('\n');
        }
        QMessageBox::information(this, "维修登记", msg);
        ui->lineEditRecordUid->clear();
        ui->lineEditRecordSituation->clear();
    }
}

RentInfo SellMainWindow::splitToRentInfo(const QString &msg)
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

BrokenInfo SellMainWindow::splitToBrokenInfo(const QString &msg)
{
    QStringList strList = msg.split("#");
    BrokenInfo broken;
    broken.B_ID = strList[0];
    broken.C_ID = strList[1];
    broken.U_ID = strList[2];
    broken.B_TIME = strList[3];
    broken.B_SITUATION = strList[4];
    broken.B_DEGREE = strList[5];
    broken.B_REPAIRED = strList[6];
    broken.B_PRICE = strList[7];
    return broken;
}

void SellMainWindow::showPickOrder(const QVector<RentInfo> &rentVec)
{
    ui->tableWidgetPick->clearContents();
    ui->tableWidgetPick->setSortingEnabled(false);
    ui->tableWidgetPick->setRowCount(rentVec.size());
    for(int i=0;i<rentVec.size();i++)
    {
        ui->tableWidgetPick->setItem(i,0,new QTableWidgetItem(rentVec[i].RT_ID));
        ui->tableWidgetPick->setItem(i,1,new QTableWidgetItem(rentVec[i].U_ID));
        ui->tableWidgetPick->setItem(i,2,new QTableWidgetItem(rentVec[i].E_ID));
        ui->tableWidgetPick->setItem(i,3,new QTableWidgetItem(rentVec[i].C_ID));
        ui->tableWidgetPick->setItem(i,4,new QTableWidgetItem(rentVec[i].RT_TIME));
        ui->tableWidgetPick->setItem(i,5,new QTableWidgetItem(rentVec[i].OUT_TIME));
        ui->tableWidgetPick->setItem(i,6,new QTableWidgetItem(rentVec[i].BACK_TIME));
        ui->tableWidgetPick->setItem(i,7,new QTableWidgetItem(rentVec[i].EXPENSE));
        ui->tableWidgetPick->setItem(i,8,new QTableWidgetItem(rentVec[i].DEPOSIT));
        ui->tableWidgetPick->setItem(i,9,new QTableWidgetItem(rentVec[i].PROGRESS));
        ui->tableWidgetPick->setItem(i,10,new QTableWidgetItem(rentVec[i].RENTAL_TIME));
    }
    ui->tableWidgetPick->setSortingEnabled(true);
}

void SellMainWindow::showBackOrder(const QVector<RentInfo> &rentVec)
{
    ui->tableWidgetBack->clearContents();
    ui->tableWidgetBack->setSortingEnabled(false);
    ui->tableWidgetBack->setRowCount(rentVec.size());
    for(int i=0;i<rentVec.size();i++)
    {
        ui->tableWidgetBack->setItem(i,0,new QTableWidgetItem(rentVec[i].RT_ID));
        ui->tableWidgetBack->setItem(i,1,new QTableWidgetItem(rentVec[i].U_ID));
        ui->tableWidgetBack->setItem(i,2,new QTableWidgetItem(rentVec[i].E_ID));
        ui->tableWidgetBack->setItem(i,3,new QTableWidgetItem(rentVec[i].C_ID));
        ui->tableWidgetBack->setItem(i,4,new QTableWidgetItem(rentVec[i].RT_TIME));
        ui->tableWidgetBack->setItem(i,5,new QTableWidgetItem(rentVec[i].OUT_TIME));
        ui->tableWidgetBack->setItem(i,6,new QTableWidgetItem(rentVec[i].BACK_TIME));
        ui->tableWidgetBack->setItem(i,7,new QTableWidgetItem(rentVec[i].EXPENSE));
        ui->tableWidgetBack->setItem(i,8,new QTableWidgetItem(rentVec[i].DEPOSIT));
        ui->tableWidgetBack->setItem(i,9,new QTableWidgetItem(rentVec[i].PROGRESS));
        ui->tableWidgetBack->setItem(i,10,new QTableWidgetItem(rentVec[i].RENTAL_TIME));
    }
    ui->tableWidgetBack->setSortingEnabled(true);
}

void SellMainWindow::showHistoryOrder(const QVector<RentInfo> &rentVec)
{
    ui->tableWidgetHistory->clearContents();
    ui->tableWidgetHistory->setSortingEnabled(false);
    ui->tableWidgetHistory->setRowCount(rentVec.size());
    for(int i=0;i<rentVec.size();i++)
    {
        ui->tableWidgetHistory->setItem(i,0,new QTableWidgetItem(rentVec[i].RT_ID));
        ui->tableWidgetHistory->setItem(i,1,new QTableWidgetItem(rentVec[i].U_ID));
        ui->tableWidgetHistory->setItem(i,2,new QTableWidgetItem(rentVec[i].E_ID));
        ui->tableWidgetHistory->setItem(i,3,new QTableWidgetItem(rentVec[i].C_ID));
        ui->tableWidgetHistory->setItem(i,4,new QTableWidgetItem(rentVec[i].RT_TIME));
        ui->tableWidgetHistory->setItem(i,5,new QTableWidgetItem(rentVec[i].OUT_TIME));
        ui->tableWidgetHistory->setItem(i,6,new QTableWidgetItem(rentVec[i].BACK_TIME));
        ui->tableWidgetHistory->setItem(i,7,new QTableWidgetItem(rentVec[i].EXPENSE));
        ui->tableWidgetHistory->setItem(i,8,new QTableWidgetItem(rentVec[i].DEPOSIT));
        ui->tableWidgetHistory->setItem(i,9,new QTableWidgetItem(rentVec[i].PROGRESS));
        ui->tableWidgetHistory->setItem(i,10,new QTableWidgetItem(rentVec[i].RENTAL_TIME));
    }
    ui->tableWidgetHistory->setSortingEnabled(true);
}

void SellMainWindow::showSpareCar(const QVector<QString> &info)
{
    ui->comboBoxCID->clear();
    for(int i=1;i<info.size();i++)
    {
        ui->comboBoxCID->addItem(info[i]);
    }
}

void SellMainWindow::showBrokenInfo(const QVector<BrokenInfo> &brokenVec)
{
    ui->tableWidgetBrokenInfo->clearContents();
    ui->tableWidgetBrokenInfo->setSortingEnabled(false);
    ui->tableWidgetBrokenInfo->setRowCount(brokenVec.size());
    for(int i=0;i<brokenVec.size();i++)
    {
        ui->tableWidgetBrokenInfo->setItem(i,0,new QTableWidgetItem(brokenVec[i].B_ID));
        ui->tableWidgetBrokenInfo->setItem(i,1,new QTableWidgetItem(brokenVec[i].C_ID));
        ui->tableWidgetBrokenInfo->setItem(i,2,new QTableWidgetItem(brokenVec[i].U_ID));
        ui->tableWidgetBrokenInfo->setItem(i,3,new QTableWidgetItem(brokenVec[i].B_TIME));
        ui->tableWidgetBrokenInfo->setItem(i,4,new QTableWidgetItem(brokenVec[i].B_SITUATION));
        ui->tableWidgetBrokenInfo->setItem(i,5,new QTableWidgetItem(brokenVec[i].B_DEGREE));
        ui->tableWidgetBrokenInfo->setItem(i,6,new QTableWidgetItem(brokenVec[i].B_REPAIRED));
        ui->tableWidgetBrokenInfo->setItem(i,7,new QTableWidgetItem(brokenVec[i].B_PRICE));
    }
    ui->tableWidgetBrokenInfo->setSortingEnabled(true);
}

void SellMainWindow::on_pushBtnFindUnrepaired_clicked()
{
    emit brokenRecord("get broken info");
}
