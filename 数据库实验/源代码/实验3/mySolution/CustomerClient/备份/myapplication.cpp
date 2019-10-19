#include "myapplication.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "clientsocket.h"
#include <QDebug>
#include <QMessageBox>


myApplication::myApplication()
{
    mainwindow = new MainWindow();
    logindialog = new LoginDialog();
    clientsocket = new ClientSocket();
    connectSignals();
    clientsocket->connectServer();
}

void myApplication::show()
{
    int status = logindialog->exec();
    if (status == QDialog::Accepted)
    {
        mainwindow->curUser.U_ID = logindialog->getID();
        mainwindow->updateUI();
        mainwindow->show();
        mainwindow->showWelcome();
    }
}

void myApplication::connectLoginDlgSignals()
{
    //登录功能
    connect(logindialog, SIGNAL(tryLogin(const QString&)), clientsocket, SLOT(handleTryLogin(const QString&)));
    connect(clientsocket, SIGNAL(loginReply(bool)), logindialog, SLOT(handleLoginReply(bool)));

    //注册账号功能
    connect(logindialog, SIGNAL(tryRegist(const QString&)), clientsocket, SLOT(handleTryRegist(const QString&)));
    connect(clientsocket, SIGNAL(registReply(bool, const QString&)),logindialog,SLOT(handleRegistReply(bool, const QString&)));

    //获取密保信息功能
    connect(logindialog, SIGNAL(tryGetQuestion(const QString&)), clientsocket, SLOT(handleTryGetQuestion(const QString&)));
    connect(clientsocket, SIGNAL(getQuestionReply(bool, const QString&)),logindialog,SLOT(handleGetQuestionReply(bool, const QString&)));

    //找回密码功能
    connect(logindialog, SIGNAL(tryFindPwd(const QString&)), clientsocket, SLOT(handleTryFindPwd(const QString&)));
    connect(clientsocket, SIGNAL(findPwdReply(bool)),logindialog,SLOT(handleFindPwdReply(bool)));

}

void myApplication::connectMainWindowSignals()
{
    connect(mainwindow, SIGNAL(tryGetRentCarInfo(const QString&)), clientsocket, SLOT(handleTryGetRentCarInfo(const QString&)));
    connect(clientsocket, SIGNAL(getRentCarInfoReply(bool, const QVector<QString> &)), mainwindow, SLOT(handleGetRentCarInfoReply(bool, const QVector<QString> &)));
}

void myApplication::connectQuitSignals()
{
    connect(logindialog, SIGNAL(quitApp()), this, SLOT(quit()));
    connect(mainwindow, SIGNAL(quitApp()), this, SLOT(quit()));
}

void myApplication::connectSignals()
{
    connectLoginDlgSignals();
    connectMainWindowSignals();
    connectQuitSignals();
}

void myApplication::quit()
{
    delete logindialog;
    delete mainwindow;
    delete clientsocket;
    exit(0);
}
