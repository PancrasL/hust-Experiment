#include "repairmainwindow.h"
#include "ui_repairmainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
RepairMainWindow::RepairMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RepairMainWindow)
{
    ui->setupUi(this);
}

RepairMainWindow::~RepairMainWindow()
{
    delete ui;
}

void RepairMainWindow::closeEvent(QCloseEvent *event)
{
    int status = QMessageBox::information(nullptr, "退出程序", "确认退出程序？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(status == QMessageBox::Yes)
    {
        emit quitApp();
    }
    else
        event->ignore();
}
