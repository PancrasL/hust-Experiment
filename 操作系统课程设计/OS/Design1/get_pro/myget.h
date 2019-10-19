#ifndef MYGET_H
#define MYGET_H

#include <QWidget>
#include <QTextBrowser>
namespace Ui {
class MyGet;
}

class MyGet : public QWidget
{
    Q_OBJECT

public:
    explicit MyGet(QWidget *parent = nullptr);
    static QTextBrowser *pText;
    static QTextBrowser *pText1;
    ~MyGet();

private:
    Ui::MyGet *ui;
};

#endif // MYGET_H
