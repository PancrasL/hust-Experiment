#include "myget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGet w;
    w.show();

    return a.exec();
}
