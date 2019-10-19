#ifndef MEM_INFO_H
#define MEM_INFO_H
#include<QString>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<QLabel>
using namespace std;
QString get_mem_usage(double &rate,int &total)//rate:使用率。total:总空间（MB）
{
    ifstream infile("/proc/meminfo");
    if(infile.is_open())
    {
        string line;
        string buf;
        double tot,free,use;
        getline(infile,line);//获取内存总容量
        istringstream instr(line);
        instr>>buf>>tot;
        getline(infile,line);
        getline(infile,line);
        istringstream instr1(line);
        instr1>>buf>>free;
        use=tot-free;
        use/=1024;tot/=1024;free/=1024;//KB转换为MB
        total=static_cast<int>(tot);
        rate=use/tot*100;
        char str[256];
        sprintf(str,"%.2lf%%\t%.0lfMB/%.0lfMB",rate,use,tot);
        infile.close();
        return str;
    }
    else
    {
        rate=0;total=0;
        return "";
    }
}
QString get_swap_usage(double &rate,int &total)//rate:使用率。total:总空间（MB）
{

    ifstream infile("/proc/meminfo");
    if(infile.is_open())
    {
        double tot,use,free;
        tot=use=free=0;
        string line;
        string buf;
        while (getline(infile,line))
        {
            if(line.find("SwapTotal")==string::npos)
                continue;
            istringstream instr(line);
            instr>>buf>>tot;
            break;
        }
        while (getline(infile,line))
        {
            if(line.find("SwapFree")==string::npos)
                continue;
            istringstream instr(line);
            instr>>buf>>free;
            break;
        }
        use=tot-free;
        rate=use/tot;
        tot/=1024;free/=1024;use/=1024;
        total=static_cast<int>(tot);
        char str[256];
        sprintf(str,"%.2lf%%\t%.0lfMB/%.0lfMB",rate,use,tot);
        return str;
    }
    else
    {
        rate=0;total=0;
        return "";
    }
}
#endif // MEM_INFO_H
