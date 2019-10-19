#ifndef OPERATION
#define OPERATION
#include "filesystem_struct.h"
#include <vector>
void show_file();                               //显示当前目录下的文件
int mkdir(int blockNum, const char *filename);  //在当前目录下创建目录
int mkfile(int blockNum, const char *filename); //在当前目录下创建文件
int cd(int blockNum, const char *filename);     //进入目录
int fileRead(int blockNum, vector<char> &buff, int size);             //读取文件
int fileWrite(int blockNum, vector<char> &buff, int size);            //向文件中写数据
void createEntry(DIRENTRY &entry, const char *name,
                 char kind, int fileSize, int blockNum); //创建目录项
int rm(int blockNum, const char *filename);                         //删除当前目录下的文件
void freeDir(int blockNum, int flag);                               //flag=0,表示清空当前目录，flag=1，递归删除目录
void freeFile(int blockNum);                                        //删除文件
int chmod(int blockNum,const char *filename,int pride);             //更改文件权限
#endif
