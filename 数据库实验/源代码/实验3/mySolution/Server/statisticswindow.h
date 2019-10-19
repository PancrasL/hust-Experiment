#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QMainWindow>
#include "tablewidget.h"
namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();

private slots:
    void on_pushButtonYear_clicked();

    void on_pushButtonSeason_clicked();

    void on_pushButtonMonth_clicked();

    void on_pushButtonDay_clicked();

private:
    Ui::StatisticsWindow *ui;
    TableWidget *chart;
};

#endif // STATISTICSWINDOW_H
