#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H
#include "struct_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QListWidget>
#include <QDebug>
#include <sstream>
#include <QProcess>
using namespace std;
void read_proc(PROC_INFO *pidinfo,const char *c_pid)//读取进程文件获取信息
{
    string temp,pidname;
    char filename[32];
    sprintf(filename,"/proc/%s/stat",c_pid);
    ifstream meminfo(filename);
    meminfo>>(pidinfo->pid)>>pidname>>pidinfo->taskState>>(pidinfo->ppid)>>temp>>temp;
    meminfo>>temp>>temp>>temp>>temp>>temp>>temp;
    meminfo>>temp>>temp>>temp>>temp>>temp>>(pidinfo->priority);
    meminfo>>temp>>temp>>temp>>temp>>temp>>pidinfo->rss;
    pidinfo->name=pidname.substr(1,pidname.find(')')-1);//去除括号
    meminfo.close();//关闭文件
}
int get_pid_info(vector<PROC_INFO> &v)//获取进程数据，保存到向量v中
{
    v.clear();
    DIR *dir;
    struct dirent *ptr;
    int i=0;
    if(!(dir=opendir("/proc")))
        return 0;
    while((ptr=readdir(dir))!=nullptr)//读取/proc目录下的文件
    {
        if(ptr->d_name[0]>='1' && ptr->d_name[0]<='9')//如果该文件是进程文件
        {
            v.push_back(PROC_INFO());
            read_proc(&(v.back()),ptr->d_name);
            i++;
        }
    }
    closedir(dir);
    return i;
}
void show_proc(QListWidget &L,vector<PROC_INFO> &v)//显示进程数据
{
    L.clear();
    PROC_INFO title;
    title.name="进程名";title.pid="pid";
    title.ppid="ppid";title.taskState="类别";
    title.priority="优先级";title.rss="内存占用";
    while(title.name.size()<25)
        title.name.push_back(' ');
    QString s=QString::fromStdString(title.name+"\t\t"+title.pid+"\t\t"+title.ppid+"\t"
                                     +title.taskState+"\t"+title.priority+"\t"+title.rss);
    L.addItem(s);
    for(unsigned i=0;i<v.size();i++)
    {
        while(v[i].name.size()<20)
            v[i].name.push_back(' ');
        s=QString::fromStdString(v[i].name+"\t\t"+v[i].pid+"\t\t"+v[i].ppid+"\t"
                                 +v[i].taskState+"\t"+v[i].priority+"\t"+v[i].rss+"kB");
        L.addItem(s);
    }
    return;
}
int get_proc_pid(QListWidget &L,QString s)
{
    string ss=s.toStdString();
    for(int i=0;i<L.count();i++)
    {
        string a=L.item(i)->text().toStdString();
        istringstream is(L.item(i)->text().toStdString());
        string temp;
        is>>temp;//获取name
        if(ss==temp)
        {
            L.setCurrentRow(i);
            is>>temp;
            return stoi(temp);
        }
        is>>temp;//获取pid
        if(temp==s.toStdString())
        {
            L.setCurrentRow(i);
            return  stoi(temp);
        }
    }
    return -1;//未找到
}
bool kill_proc(int pid)//杀死进程
{

    string s="kill "+to_string(pid);
    QString ss=s.c_str();
    QProcess::execute(ss);
    return true;
}
#endif // PROCESS_INFO_H
