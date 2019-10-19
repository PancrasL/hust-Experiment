#include "findpwddialog.h"
#include "ui_findpwddialog.h"
#include <QDebug>
#include <QMessageBox>
FindPwdDialog::FindPwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPwdDialog)
{
    ui->setupUi(this);
}

FindPwdDialog::~FindPwdDialog()
{
    delete ui;
    qDebug()<<"FindPwdDialog's destructor";
}

void FindPwdDialog::handleFindPwdSuccess()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEditID->clear();
    ui->lineEditName->clear();
    ui->lineEditPhone->clear();
    ui->lineEditAnswer->clear();
    ui->lineEditNewPwd->clear();
    ui->lineEditQuestion->clear();
    QMessageBox::information(this, "找回密码", "密码已修改，请重新登陆！");
    this->close();
}

void FindPwdDialog::handleFindPwdDefeat()
{
    QMessageBox::information(this, "找回密码", "密保问题答案错误，请检查输入");
}

void FindPwdDialog::handleGetQuestion(bool success, const QString &msg)
{
    if(success == true)
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->lineEditQuestion->setText(msg);
    }
    else
    {
        QMessageBox::information(this, "找回密码", "未查询到账号信息，请重新检查输入信息是否有误");
    }
}


void FindPwdDialog::on_pushBtnNext_clicked()
{
    QString msg;
    msg.append(ui->lineEditID->text());
    msg.push_back('\n');
    msg.append(ui->lineEditPhone->text());
    msg.push_back('\n');
    msg.append(ui->lineEditName->text());
    emit tryGetQuestion(msg);
}

void FindPwdDialog::on_pushBtnConfirm_clicked()
{
    QString msg;
    msg.append(ui->lineEditID->text());
    msg.push_back('\n');
    msg.append(ui->lineEditAnswer->text());
    msg.push_back('\n');
    msg.append(ui->lineEditNewPwd->text());
    emit tryFindPwd(msg);
}

void FindPwdDialog::on_pushBtnLast_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

bool FindPwdDialog::checkIDCard() {
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

bool FindPwdDialog::checkPhoneNum()
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
