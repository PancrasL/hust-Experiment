#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include <QApplication>
class LoginDialog;
class MainWindow;
class UClientSocket;
class myApplication : public QObject
{
    Q_OBJECT
public:
    explicit myApplication();
    void show();

private:
    LoginDialog *logindialog;
    MainWindow *mainwindow;
    UClientSocket *clientsocket;
    void connectLoginDlgSignals();
    void connectMainWindowSignals();
    void connectQuitSignals();
    void connectSignals();

signals:

public slots:
    void quit();
};

#endif // MYAPPLICATION_H
