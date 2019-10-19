#include "registdialog.h"
#include "ui_registdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
RegistDialog::RegistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistDialog)
{
    ui->setupUi(this);
    connect(ui->lineEditID,SIGNAL(editingFinished()),this,SLOT(finishedIDEdit()));
    connect(ui->lineEditID,SIGNAL(textChanged(const QString&)),this,SLOT(startIDEdit()));
    connect(ui->lineEditPwd2,SIGNAL(editingFinished()),this,SLOT(finishedPwdEdit()));
    connect(ui->lineEditPwd2,SIGNAL(textChanged(const QString&)),this,SLOT(startPwdEdit()));
    connect(ui->lineEditPhone,SIGNAL(editingFinished()),this,SLOT(finishedPhoneEdit()));
    connect(ui->lineEditPhone,SIGNAL(textChanged(const QString&)),this,SLOT(startPhoneEdit()));
    connect(ui->lineEditName,SIGNAL(textChanged(const QString&)),this,SLOT(startNameEdit()));
    connect(ui->lineEditQuestion,SIGNAL(textChanged(const QString&)),this,SLOT(startQuestionEdit()));
    connect(ui->lineEditAnswer,SIGNAL(textChanged(const QString&)),this,SLOT(startAnswerEdit()));
}

RegistDialog::~RegistDialog()
{
    delete ui;
    qDebug()<<"RegistDialog's destructor";
}

void RegistDialog::on_registBtn_clicked()
{
    if(checkInput()==true)
    {
        QString msg;
        msg.append(ui->lineEditID->text());         //身份证号
        msg.append("\n");
        msg.append(ui->lineEditPwd->text());        //密码
        msg.append("\n");
        msg.append(ui->lineEditPhone->text());      //手机号码
        msg.append("\n");
        msg.append(ui->lineEditName->text());       //姓名
        msg.append("\n");
        msg.append(ui->comboBox->currentText());    //性别
        msg.append("\n");
        QString birthday = ui->lineEditID->text().mid(6,8);
        birthday.insert(4,'-');
        birthday.insert(7,'-');
        msg.append(birthday);                       //从身份证号中提取出生日
        msg.append("\n");
        msg.append("0");                            //新帐号的VIP等级为0
        msg.append("\n");
        msg.append("90");                           //新用户的信誉等级为90
        msg.append("\n");
        msg.append("0");                            //新用户的余额为0
        msg.append("\n");
        msg.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));//注册日期
        msg.append("\n");
        msg.append(ui->lineEditQuestion->text());   //密保问题
        msg.append("\n");
        msg.append(ui->lineEditAnswer->text());     //密保答案
        qDebug()<<"regist Info:";
        qDebug()<<msg;
        emit tryRegist(msg);
    }
}

bool RegistDialog::checkIDCard() {
    QString cardNum;
    cardNum = ui->lineEditID->text();
    if (cardNum.length() != 18) return false;
    //加权因子
    int weight[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    //校验码表
    char validateCodes[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    int sum = 0;
    for(int i = 0; i < 17; i++) {
        sum = sum + (cardNum.at(i).digitValue()) * weight[i];
    }
    int mod = sum % 11;
    if (mod == 2) {
        return validateCodes[mod] == 'x' || validateCodes[mod] == 'X';
    }
    return validateCodes[mod] == cardNum[17];
}

bool RegistDialog::checkPhoneNum()
{
    QString phoneNum = ui->lineEditPhone->text();
    if(phoneNum.length() == 11)
    {
        for(auto e:phoneNum)
            if(e>'9'||e<'0')
                return false;
        return true;
    }
    else
        return false;
}

bool RegistDialog::checkPassword()
{
    if(ui->lineEditPwd->text().isEmpty())
        return false;
    else return ui->lineEditPwd->text()==ui->lineEditPwd2->text();
}

bool RegistDialog::checkInput()
{
    if(checkIDCard()==false)
        QMessageBox::warning(this,"注册账号","请输入合法的身份证号");
    else if(ui->lineEditName->text().isEmpty())
    {
        QMessageBox::warning(this,"注册账号","请输入姓名");
        ui->lineEditName->setStyleSheet("background-color: pink;");
    }
    else if(checkPhoneNum()==false)
        QMessageBox::warning(this,"注册账号","请输入合法的电话号码");
    else if(ui->lineEditPwd->text().isEmpty())
        QMessageBox::warning(this,"注册账号","请输入密码");
    else if(checkPassword()==false)
        QMessageBox::warning(this,"注册账号","输入密码不一致");
    else if(ui->lineEditQuestion->text().isEmpty())
    {
        QMessageBox::warning(this,"注册账号","请输入密保问题");
        ui->lineEditQuestion->setStyleSheet("background-color: pink;");
    }
    else if(ui->lineEditAnswer->text().isEmpty())
    {
        QMessageBox::warning(this,"注册账号","请输入密保答案");
        ui->lineEditAnswer->setStyleSheet("background-color: pink;");
    }
    else return true;
    return false;
}

void RegistDialog::handleRegistSuccess()
{
    QMessageBox::information(this,"注册账号","账号注册成功！");
    accept();
}

void RegistDialog::handleRegistDefeat(const QString &msg)
{
    QMessageBox::information(this,"注册账号",msg);
}

void RegistDialog::finishedIDEdit()
{
    if(checkIDCard()==false)
        ui->lineEditID->setStyleSheet("background-color: pink;");
}

void RegistDialog::startIDEdit()
{
    ui->lineEditID->setStyleSheet("background-color: white");
}

void RegistDialog::finishedPwdEdit()
{
    if(checkPassword()==false)
    {
        ui->lineEditPwd->setStyleSheet("background-color: pink;");
        ui->lineEditPwd2->setStyleSheet("background-color: pink;");
    }
}

void RegistDialog::startPwdEdit()
{
    ui->lineEditPwd->setStyleSheet("background-color: white;");
    ui->lineEditPwd2->setStyleSheet("background-color: white;");
}

void RegistDialog::finishedPhoneEdit()
{
    if(checkPhoneNum()==false)
    {
        ui->lineEditPhone->setStyleSheet("background-color: pink;");
    }
}

void RegistDialog::startPhoneEdit()
{
    ui->lineEditPhone->setStyleSheet("background-color: white;");
}

void RegistDialog::startNameEdit()
{
    ui->lineEditName->setStyleSheet("background-color: white;");
}

void RegistDialog::startQuestionEdit()
{
    ui->lineEditQuestion->setStyleSheet("background-color: white;");
}

void RegistDialog::startAnswerEdit()
{
    ui->lineEditAnswer->setStyleSheet("background-color: white;");
}


