#include "addnewcar.h"
#include "ui_addnewcar.h"
#include "dbconnector.h"
#include <QMessageBox>
extern DBConnector dbConnector;
AddNewCar::AddNewCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewCar)
{
    ui->setupUi(this);
}

AddNewCar::~AddNewCar()
{
    delete ui;
}

void AddNewCar::updateDate()
{
    ui->C_BUYTIME->setDateTime(QDateTime::currentDateTime());
}

void AddNewCar::on_confirm_clicked()
{
    if(ui->C_ID->text().isEmpty()
            || ui->C_BRAND->text().isEmpty())
    {
        QMessageBox::information(this, "插入失败", "请将信息填写完整");
        return;
    }
    car.C_ID = ui->C_ID->text();
    car.C_TYPE = ui->C_TYPE->currentText();
    car.C_BRAND = ui->C_BRAND->text();
    car.C_BUYTIME = ui->C_BUYTIME->text();
    car.C_DEPOSIT = ui->C_DEPOSIT->text();
    car.C_PRICE = ui->C_PRICE->text();
    car.C_TIMEOUT_PRICE = ui->C_TIMEOUT_PRICE->text();
    car.C_STATUS = ui->C_STATUS->currentText();

    int status = dbConnector.insertCarInfo(car);
    switch (status) {
    case INSERT_SUCCESS:
        QMessageBox::information(this, "插入成功", "车辆信息插入成功!");
        car.C_ID.clear();
        break;
    case INSERT_DEFEAT:
        QMessageBox::information(this, "插入失败", "车辆信息插入失败!");
        break;
    case INSERT_ALREADY_EXIST:
        QMessageBox::information(this, "插入失败", "车牌号已被占用!");
        break;
    }
}
