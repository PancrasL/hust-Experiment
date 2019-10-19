#include "mytaskmanager.h"
#include "ui_mytaskmanager.h"
#include "sys_info.h"
#include "cpu_info.h"
#include "process_info.h"
#include "mem_info.h"
#include "struct_info.h"
#include "qcustomplot.h"
#include <QTimer>
#include <vector>
#include <QString>
#include <QVector>
#include <algorithm>
#include <string>
#include <math.h>
#include <QMessageBox>
#include <QInputDialog>
using namespace std;
char op(char ch)
{
    return static_cast<char>(tolower(ch));
}
MyTaskManager::MyTaskManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyTaskManager)
{
    ui->setupUi(this);
    sort_type=1;
    Lcpu=QVector<double>(120,0);
    Lmem=QVector<double>(120,0);
    Lswap=QVector<double>(120,0);
    for(int i=0;i<120;i++)
        X.push_back(i);
    init_graph();
    display_process_info();
    display_status_bar();
    display_sys_info();
    QTimer *timer=new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_update_info()));
}
void MyTaskManager::timer_update_info()
{
    display_status_bar();
    int index=ui->tabWidget->currentIndex();
    display_sys_info();
    display_tabWidget(index);
}

void MyTaskManager::display_tabWidget(int index)
{
    int status=0;
    switch (index) {
    case 0:
        if(status!=0)//状态切换了
        {
            status=0;

        }
        break;
    case 1:
        if(status!=1)
        {
            status=1;

        }
        break;
    case 2:
        if(status!=2)
        {
            draw_graph(ui->widget_cpu,Lcpu);
            status=2;

        }
        break;
    case 3:
        if(status!=3)
        {
            draw_graph(ui->widget_mem,Lmem);
            status=3;

        }
        break;
    case 4:
        if(status!=4)
        {
            draw_graph(ui->widget_swap,Lswap);
            status=4;

        }
        break;
    }
}

void MyTaskManager::display_sys_info()
{
    /*时间、系统信息*/
    ui->label_host_val->setText(get_hostname());
    ui->label_edition_val->setText(get_os_edition());
    ui->label_start_val->setText(get_start_time());
    ui->label_run_val->setText(get_run_time());
    /*CPU信息*/
    std::vector<QString> v=get_processor();
    ui->label_CPU_val->setText(v[0]);
    ui->label_cache_val->setText(v[1]);
    ui->label_cores_val->setText(v[2]);
}
void MyTaskManager::display_process_info()
{
    int num=get_pid_info(this->v);//num为总进程数，获取的进程保存在向量v中
    switch (abs(sort_type)) {//sort_type<0,降序;sort_type>0,生序
    case 1://按名称排序
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO a, PROC_INFO b) -> bool
            {
                string s1=a.name;string s2=b.name;
                s1[0]=static_cast<char>(tolower(s1[0]));
                s2[0]=static_cast<char>(tolower(s2[0]));
                return s1>s2;
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO a, PROC_INFO b) -> bool
            {
                string s1=a.name;string s2=b.name;
                s1[0]=static_cast<char>(tolower(s1[0]));
                s2[0]=static_cast<char>(tolower(s2[0]));
                return s1<s2;
            });
        }
        break;
    case 2://pid
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.pid)>stoi(b.pid);
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.pid)<stoi(b.pid);
            });
        }
        break;
    case 3://ppid
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.ppid)>stoi(b.ppid);
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.ppid)<stoi(b.ppid);
            });
        }
        break;
    case 4://按类别排序
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return a.taskState>b.taskState;
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return a.taskState<b.taskState;
            });
        }
        break;
    case 5://按优先级排序
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.priority)>stoi(b.priority);
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.priority)<stoi(b.priority);
            });
        }
        break;
    case 6://按内存占用排序
        if(sort_type<0){
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.rss)>stoi(b.rss);
            });
        }
        else{
            sort(v.begin(),v.end(),[](PROC_INFO &a, PROC_INFO &b) -> bool
            {
                return stoi(a.rss)<stoi(b.rss);
            });
        }
        break;
    default:break;
    }
    show_proc(*(ui->listWidget),this->v);
    ui->label_process_num_val->setNum(num);
}

void MyTaskManager::display_status_bar()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString s =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
    ui->label_cur_date_time_val->setText(s);
    double num;
    int total;
    //获取CPU利用率
    s=get_cpu_usage(num);
    ui->label_cpu_use_val->setText(s);
    ui->label_cpu_use_1->setText(s);
    int usage=static_cast<int>(num);
    ui->progressBar_cpu_use->setValue(usage);;
    Lcpu.pop_front();
    Lcpu.push_back(usage);
    //获取内存利用率和内存容量
    s=get_mem_usage(num,total);
    ui->label_mem_total_val->setNum(total);
    ui->label_mem_use_val->setText(s);
    ui->label_mem_use_1->setText(s);
    usage=static_cast<int>(num);
    ui->progressBar_mem_use->setValue(usage);
    Lmem.pop_front();Lmem.push_back(usage);
    //获取交换分区利用率
    s=get_swap_usage(num,total);
    ui->label_swap_use->setText(s);
    usage=static_cast<int>(num);
    ui->progressBar_swap_use->setValue(usage);
    Lswap.pop_front();Lswap.push_back(usage);
}

