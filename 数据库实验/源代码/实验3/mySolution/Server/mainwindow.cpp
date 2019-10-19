#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "serversocket.h"
#include "dbconnector.h"
#include "customtablemodel.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QTimer>
#include <QTcpServer>
#include <QMutex>
#include <QThread>
extern DBConnector dbConnector;
QTableWidget* MainWindow::log;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::log = ui->log;  //添加日志的位置
    initDataBase();
    initNetwork();
    initUI();
    initTimer();
}

MainWindow::~MainWindow()
{
    delete tcpServer;
    delete ui;
}

void MainWindow::handleUserItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        //属性列表
        const char *attributeArray[]={"U_ID", "U_PASSWORD", "U_PHONE_NUM", "U_NAME",
                                      "U_SEX", "U_BIRTHDAY", "U_VIP", "U_CREDIT", "U_BALANCE",
                                      "U_REGISTDATE", "U_SECRET_QUESTION", "U_SECRET_ANSWER"};
        //获取内容改变的单元格的行和列
        int row = item->row();
        int col = item->column();
        //根据列数获取被修改的属性
        QString attribute = attributeArray[col];
        //根据行、列获取用户编号
        QString id = userVec[row].U_ID;
        QString value = item->text();
        //修改用户信息
        bool success = dbConnector.updateUserInfo(id, attribute, value);
        if(success)
        {
            QMessageBox::information(this, "用户信息表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "用户信息表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::handleCarItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        const char *attributeArray[]={"C_ID", "C_TYPE", "C_BRAND", "C_BUYTIME", "C_DEPOSIT", "C_PRICE", "C_TIMEOUT_PRICE", "C_STATUS"};
        int row = item->row();
        int col = item->column();
        QString attribute = attributeArray[col];
        QString id = carVec[row].C_ID;
        QString value = item->text();
        bool success = dbConnector.updateCarInfo(id, attribute, value);
        if(success)
        {
            QMessageBox::information(this, "车辆信息表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "车辆信息表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::handleEmployeeItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        const char *attributeArray[]={"E_ID", "E_PASSWORD", "E_NAME", "E_SEX", "E_PHONE_NUM", "E_ENTRYDATE", "E_TYPE"};
        int row = item->row();
        int col = item->column();
        QString attribute = attributeArray[col];
        QString id = employeeVec[row].E_ID;
        QString value = item->text();
        bool success = dbConnector.updateEmployeeInfo(id, attribute, value);
        qDebug()<<success;
        if(success)
        {
            QMessageBox::information(this, "员工信息表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "员工信息表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::handleRentItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        const char *attributeArray[]={"RT_ID", "U_ID", "E_ID", "C_ID", "RT_TIME",
                                      "OUT_TIME", "BACK_TIME", "EXPENSE", "DEPOSIT",
                                      "PROGRESS", "RENTAL_TIME"};
        int row = item->row();
        int col = item->column();
        QString attribute = attributeArray[col];
        QString id = rentVec[row].RT_ID;
        QString value = item->text();
        bool success = dbConnector.updateRentInfo(id, attribute, value);
        if(success)
        {
            QMessageBox::information(this, "租赁信息表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "租赁信息表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::handleRecordItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        const char *attributeArray[]={"R_ID", "U_ID", "R_SITUATION", "R_FINE", "R_TIME"};
        int row = item->row();
        int col = item->column();
        QString attribute = attributeArray[col];
        QString id = recordVec[row].R_ID;
        QString value = item->text();
        bool success = dbConnector.updateRecordInfo(id, attribute, value);
        if(success)
        {
            QMessageBox::information(this, "违章信息表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "违章信息表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::handleBrokenItemChanged(QTableWidgetItem *item)
{
    if(!itemIsNew)
    {
        const char *attributeArray[]={"B_ID", "C_ID", "U_ID", "B_TIME", "B_SITUATION", "B_DEGREE", "B_REPAIRED", "B_PRICE"};
        int row = item->row();
        int col = item->column();
        QString attribute = attributeArray[col];
        QString id = brokenVec[row].B_ID;
        QString value = item->text();
        bool success = dbConnector.updateBrokenInfo(id, attribute, value);
        if(success)
        {
            QMessageBox::information(this, "损坏记录表", QString("%1数据已更新").arg(attribute));
        }
        else
        {
            QMessageBox::information(this, "损坏记录表", QString("%1数据更新失败，请输入正确的数据").arg(attribute));
        }
    }
}

void MainWindow::addLog(const QString &obj, const QString &msg)
{
    int rowcount = log->rowCount();
    log->insertRow(rowcount);
    log->setItem(rowcount,0,new QTableWidgetItem(getCurrentDateTime()));
    log->setItem(rowcount,1,new QTableWidgetItem(obj));
    log->setItem(rowcount,2,new QTableWidgetItem(msg));
}

QString MainWindow::getCurrentDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
}

void MainWindow::initDataBase()
{
    if(dbConnector.isOpen())
        addLog("server", "数据库连接成功");
    else
    {
        QMessageBox::information(this,"数据库", "数据库连接失败!");
        addLog("server", "数据库连接失败");
    }
}

bool MainWindow::initNetwork()
{
    //创建监听Socket
    tcpServer= new QTcpServer();
    //开始监听
    if(!tcpServer->listen(QHostAddress::Any,Config::port))
    {
        QMessageBox::information(this,"QT网络通信","服务器监听失败!");
        addLog("server","服务器监听失败");
        return false;
    }
    addLog("server","服务器监听成功");
    //处理连接信号
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));
    return true;
}

void MainWindow::initUI()
{
    connect(ui->tableWidgetUserInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleUserItemChanged(QTableWidgetItem *)));
    connect(ui->tableWidgetCarInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleCarItemChanged(QTableWidgetItem *)));
    connect(ui->tableWidgetEmployeeInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleEmployeeItemChanged(QTableWidgetItem *)));
    connect(ui->tableWidgetRentInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleRentItemChanged(QTableWidgetItem *)));
    connect(ui->tableWidgetRecordInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleRecordItemChanged(QTableWidgetItem *)));
    connect(ui->tableWidgetBrokenInfo, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(handleBrokenItemChanged(QTableWidgetItem *)));

    ui->tableWidgetRentInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetUserInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetEmployeeInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetCarInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetBrokenInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidgetRecordInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->log->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽

}

void MainWindow::initTimer()
{
    QTimer *pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    pTimer->start(500);
}

void MainWindow::closeNetwork()
{
    Q_CHECK_PTR(tcpServer);
    tcpServer->close();
    delete tcpServer;
}

void MainWindow::setWidgetItemUneditable(QTableWidgetItem *item)
{
    item->setBackground(QBrush(QColor(Qt::lightGray)));
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
}

void MainWindow::newConnection()
{
    QTcpSocket *tcpSocket= tcpServer->nextPendingConnection();
    ServerSocket *serverSocket = new ServerSocket();
    serverSocket->setTcpSocket(tcpSocket);
    //MainWindow::addLog("server","收到来自客户端的连接！");
}

void MainWindow::handleTimeout()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->labelDateTime->setText(str);
}

void MainWindow::on_pushBtnFindUser_clicked()
{
    itemIsNew = true;
    ui->tableWidgetUserInfo->clearContents();
    ui->tableWidgetUserInfo->setSortingEnabled(false);
    QString value = ui->lineEditUserInfo->text();
    int index = ui->comboBoxUserInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_USER_BY_NAME;
        break;
    case 1:
        type = MODE::QUERY_USER_BY_UID;
        break;
    case 2:
        type = MODE::QUERY_USER_BY_PHONE;
        break;
    default:
        ;
    }
    userVec.clear();
    userVec = dbConnector.getUserInfo(value, type);
    ui->tableWidgetUserInfo->setRowCount(userVec.size());;
    for(int i=0;i<userVec.size();i++)
    {
        ui->tableWidgetUserInfo->setItem(i,0,new QTableWidgetItem(userVec[i].U_ID));
        ui->tableWidgetUserInfo->setItem(i,1,new QTableWidgetItem(userVec[i].U_PASSWORD));
        ui->tableWidgetUserInfo->setItem(i,2,new QTableWidgetItem(userVec[i].U_PHONE_NUM));
        ui->tableWidgetUserInfo->setItem(i,3,new QTableWidgetItem(userVec[i].U_NAME));
        ui->tableWidgetUserInfo->setItem(i,4,new QTableWidgetItem(userVec[i].U_SEX));
        ui->tableWidgetUserInfo->setItem(i,5,new QTableWidgetItem(userVec[i].U_BIRTHDAY));
        ui->tableWidgetUserInfo->setItem(i,6,new QTableWidgetItem(userVec[i].U_VIP));
        ui->tableWidgetUserInfo->setItem(i,7,new QTableWidgetItem(userVec[i].U_CREDIT));
        ui->tableWidgetUserInfo->setItem(i,8,new QTableWidgetItem(userVec[i].U_BALANCE));
        ui->tableWidgetUserInfo->setItem(i,9,new QTableWidgetItem(userVec[i].U_REGISTDATE));
        ui->tableWidgetUserInfo->setItem(i,10,new QTableWidgetItem(userVec[i].U_SECRET_QUESTION));
        ui->tableWidgetUserInfo->setItem(i,11,new QTableWidgetItem(userVec[i].U_SECRET_ANSWER));
    }
    ui->tableWidgetUserInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_pushBtnFindEmployee_clicked()
{
    itemIsNew = true;
    ui->tableWidgetEmployeeInfo->clearContents();
    ui->tableWidgetEmployeeInfo->setSortingEnabled(false);
    QString value = ui->lineEditEmployeeInfo->text();
    int index = ui->comboBoxEmployeeInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_EP_BY_NAME;
        break;
    case 1:
        type = MODE::QUERY_EP_BY_EID;
        break;
    case 2:
        type = MODE::QUERY_EP_BY_PHONE;
        break;
    default:
        break;
    }
    employeeVec.clear();
    employeeVec = dbConnector.getEmployeeInfo(value,type);
    ui->tableWidgetEmployeeInfo->setRowCount(employeeVec.size());
    for(int i=0;i<employeeVec.size();i++)
    {
        ui->tableWidgetEmployeeInfo->setItem(i,0,new QTableWidgetItem(employeeVec[i].E_ID));
        ui->tableWidgetEmployeeInfo->setItem(i,1,new QTableWidgetItem(employeeVec[i].E_PASSWORD));
        ui->tableWidgetEmployeeInfo->setItem(i,2,new QTableWidgetItem(employeeVec[i].E_NAME));
        ui->tableWidgetEmployeeInfo->setItem(i,3,new QTableWidgetItem(employeeVec[i].E_SEX));
        ui->tableWidgetEmployeeInfo->setItem(i,4,new QTableWidgetItem(employeeVec[i].E_PHONE_NUM));
        ui->tableWidgetEmployeeInfo->setItem(i,5,new QTableWidgetItem(employeeVec[i].E_ENTRYDATE));
        ui->tableWidgetEmployeeInfo->setItem(i,6,new QTableWidgetItem(employeeVec[i].E_TYPE));
    }
    ui->tableWidgetEmployeeInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_pushBtnFindCar_clicked()
{
    itemIsNew = true;
    ui->tableWidgetCarInfo->clearContents();
    ui->tableWidgetCarInfo->setSortingEnabled(false);
    QString value = ui->lineEditCarInfo->text();
    int index = ui->comboBoxCarInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_CAR_BY_CID;
        break;
    case 1:
        type = MODE::QUERY_CAR_BY_TYPE;
        break;
    default:
        break;
    }
    carVec.clear();
    carVec = dbConnector.getCarInfo(value,type);
    ui->tableWidgetCarInfo->setRowCount(carVec.size());
    for(int i=0;i<carVec.size();i++)
    {
        ui->tableWidgetCarInfo->setItem(i,0,new QTableWidgetItem(carVec[i].C_ID));
        ui->tableWidgetCarInfo->setItem(i,1,new QTableWidgetItem(carVec[i].C_TYPE));
        ui->tableWidgetCarInfo->setItem(i,2,new QTableWidgetItem(carVec[i].C_BRAND));
        ui->tableWidgetCarInfo->setItem(i,3,new QTableWidgetItem(carVec[i].C_BUYTIME));
        ui->tableWidgetCarInfo->setItem(i,4,new QTableWidgetItem(carVec[i].C_DEPOSIT));
        ui->tableWidgetCarInfo->setItem(i,5,new QTableWidgetItem(carVec[i].C_PRICE));
        ui->tableWidgetCarInfo->setItem(i,6,new QTableWidgetItem(carVec[i].C_TIMEOUT_PRICE));
        ui->tableWidgetCarInfo->setItem(i,7,new QTableWidgetItem(carVec[i].C_STATUS));
    }
    ui->tableWidgetCarInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_pushBtnFindRent_clicked()
{
    itemIsNew = true;
    QString startTime = ui->startDateEdit->date().toString("yyyy-MM-dd");
    QString closingTime = ui->closingDateEdit->date().toString("yyyy-MM-dd");
    ui->tableWidgetRentInfo->clearContents();
    ui->tableWidgetRentInfo->setSortingEnabled(false);
    QString value = ui->lineEditRentInfo->text();
    int index = ui->comboBoxRentInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_RENT_BY_RTID;
        break;
    case 1:
        type = MODE::QUERY_RENT_BY_UID;
        break;
    case 2:
        type = MODE::QUERY_RENT_BY_EID;
        break;
    case 3:
        type = MODE::QUERY_RENT_BY_CID;
        break;
    default:
        break;
    }
    rentVec.clear();
    rentVec = dbConnector.getRentInfo(value,type,startTime,closingTime);
    ui->tableWidgetRentInfo->setRowCount(rentVec.size());
    for(int i=0;i<rentVec.size();i++)
    {
        ui->tableWidgetRentInfo->setItem(i,0,new QTableWidgetItem(rentVec[i].RT_ID));
        ui->tableWidgetRentInfo->setItem(i,1,new QTableWidgetItem(rentVec[i].U_ID));
        ui->tableWidgetRentInfo->setItem(i,2,new QTableWidgetItem(rentVec[i].E_ID));
        ui->tableWidgetRentInfo->setItem(i,3,new QTableWidgetItem(rentVec[i].C_ID));
        ui->tableWidgetRentInfo->setItem(i,4,new QTableWidgetItem(rentVec[i].RT_TIME));
        ui->tableWidgetRentInfo->setItem(i,5,new QTableWidgetItem(rentVec[i].OUT_TIME));
        ui->tableWidgetRentInfo->setItem(i,6,new QTableWidgetItem(rentVec[i].BACK_TIME));
        ui->tableWidgetRentInfo->setItem(i,7,new QTableWidgetItem(rentVec[i].EXPENSE));
        ui->tableWidgetRentInfo->setItem(i,8,new QTableWidgetItem(rentVec[i].DEPOSIT));
        ui->tableWidgetRentInfo->setItem(i,9,new QTableWidgetItem(rentVec[i].PROGRESS));
        ui->tableWidgetRentInfo->setItem(i,10,new QTableWidgetItem(rentVec[i].RENTAL_TIME));
        //设置外码不可编辑
        setWidgetItemUneditable(ui->tableWidgetRentInfo->item(i, 1));
        setWidgetItemUneditable(ui->tableWidgetRentInfo->item(i, 2));
        setWidgetItemUneditable(ui->tableWidgetRentInfo->item(i, 3));
    }
    ui->tableWidgetRentInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_pushBtnBrokenInfo_clicked()
{
    itemIsNew = true;
    QString startTime = ui->startDateEdit->date().toString("yyyy-MM-dd");
    QString closingTime = ui->closingDateEdit->date().toString("yyyy-MM-dd");
    ui->tableWidgetBrokenInfo->clearContents();
    ui->tableWidgetBrokenInfo->setSortingEnabled(false);
    QString value = ui->lineEditBrokenInfo->text();
    int index = ui->comboBoxBrokenInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_BROKEN_BY_BID;
        break;
    case 1:
        type = MODE::QUERY_BROKEN_BY_CID;
        break;
    case 2:
        type = MODE::QUERY_BROKEN_BY_UID;
        break;
    default:
        break;
    }
    brokenVec.clear();
    brokenVec = dbConnector.getBrokenInfo(value,type,startTime,closingTime);
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
        //设置外码不可编辑
        setWidgetItemUneditable(ui->tableWidgetBrokenInfo->item(i, 1));
        setWidgetItemUneditable(ui->tableWidgetBrokenInfo->item(i, 2));
    }
    ui->tableWidgetBrokenInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_pushBtnRecordInfo_clicked()
{
    itemIsNew = true;
    QString startTime = ui->startDateEdit->date().toString("yyyy-MM-dd");
    QString closingTime = ui->closingDateEdit->date().toString("yyyy-MM-dd");
    ui->tableWidgetRecordInfo->clearContents();
    ui->tableWidgetRecordInfo->setSortingEnabled(false);
    QString value = ui->lineEditRecordInfo->text();
    int index = ui->comboBoxRecordInfo->currentIndex();
    int type = 0;
    switch (index) {
    case 0:
        type = MODE::QUERY_RECORD_BY_RID;
        break;
    case 1:
        type = MODE::QUERY_RECORD_BY_UID;
        break;
    default:
        break;
    }
    recordVec.clear();
    recordVec = dbConnector.getRecordInfo(value,type,startTime,closingTime);
    ui->tableWidgetRecordInfo->setRowCount(recordVec.size());
    for(int i=0;i<recordVec.size();i++)
    {
        ui->tableWidgetRecordInfo->setItem(i,0,new QTableWidgetItem(recordVec[i].R_ID));
        ui->tableWidgetRecordInfo->setItem(i,1,new QTableWidgetItem(recordVec[i].U_ID));
        ui->tableWidgetRecordInfo->setItem(i,2,new QTableWidgetItem(recordVec[i].R_SITUATION));
        ui->tableWidgetRecordInfo->setItem(i,3,new QTableWidgetItem(recordVec[i].R_FINE));
        ui->tableWidgetRecordInfo->setItem(i,4,new QTableWidgetItem(recordVec[i].R_TIME));
        //设置外码不可编辑
        setWidgetItemUneditable(ui->tableWidgetRecordInfo->item(i, 1));
    }
    ui->tableWidgetRecordInfo->setSortingEnabled(true);
    itemIsNew = false;
}

void MainWindow::on_actionVIP_triggered()
{
    vip.show();
}

void MainWindow::on_actionNewCar_triggered()
{
    newCar.show();
}

void MainWindow::on_actionNewEmployee_triggered()
{
    newEmployee.show();
}

void MainWindow::on_actionIncome_triggered()
{
    statisticsWindow.show();
}
