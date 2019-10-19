#include "myapplication.h"

MyApplication::MyApplication(QObject *parent) : QObject(parent)
{
    connectSignals();
    clientsocket.connectServer();
}

void MyApplication::connectSignals()
{
    connectLoginDlg();
    connectSellWindow();
    connectQuit();
}

void MyApplication::connectLoginDlg()
{
    connect(&logindlg, SIGNAL(tryLogin(const QString&)), &clientsocket, SLOT(handleTryLogin(const QString&)));
    connect(&clientsocket, SIGNAL(loginReply(bool, bool)), &logindlg, SLOT(handleLoginReply(bool, bool)));
}

void MyApplication::connectSellWindow()
{
    connect(&sellwindow, SIGNAL(getOrder(const QString&)), &clientsocket, SLOT(handleGetOrder(const QString&)));
    connect(&clientsocket, SIGNAL(getOrderReply(const QVector<QString> &)), &sellwindow, SLOT(handleGetOrderReply(const QVector<QString> &)));

    connect(&sellwindow, SIGNAL(cancelOrConfirmOrder(const QString&)), &clientsocket, SLOT(cancleOrConfirmOrder(const QString&)));
    connect(&clientsocket, SIGNAL(CclOrCfmReply(const QVector<QString> &)), &sellwindow, SLOT(handleCancelOrConfirmOrder(const QVector<QString> &)));

    connect(&sellwindow, SIGNAL(backCar(const QString&)), &clientsocket, SLOT(handleBackCar(const QString&)));
    connect(&clientsocket, SIGNAL(backCarReply(const QVector<QString> &)), &sellwindow, SLOT(handleBackCarReply(const QVector<QString> &)));

    connect(&sellwindow, SIGNAL(brokenRecord(const QString&)), &clientsocket, SLOT(handleBroken(const QString&)));
    connect(&clientsocket, SIGNAL(brokenReply(const QVector<QString> &)), &sellwindow, SLOT(handleBrokenReply(const QVector<QString> &)));

    connect(&sellwindow, SIGNAL(record(const QString&)), &clientsocket, SLOT(handleRecord(const QString&)));
    connect(&clientsocket, SIGNAL(recordReply(const QVector<QString> &)), &sellwindow, SLOT(handleRecordReply(const QVector<QString> &)));

}

void MyApplication::connectQuit()
{
    connect(&logindlg, SIGNAL(quitApp()), this, SLOT(quit()));
    connect(&sellwindow, SIGNAL(quitApp()), this, SLOT(quit()));
}

void MyApplication::quit()
{
    exit(-1);
}


