#ifndef STRUCT_INFO_H
#define STRUCT_INFO_H
#include<string>
using namespace std;
struct PROC_INFO{
    string pid;//进程id
    string name;//进程名
    string taskState;//进程状态：
    string ppid;//进程父id
    string rss;//占用内存,单位KB
    string priority;//进程优先级
};//保存进程的相关信息
struct DOT{//坐标点
    int x;//横坐标
    int y;//纵坐标
    DOT(int x1=0,int y1=0):x(x1),y(y1){};
};

#endif // STRUCT_INFO_H
