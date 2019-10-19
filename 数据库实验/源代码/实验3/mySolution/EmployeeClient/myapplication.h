#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include "sellmainwindow.h"
#include "main.h"
#include "logindialog.h"
#include "eclientsocket.h"
class MyApplication : public QObject
{
    Q_OBJECT
public:
    LoginDialog logindlg;
    SellMainWindow sellwindow;
    EClientSocket clientsocket;
    explicit MyApplication(QObject *parent = nullptr);
    void connectSignals();

private:
    void connectLoginDlg();
    void connectSellWindow();
    void connectRepairWindow();
    void connectQuit();
signals:

public slots:
    void quit();
};

#endif // MYAPPLICATION_H
