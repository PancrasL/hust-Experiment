#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"
class RegistDialog;
class FindPwdDialog;
namespace Ui {
class LoginDialog;
}
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getID();
    ~LoginDialog();

private slots:
    void on_pushBtnLogin_clicked();
    void on_pushBtnRegist_clicked();
    void on_pushBtnFindPwd_clicked();
    void handleLoginReply(bool success);
    void handleRegistReply(bool success, const QString &msg);
    void handleFindPwdReply(bool succes);
    void handleGetQuestionReply(bool success, const QString &msg);
    void emitTryRegist(const QString &msg);                       //在收到regist的提交注册信息的信号时触发
    void emitTryFindPwd(const QString &msg);                      //在收到findpwd的找回密码信号时触发
    void emitTryGetQuestion(const QString &msg);                  //在收到findpwd的获取密保信号时触发
private:
    Ui::LoginDialog *ui;
    RegistDialog *regist;
    FindPwdDialog *findpwd;
signals:
    //和ClientSocket连接
    void tryLogin(const QString &msg);
    void tryRegist(const QString &msg);
    void tryFindPwd(const QString &msg);
    void tryGetQuestion(const QString &msg);
    //和子窗口RegistDialog的槽函数连接
    void registSuccess();
    void registDefeat(const QString &msg);

    //和子窗口FindPwdDialog的槽函数连接
    void findPwdSuccess();
    void findPwdDefeat();
    void getQuestion(bool success, const QString &msg);         //获取密保问题的结果
    //按下叉号时发射的信号，被myApplication捕捉，用于退出程序
    void quitApp();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOGINDIALOG_H
