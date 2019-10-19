#ifndef FILECONTROL
#define FILECONTROL
#include <iostream>
#include <string.h>
#include "filesystem_struct.h"
#include "blockManage_layer.h"
using namespace std;
int namei(int blockNum, const char *name, DIRENTRY &entry); //在目录块dir中查找目录项name，找到返回1，并将目录项保存到entry中，未找到返回0
int modifyEntry(int blockNum,const char *name, DIRENTRY &entry);//修改块中filename的目录项为entry
int insertEntry(int blockNum, DIRENTRY &entry); //增加目录项，插入成功返回1,失败返回0
int deleteEntry(int blockNum, const char *name);//删除目录项，成功返回1,失败返回0
void display_dir(int blockNum);
void createEntry(DIRENTRY &entry,const char *name,char kind,int fileSize,int blockNum,int pride);

#endif
