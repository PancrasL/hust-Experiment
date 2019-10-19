#ifndef INFO_H
#define INFO_H
/*
 * 获取系统信息和设备信息
*/
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QDebug>
#include <QTime>
QString get_hostname()//获取主机名，使用了/proc/sys/kernel/hostname
{
    FILE* fp;
    char host[256];
    fp=fopen("/proc/sys/kernel/hostname","r");
    if(fp==nullptr)//文件打开失败
    {
        return QString("");
    }
    fgets(host,sizeof(host),fp);
    host[strlen(host)-1]=0;//去除换行符
    fclose(fp);
    return QString(host);
}
QString get_start_time()//获取启动时间，使用了/proc/uptime
{
    FILE* fp;
    double runTime;
    char line[32];
    fp=fopen("/proc/uptime","r");
    if(fp==nullptr)
    {
        return QString("");
    }
    fgets(line,sizeof(line),fp);
    sscanf(line,"%lf",&runTime);
    double curtime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    curtime-=runTime;//计算出启动时间
    QDateTime dt = QDateTime::fromTime_t(static_cast<unsigned>(curtime));
    QString s = dt.toString(Qt::SystemLocaleLongDate);
    fclose(fp);
    return s;
}
QString get_run_time()//获取运行时间，使用了/proc/uptime
{
    FILE* fp;
    double runTime;
    char line[32];
    fp=fopen("/proc/uptime","r");
    if(fp==nullptr)
    {
        return QString("");
    }
    fgets(line,sizeof(line),fp);
    sscanf(line,"%lf",&runTime);
    int time,hours,minutes,seconds;
    time=static_cast<int>(runTime);
    hours=time/3600;time%=3600;//计算出小时
    minutes=time/60;time%=60;//计算出分钟
    seconds=time;//计算出秒
    QString s=QString::number(hours)+":"+QString::number(minutes)+":"+QString::number(seconds);
    fclose(fp);
    return s;
}
QString get_os_edition()//获取系统版本号，/proc/sys/kernel/ostype, /proc/sys/kernel/osrelease
{

    char buff1[16],buff2[16];
    FILE *fp1,*fp2;
    fp1=fopen("/proc/sys/kernel/ostype","r");
    fp2=fopen("/proc/sys/kernel/osrelease","r");
    if(fp1==nullptr||fp2==nullptr)
        return QString("");
    fgets(buff1,sizeof(buff1),fp1);
    fgets(buff2,sizeof(buff2),fp2);
    buff1[strlen(buff1)-1]=0;buff2[strlen(buff2)-1]=0;
    fclose(fp1);
    fclose(fp2);
    return QString(buff1)+" "+QString(buff2);
}

#endif // INFO_Hs
