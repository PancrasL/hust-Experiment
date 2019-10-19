#include "addnewemployee.h"
#include "ui_addnewemployee.h"
#include "dbconnector.h"
#include <QMessageBox>
extern DBConnector dbConnector;
AddNewEmployee::AddNewEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewEmployee)
{
    ui->setupUi(this);
    ui->E_ENTRYDATE->setDate(QDate::currentDate());
}

AddNewEmployee::~AddNewEmployee()
{
    delete ui;
}

void AddNewEmployee::updateDate()
{
    ui->E_ENTRYDATE->setDate(QDate::currentDate());
}

void AddNewEmployee::on_confirm_clicked()
{
    if(ui->E_ID->text().isEmpty()
            || ui->E_PASSWORD->text().isEmpty()
            || ui->E_NAME->text().isEmpty()
            || ui->E_PHONE->text().isEmpty())
    {
        QMessageBox::information(this, "插入失败", "请将信息填写完整");
        return;
    }
    employee.E_ID = ui->E_ID->text();
    employee.E_PASSWORD = ui->E_PASSWORD->text();
    employee.E_NAME = ui->E_NAME->text();
    employee.E_SEX = ui->E_SEX->currentText();
    employee.E_PHONE_NUM = ui->E_PHONE->text();
    employee.E_ENTRYDATE = ui->E_ENTRYDATE->text();
    employee.E_TYPE = ui->E_TYPE->currentText();
    int status = dbConnector.insertEmployeeInfo(employee);
    switch (status) {
    case INSERT_SUCCESS:
        QMessageBox::information(this, "插入成功", "员工信息插入成功!");
        employee.E_ID.clear();
        employee.E_PASSWORD.clear();
        employee.E_NAME.clear();
        employee.E_PHONE_NUM.clear();
        break;
    case INSERT_DEFEAT:
        QMessageBox::information(this, "插入失败", "员工信息插入失败!");
        break;
    case INSERT_ALREADY_EXIST:
        QMessageBox::information(this, "插入失败", "员工编号号已被占用!");
        break;
    }
}
