#ifndef MYTASKMANAGER_H
#define MYTASKMANAGER_H

#include <QMainWindow>
#include <list>
#include <QVector>
#include <qcustomplot.h>
#include "struct_info.h"

namespace Ui {
class MyTaskManager;
}

class MyTaskManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyTaskManager(QWidget *parent = nullptr);
    ~MyTaskManager();

private:
    Ui::MyTaskManager *ui;
    vector<PROC_INFO> v;
    int sort_type;//进程排序，0:不排序、1：名称、2：pid、3：ppid、4：类别、5：优先级、6：内存
    QVector<double> Lcpu;//用于绘制CPU曲线
    QVector<double> Lmem;//用于绘制mem曲线
    QVector<double> Lswap;//用于绘制swap曲线
    QVector<double> X;//横坐标
    void display_tabWidget(int index);//展示tabWidget
    void display_sys_info();
    void display_process_info();
    void display_status_bar();
    void draw_graph(QCustomPlot *pWidget, QVector<double> &L);
    void init_graph();
private slots:
    void timer_update_info();//更新界面
    void on_pushButton_sort_by_name_clicked();
    void on_pushButton_sort_by_pid_clicked();
    void on_pushButton_sort_by_ppid_clicked();
    void on_pushButton_sort_by_class_2_clicked();
    void on_pushButton_sort_by_prio_clicked();
    void on_pushButton_sort_by_mem_clicked();
    void on_pushButton_search_proc_clicked();
    void on_pushButton_end_process_clicked();
    void on_action_kill_proc_triggered();
    void on_action_shutdown_triggered();
    void on_action_reboot_triggered();
    void on_action_new_proc_triggered();
};

#endif // MYTASKMANAGER_H
