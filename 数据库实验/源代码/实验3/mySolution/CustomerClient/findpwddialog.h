#ifndef FINDPWDDIALOG_H
#define FINDPWDDIALOG_H

#include <QDialog>

namespace Ui {
class FindPwdDialog;
}

class FindPwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindPwdDialog(QWidget *parent = nullptr);
    ~FindPwdDialog();
private slots:
    void handleFindPwdSuccess();
    void handleFindPwdDefeat();
    void handleGetQuestion(bool success, const QString &msg);
    void on_pushBtnNext_clicked();

    void on_pushBtnConfirm_clicked();

    void on_pushBtnLast_clicked();

private:
    Ui::FindPwdDialog *ui;
    bool checkIDCard();
    bool checkPhoneNum();
signals:
    void tryFindPwd(const QString &msg);
    void tryGetQuestion(const QString &msg);//获取密保问题
};

#endif // FINDPWDDIALOG_H
