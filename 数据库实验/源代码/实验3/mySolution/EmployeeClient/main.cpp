#include "myapplication.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    MyApplication application;
    if(application.logindlg.exec() == QDialog::Accepted)
    {
        application.sellwindow.initUI(application.logindlg.isSellEmployee);
        application.sellwindow.show();
        application.sellwindow.EID = application.logindlg.getEID();
    }
    return a.exec();
}
