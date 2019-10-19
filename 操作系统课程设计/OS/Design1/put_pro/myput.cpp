#include "myput.h"
#include "ui_myput.h"
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
QTextBrowser *MyPut::pText;
QTextBrowser *MyPut::pText1;
void *put_msg(void *arg);
MyPut::MyPut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyPut)
{
    ui->setupUi(this);
    pText=ui->textBrowser;
    pText1=ui->textBrowser_2;
    pthread_t t;
    pthread_create(&t,nullptr,put_msg,nullptr);
}

MyPut::~MyPut()
{
    delete ui;
}
void *put_msg(void *arg)
{
    FILE *fp=fopen("./dest.txt","wb");
    if(fp) qDebug()<<"./dest.txt"<<"打开成功";
    /*使用相同的id获取信号灯组和缓冲区组*/
    int shmid1 = shmget(112, sizeof(BUFF), IPC_CREAT | 0666);
    int semid1 = semget(223, 2, IPC_CREAT | 0666);//缓冲区T相关
    /*从缓冲区中读取信息存放到文件中*/
    BUFF *pbuf1 = (BUFF *)shmat(shmid1, nullptr, SHM_R);//缓冲区T
    BUFF temp;
    while (true)
    {
        P(semid1,1);        //请求T满缓冲区
        QDateTime time =QDateTime::currentDateTime();
        QString current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":开始从缓冲区T中取出数据";
        MyPut::pText->append(current_date);
        sleep(1);
        temp=*pbuf1;
        V(semid1,0);        //增加T空缓冲区
        time=QDateTime::currentDateTime();
        current_date =time.toString("hh:mm:ss.zzz");
        current_date+=":成功从缓冲区T中取出数据";
        MyPut::pText->append(current_date);
        QString s=temp.data;
        MyPut::pText->append(s);
        MyPut::pText1->append(temp.data);

        fprintf(fp,"%s",temp.data);
        if(temp.data[0]==0) break;//到达文件尾，跳出循环
    }
    fclose(fp);
    shmdt(pbuf1); //断开共享内存连接
    MyPut::pText->append("put完成");
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
