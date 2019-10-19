#ifndef RENTDIALOG_H
#define RENTDIALOG_H

#include <QDialog>

namespace Ui {
class RentDialog;
}

class RentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RentDialog(QWidget *parent = nullptr);
    void initUI(const QVector<QString> &info);
    ~RentDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RentDialog *ui;
};

#endif // RENTDIALOG_H
