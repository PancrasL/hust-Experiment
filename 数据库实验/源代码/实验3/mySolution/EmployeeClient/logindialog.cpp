#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QCloseEvent>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

QString LoginDialog::getEID()
{
    return  ui->lineEditUser->text();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushBtnLogin_clicked()
{
    QString msg;
    msg = QString("%1\n%2").arg(ui->lineEditUser->text()).arg(ui->lineEditPassword->text());
    emit tryLogin(msg);
}

void LoginDialog::handleLoginReply(bool success, bool isSellEmployee)
{
    if(success)
    {
        this->isSellEmployee = isSellEmployee;
        accept();
    }
    else {
        QMessageBox::warning(this, tr("登陆失败"),tr("用户名或账户密码错误"),QMessageBox::Yes);
        // 清空内容并定位光标
        ui->lineEditPassword->clear();
        ui->lineEditUser->setFocus();
    }
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

