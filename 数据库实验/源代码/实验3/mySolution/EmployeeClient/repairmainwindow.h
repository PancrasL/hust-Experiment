#ifndef REPAIRMAINWINDOW_H
#define REPAIRMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class RepairMainWindow;
}

class RepairMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RepairMainWindow(QWidget *parent = nullptr);
    QString EID;
    ~RepairMainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::RepairMainWindow *ui;
signals:
    void quitApp();                                     //按下叉号时退出程序
};

#endif // REPAIRMAINWINDOW_H
