#include "mycopy.h"
#include "ui_mycopy.h"
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
QTextBrowser *MyCopy::pText;
QTextBrowser *MyCopy::pText1;
void *cpy_msg(void *arg);
MyCopy::MyCopy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyCopy)
{
    ui->setupUi(this);
    MyCopy::pText=ui->textBrowser;
    MyCopy::pText1=ui->textBrowser_2;
    pthread_t t;
    pthread_create(&t,nullptr,cpy_msg,nullptr);
}
void *cpy_msg(void *arg)
{
    /*使用相同的id获取信号灯组和缓冲区组*/
    int shmid = shmget(111, sizeof(BUFF), IPC_CREAT | 0666);
    int semid = semget(222, 2, IPC_CREAT | 0666);//缓冲区S相关
    int shmid1 = shmget(112, sizeof(BUFF), IPC_CREAT | 0666);
    int semid1 = semget(223, 2, IPC_CREAT | 0666);//缓冲区T相关
    /*从缓冲区中读取信息存放到文件中*/
    BUFF *pbuf = (BUFF *)shmat(shmid, nullptr, SHM_R);//缓冲区S
    BUFF *pbuf1 = (BUFF *)shmat(shmid1, nullptr, SHM_R);//缓冲区T
    BUFF temp;
    while (true)
    {
        P(semid, 1);          //请求S满缓冲区
        QDateTime time =QDateTime::currentDateTime();
        QString current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":开始从缓冲区S中取出数据";
        MyCopy::pText->append(current_date);
        sleep(1);
        temp=*pbuf;           //从S中取出数据
        V(semid, 0);          //增加S空缓冲区个数

        time=QDateTime::currentDateTime();
        current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":成功从缓冲区S中取出数据";
        MyCopy::pText->append(current_date);
        QString s=temp.data;
        MyCopy::pText->append(s);

        P(semid1,0);        //请求T空缓冲区
        time=QDateTime::currentDateTime();
        current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":开始将数据存放到缓冲区T中";
        MyCopy::pText->append(current_date);
        sleep(1);
        *pbuf1=temp;        //存放数据到T
        V(semid1,1);        //增加T满缓冲区
        time=QDateTime::currentDateTime();
        current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":成功将数据存放到缓冲区T";
        MyCopy::pText->append(current_date);
        MyCopy::pText->append(s);
        MyCopy::pText1->append(temp.data);
    }
    shmdt(pbuf); //断开共享内存连接
    shmdt(pbuf1);
    return nullptr;
}
MyCopy::~MyCopy()
{
    delete ui;
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
