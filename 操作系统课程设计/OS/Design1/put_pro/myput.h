#ifndef MYPUT_H
#define MYPUT_H

#include <QWidget>
#include <QTextBrowser>
namespace Ui {
class MyPut;
}

class MyPut : public QWidget
{
    Q_OBJECT

public:
    explicit MyPut(QWidget *parent = nullptr);
    ~MyPut();
    static QTextBrowser *pText;
    static QTextBrowser *pText1;

private:
    Ui::MyPut *ui;
};

#endif // MYPUT_H
