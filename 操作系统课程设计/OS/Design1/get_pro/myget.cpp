#include "myget.h"
#include "ui_myget.h"
#include "sem.h"
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <QTextBrowser>
 #include <pthread.h>
#include <QString>
#include <QDebug>
#include <unistd.h>
#include <QDateTime>
void *get_msg(void *arg);
QTextBrowser *MyGet::pText;
QTextBrowser *MyGet::pText1;
MyGet::MyGet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyGet)
{
    ui->setupUi(this);
    MyGet::pText=ui->textBrowser;
    MyGet::pText1=ui->textBrowser_2;
    pthread_t t;
    pthread_create(&t,nullptr,get_msg,nullptr);
}

MyGet::~MyGet()
{
    delete ui;
}
void *get_msg(void *arg)
{
    const char *filename="./test.txt";
    /*使用相同的id获取信号灯组和缓冲区组*/
    int shmid = shmget(111, sizeof(BUFF), IPC_CREAT | 0666);
    int semid = semget(222, 2, IPC_CREAT | 0666);
    /*从缓冲区中读取信息存放到文件中*/
    BUFF *pbuf = (BUFF *)shmat(shmid, nullptr, SHM_R);
    FILE *fp = fopen(filename, "rb");
    if (fp == nullptr)
    {
        qDebug()<<filename<<"打开失败\n";
        return nullptr;
    } //文件打开失败
    qDebug()<<filename<<"打开成功\n";
    BUFF temp;
    while (true)
    {
        char * end=fgets(temp.data,sizeof(temp.data),fp);
        if(end==nullptr) temp.data[0]=0;
        P(semid, 0);          //请求空缓冲区
        QDateTime time =QDateTime::currentDateTime();
        QString current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":开始拷贝数据到缓冲区S";
        MyGet::pText->append(current_date);
        sleep(2);           //暂停3s
        *pbuf = temp;         //存放数据到缓冲区中
        V(semid, 1);          //增加满缓冲区个数
        time=QDateTime::currentDateTime();
        current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":数据已拷贝到缓冲区S";
        MyGet::pText->append(current_date);
        QString s=temp.data;
        MyGet::pText->append(s);
        MyGet::pText1->append(temp.data);
        if(end==nullptr) break;
    }
    fclose(fp);  //关闭文件
    shmdt(pbuf); //断开共享内存连接
    MyGet::pText->append("get完成");
    sleep(1000);
    return nullptr;
}

void P(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num = static_cast<unsigned short>(index);
    sem.sem_op = -1;
    sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);//1:表示执行命令的个数
    return;
}
void V(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num = static_cast<unsigned short>(index);
    sem.sem_op =  1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}
