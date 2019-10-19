#ifndef ADDNEWCAR_H
#define ADDNEWCAR_H

#include "myStruct.h"
#include <QDialog>

namespace Ui {
class AddNewCar;
}

class AddNewCar : public QDialog
{
    Q_OBJECT

public:
    CarInfo car;
    explicit AddNewCar(QWidget *parent = nullptr);
    ~AddNewCar();
    void updateDate();
private slots:
    void on_confirm_clicked();

private:
    Ui::AddNewCar *ui;
};

#endif // ADDNEWCAR_H
