#ifndef VIPDISCOUNTDIALOG_H
#define VIPDISCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class VipDiscountDialog;
}

class VipDiscountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VipDiscountDialog(QWidget *parent = nullptr);
    ~VipDiscountDialog();
    void showCurrentDiscount();


private slots:
    void on_pushButtonDeposit_clicked();

    void on_pushButtonPrice_clicked();

private:
    Ui::VipDiscountDialog *ui;
    void setDepositDiscount(QVector<double> &deposit);
    void setPriceDiscount(QVector<double> &price);
};

#endif // VIPDISCOUNTDIALOG_H
