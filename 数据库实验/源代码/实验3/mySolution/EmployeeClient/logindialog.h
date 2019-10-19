#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    bool isSellEmployee;
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getEID();
    ~LoginDialog();
private:
    Ui::LoginDialog *ui;
private slots:
    void on_pushBtnLogin_clicked();
    void handleLoginReply(bool success, bool isSellEmployee);

protected:
    void closeEvent(QCloseEvent *event);


signals:

    void tryLogin(const QString &msg);

    //按下叉号时发射的信号，被myApplication捕捉，用于退出程序
    void quitApp();
};

#endif // LOGINDIALOG_H
