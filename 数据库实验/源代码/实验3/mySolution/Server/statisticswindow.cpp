#include "statisticswindow.h"
#include "ui_statisticswindow.h"
#include "dbconnector.h"
extern DBConnector dbConnector;
StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
    chart = nullptr;
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::on_pushButtonYear_clicked()
{
    delete chart;
    chart = new TableWidget;
    QStringList categories;
    QVector<Income> incomeVec = dbConnector.getYearStatistics();
    for(auto e : incomeVec)
        categories<< QString::number(e.year);
    chart->setCatgories(categories);

    CustomTableModel *model = new CustomTableModel;
    model->initModel(incomeVec, "year");
    chart->initUI(model);
    chart->show();
}

void StatisticsWindow::on_pushButtonSeason_clicked()
{
    delete chart;
    chart = new TableWidget;
    QStringList categories;
    QVector<Income> incomeVec = dbConnector.getSeasonStatistics(ui->dateEditSeason->date().year());
    for(auto e : incomeVec)
        categories<< QString("%1年%2季度").arg(e.year).arg(e.season);
    chart->setCatgories(categories);

    CustomTableModel *model = new CustomTableModel;
    model->initModel(incomeVec, "season");
    chart->initUI(model);
    chart->show();
}

void StatisticsWindow::on_pushButtonMonth_clicked()
{
    delete chart;
    chart = new TableWidget;

    QStringList categories;
    QVector<Income> incomeVec = dbConnector.getMonthStatistics(ui->dateEditMonth->date().year());
    for(auto e : incomeVec)
    {
        categories<< e.date;
        qDebug()<<e.date;
    }
    chart->setCatgories(categories);
    CustomTableModel *model = new CustomTableModel;
    model->initModel(incomeVec , "month");
    chart->initUI(model);
    chart->show();
}

void StatisticsWindow::on_pushButtonDay_clicked()
{
    delete chart;
    chart = new TableWidget;

    QStringList categories;
    QVector<Income> incomeVec = dbConnector.getDayStatistics(ui->dateEditDay->date().year(), ui->dateEditDay->date().month());
    for(auto e : incomeVec)
        categories<< e.date;
    chart->setCatgories(categories);
    CustomTableModel *model = new CustomTableModel;
    model->initModel(incomeVec , "day");
    chart->initUI(model);
    chart->show();
}
