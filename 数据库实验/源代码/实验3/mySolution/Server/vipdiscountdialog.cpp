#include "vipdiscountdialog.h"
#include "ui_vipdiscountdialog.h"
#include "uclientservice.h"
#include <QMessageBox>
VipDiscountDialog::VipDiscountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VipDiscountDialog)
{
    ui->setupUi(this);
    showCurrentDiscount();
}

VipDiscountDialog::~VipDiscountDialog()
{
    delete ui;
}

void VipDiscountDialog::showCurrentDiscount()
{
    QVector<double> deposit = UClient::getVipDepositDiscount();
    QVector<double> price = UClient::getVipPriceDiscount();
    ui->DepVip0->setValue(deposit[0]);
    ui->DepVip1->setValue(deposit[1]);
    ui->DepVip2->setValue(deposit[2]);
    ui->DepVip3->setValue(deposit[3]);
    ui->DepVip4->setValue(deposit[4]);
    ui->DepVip5->setValue(deposit[5]);

    ui->PriVip0->setValue(price[0]);
    ui->PriVip1->setValue(price[1]);
    ui->PriVip2->setValue(price[2]);
    ui->PriVip3->setValue(price[3]);
    ui->PriVip4->setValue(price[4]);
    ui->PriVip5->setValue(price[5]);
}

void VipDiscountDialog::setDepositDiscount(QVector<double> &deposit)
{
    deposit[0] = ui->DepVip0->value();
    deposit[1] = ui->DepVip1->value();
    deposit[2] = ui->DepVip2->value();
    deposit[3] = ui->DepVip3->value();
    deposit[4] = ui->DepVip4->value();
    deposit[5] = ui->DepVip5->value();
    QMessageBox::information(this, "押金折扣", "押金折扣更改成功");
}

void VipDiscountDialog::setPriceDiscount(QVector<double> &price)
{
    price[0] = ui->PriVip0->value();
    price[1] = ui->PriVip1->value();
    price[2] = ui->PriVip2->value();
    price[3] = ui->PriVip3->value();
    price[4] = ui->PriVip4->value();
    price[5] = ui->PriVip5->value();
    QMessageBox::information(this, "价格折扣", "价格折扣更改成功");
}


void VipDiscountDialog::on_pushButtonDeposit_clicked()
{
    QVector<double> price(6);
    setDepositDiscount(price);
    UClient::setVipDepositDiscount(price);
}

void VipDiscountDialog::on_pushButtonPrice_clicked()
{
    QVector<double> deposit(6);
    setDepositDiscount(deposit);
    UClient::setVipPriceDiscount(deposit);
}
