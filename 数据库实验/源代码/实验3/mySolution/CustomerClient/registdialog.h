#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

#include <QDialog>
class UserInfo;
namespace Ui {
class RegistDialog;
}

class RegistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistDialog(QWidget *parent = nullptr);
    ~RegistDialog();
private slots:
    void on_registBtn_clicked();
    void handleRegistSuccess();
    void handleRegistDefeat(const QString &msg);

    void finishedIDEdit();
    void startIDEdit();
    void finishedPwdEdit();
    void startPwdEdit();
    void finishedPhoneEdit();
    void startPhoneEdit();
    void startNameEdit();
    void startQuestionEdit();
    void startAnswerEdit();
private:
    Ui::RegistDialog *ui;
    bool checkIDCard();         //检测身份证号的合法性
    bool checkPhoneNum();       //检测电话号码的合法性
    bool checkPassword();       //检测密码的合法性
    bool checkInput();          //检测所有输入的合法性

signals:
    void tryRegist(const QString &msg);
};

#endif // REGISTDIALOG_H
