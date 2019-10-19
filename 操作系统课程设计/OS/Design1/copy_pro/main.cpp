#include "mycopy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyCopy w;
    w.show();

    return a.exec();
}
