#ifndef ADDNEWEMPLOYEE_H
#define ADDNEWEMPLOYEE_H

#include <QDialog>
#include "myStruct.h"
namespace Ui {
class AddNewEmployee;
}

class AddNewEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEmployee(QWidget *parent = nullptr);
    ~AddNewEmployee();
    void updateDate();
private slots:
    void on_confirm_clicked();

private:
    Ui::AddNewEmployee *ui;
    EmployeeInfo employee;
};

#endif // ADDNEWEMPLOYEE_H
