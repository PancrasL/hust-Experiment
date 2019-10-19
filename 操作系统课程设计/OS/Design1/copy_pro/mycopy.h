#ifndef MYCOPY_H
#define MYCOPY_H

#include <QWidget>
#include <QTextBrowser>
namespace Ui {
class MyCopy;
}

class MyCopy : public QWidget
{
    Q_OBJECT

public:
    explicit MyCopy(QWidget *parent = nullptr);
    ~MyCopy();
    static QTextBrowser *pText;
    static QTextBrowser *pText1;
private:
    Ui::MyCopy *ui;
};

#endif // MYCOPY_H
