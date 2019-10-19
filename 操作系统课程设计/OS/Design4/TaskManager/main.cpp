#include "mytaskmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTaskManager w;
    w.show();

    return a.exec();
}
