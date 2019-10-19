#include "logindialog.h"
#include "ui_logindialog.h"
#include "registdialog.h"
#include "findpwddialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    regist = new RegistDialog(this);
    findpwd = new FindPwdDialog(this);
    //注册账号
    connect(this, SIGNAL(registSuccess()), this->regist, SLOT(handleRegistSuccess()));
    connect(this, SIGNAL(registDefeat(const QString&)), this->regist, SLOT(handleRegistDefeat(const QString&)));
    connect(this->regist, SIGNAL(tryRegist(const QString &)), this, SLOT(emitTryRegist(const QString&)));

    //获取密保
    connect(this, SIGNAL(getQuestion(bool, const QString &)), this->findpwd, SLOT(handleGetQuestion(bool, const QString &)));
    connect(this->findpwd, SIGNAL(tryGetQuestion(const QString &)), this, SLOT(emitTryGetQuestion(const QString&)));

    //重置密码
    connect(this, SIGNAL(findPwdSuccess()), this->findpwd, SLOT(handleFindPwdSuccess()));
    connect(this, SIGNAL(findPwdDefeat()), this->findpwd, SLOT(handleFindPwdDefeat()));
    connect(this->findpwd, SIGNAL(tryFindPwd(const QString &)), this, SLOT(emitTryFindPwd(const QString&)));
}

QString LoginDialog::getID()
{
    return ui->lineEditUser->text().trimmed();
}

LoginDialog::~LoginDialog()
{
    delete ui;
    qDebug()<<"LoginDialog's destructor";
}

void LoginDialog::on_pushBtnLogin_clicked()
{
    /*取出账号密码*/
    QString msg;
    msg.append(ui->lineEditUser->text().trimmed() + "\n");
    msg.append(ui->lineEditPassword->text());

    /*向服务器发送数据*/
    emit tryLogin(msg);
}

void LoginDialog::on_pushBtnRegist_clicked()
{
    regist->exec();
}

void LoginDialog::on_pushBtnFindPwd_clicked()
{
    findpwd->exec();
}

void LoginDialog::handleLoginReply(bool success)
{
    if(success == true)
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("登陆失败"),tr("用户名或账户密码错误"),QMessageBox::Yes);
        // 清空内容并定位光标
        ui->lineEditPassword->clear();
        ui->lineEditUser->setFocus();
    }
}

void LoginDialog::handleRegistReply(bool success, const QString &msg)
{
    if(success == true)
    {
        emit registSuccess();
    }
    else
    {
        emit registDefeat(msg);
    }
}

void LoginDialog::handleFindPwdReply(bool success)
{
    if(success == true)
    {
        emit findPwdSuccess();
    }
    else
    {
        emit findPwdDefeat();
    }
}

void LoginDialog::handleGetQuestionReply(bool success, const QString &msg)
{
    emit getQuestion(success, msg);
}

void LoginDialog::emitTryRegist(const QString &msg)
{
    emit tryRegist(msg);
}

void LoginDialog::emitTryFindPwd(const QString &msg)
{
    emit tryFindPwd(msg);
}

void LoginDialog::emitTryGetQuestion(const QString &msg)
{
    emit tryGetQuestion(msg);
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    int status = QMessageBox::information(nullptr, "退出程序", "确认退出程序？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(status == QMessageBox::Yes)
    {
        emit quitApp();
    }
    else
        event->ignore();
}

