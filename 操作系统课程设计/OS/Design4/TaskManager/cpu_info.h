#ifndef CPU_INFO_H
#define CPU_INFO_H
/*
 * 获取CPU相关信息
*/
#include <QString>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QProcess>
using namespace std;
vector<QString> get_processor()
{
    vector<QString> v(3);
    ifstream infile;
    infile.open("/proc/cpuinfo");
    if(infile.is_open()==false)//打开文件失败
    {
        return v;
    }
    QString processor;
    QString str;
    string line;
    while (getline(infile,line)) //获取CPU型号
    {
        size_t pos;
        pos=line.find("model name");
        if(pos==string::npos)
            continue;
        pos=line.find(':',pos);
        v[0]=QString::fromStdString(line.substr(pos+2));
        break;
    }
    while(getline(infile,line))//获取cache size
    {
        size_t pos;
        pos=line.find("cache size");
        if(pos==string::npos) continue;
        pos=line.find(':',pos);
        v[1]=QString::fromStdString(line.substr(pos+2));
        break;
    }
    while(getline(infile,line))//获取CPU核心数
    {
        size_t pos;
        pos=line.find("cpu cores");
        if(pos==string::npos) continue;
        pos=line.find(':',pos);
        v[2]=QString::fromStdString(line.substr(pos+2));
        break;
    }
    infile.close();
    return v;
}
QString get_cpu_usage(double &num)//获取CPU利用率
{
        FILE *fp;
        char buf[128];
        char cpu[5];
        static long int static_all = 0;
        static long int static_idle = 0;
        long int user, nice, sys, idle, iowait, irq, softirq;

        long int all1, idle1;
        double usage;

        fp = fopen("/proc/stat", "r");
        if (fp == nullptr)
        {
            qDebug()<<"/proc/stat文件打开失败";
            return "";
        }
        fgets(buf, sizeof(buf), fp);
        sscanf(buf, "%s%ld%ld%ld%ld%ld%ld%ld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);
        all1 = user + nice + sys + idle + iowait + irq + softirq;
        idle1 = idle;
        usage = (double)(all1 - static_all - (idle1 - static_idle)) / (all1 - static_all) * 100;
        //CPU利用率 =100* (总CPU时间-空闲时间)/总CPU时间
        static_all = all1;
        static_idle = idle1;

        fclose(fp);
        char s[256];
        num=usage;
        sprintf(s,"%.2lf%%",usage);
        return QString(s);

}
#endif // CPU_INFO_H
