#include "rentdialog.h"
#include "ui_rentdialog.h"
RentDialog::RentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RentDialog)
{
    ui->setupUi(this);
}

void RentDialog::initUI(const QVector<QString> &info)
{
    ui->labelCID->setText(info[0]);
    ui->labelCTYPE->setText(info[1]);
    ui->labelCBRAND->setText(info[2]);
    ui->labelDeposit->setText(info[3]);
    ui->labelPrice->setText(info[4]);
    ui->labelRealDeposit->setText(info[5]);
    ui->labelRealPrice->setText(info[6]);
    ui->labelRentalDay->setText(info[7]);
}

RentDialog::~RentDialog()
{
    delete ui;
}

void RentDialog::on_pushButton_clicked()
{
    accept();
}