void MyTaskManager::draw_graph(QCustomPlot *pWidget, QVector<double> &L)
{
    pWidget->graph(0)->setData(X,L,true);
    pWidget->replot();
}

void MyTaskManager::init_graph()
{

    ui->widget_cpu->addGraph();
    ui->widget_cpu->graph(0)->setPen(QPen(Qt::blue));
    ui->widget_cpu->graph(0)->setBrush(QBrush(Qt::yellow));
    ui->widget_cpu->axisRect()->setupFullAxesBox();
    ui->widget_cpu->xAxis->setRange(0,120);
    ui->widget_cpu->xAxis->setLabel("时间");
    ui->widget_cpu->yAxis->setLabel("利用率");
    ui->widget_cpu->graph(0)->setName("CPU利用率");
    ui->widget_cpu->yAxis->setRange(0,100);

    ui->widget_mem->addGraph();
    ui->widget_mem->graph(0)->setPen(QPen(Qt::red));
    ui->widget_mem->graph(0)->setBrush(QBrush(Qt::yellow));
    ui->widget_mem->axisRect()->setupFullAxesBox();
    ui->widget_mem->xAxis->setRange(0,120);
    ui->widget_mem->xAxis->setLabel("时间");
    ui->widget_mem->yAxis->setLabel("利用率");
    ui->widget_mem->graph(0)->setName("Mem利用率");
    ui->widget_mem->yAxis->setRange(0,100);

    ui->widget_swap->addGraph();
    ui->widget_swap->graph(0)->setPen(QPen(Qt::yellow));
    ui->widget_swap->graph(0)->setBrush(QBrush(Qt::yellow));
    ui->widget_swap->axisRect()->setupFullAxesBox();
    ui->widget_swap->xAxis->setRange(0,120);
    ui->widget_swap->xAxis->setLabel("时间");
    ui->widget_swap->yAxis->setLabel("利用率");
    ui->widget_swap->graph(0)->setName("Swap利用率");
    ui->widget_swap->yAxis->setRange(0,100);
}

MyTaskManager::~MyTaskManager()
{
    delete ui;
}


void MyTaskManager::on_pushButton_sort_by_name_clicked()
{
    static int op=-1;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_sort_by_pid_clicked()
{
    static int op=-2;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_sort_by_ppid_clicked()
{
    static int op=-3;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_sort_by_class_2_clicked()
{
    static int op=-4;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_sort_by_prio_clicked()
{
    static int op=-5;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_sort_by_mem_clicked()
{
    static int op=6;
    op*=-1;
    this->sort_type=op;
    display_process_info();
}

void MyTaskManager::on_pushButton_search_proc_clicked()
{
    display_process_info();
    QString s=ui->lineEdit->text();
    if(get_proc_pid(*(ui->listWidget),s)<0)
        ui->lineEdit->setText("未找到");
}

void MyTaskManager::on_pushButton_end_process_clicked()
{
    QListWidgetItem *pIt=ui->listWidget->currentItem();
    if(pIt==nullptr)//未选中任何item
        return;
    istringstream is(pIt->text().toStdString());
    string temp;int pid;
    is>>temp>>pid;
    kill_proc(pid);
    display_process_info();
    temp="进程\""+temp+"\"已杀死";
    QMessageBox *msg=new QMessageBox(this);
    msg->setWindowTitle("确认");
    msg->setText(QString::fromStdString(temp));
    msg->show();
}

void MyTaskManager::on_action_kill_proc_triggered()
{
    display_process_info();//更新进程列表
    bool ok;
    QString string=QInputDialog::getText(this,"结束进程","请输入进程名或进程pid",QLineEdit::Normal,"name|pid",&ok);
    if(ok)//用户点击了确认
    {
        int pid;
        pid=get_proc_pid(*(ui->listWidget),string);
        QMessageBox *msg=new QMessageBox(this);
        msg->setWindowTitle(QString(pid));
        if(pid>0)
        {
            kill_proc(pid);
            display_process_info();
            msg->setText("进程已杀死");
        }
        else msg->setText("进程不存在");

        msg->show();
    }
}


void MyTaskManager::on_action_shutdown_triggered()
{
    system("poweroff");
}
void MyTaskManager::on_action_reboot_triggered()
{
    system("reboot");
}
void MyTaskManager::on_action_new_proc_triggered()
{
    bool ok;
    QString s=QInputDialog::getText(this,"新的进程","",QLineEdit::Normal,"",&ok);
    if(ok)//用户点击了确认
    {
        QProcess *pro=new QProcess;
        pro->start(s);
    }
}
