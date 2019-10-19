#include "fileControl_layer.h"
#include <time.h>
int curDir;                     //当前目录所在块
int dirOwner;                   //当前目录拥有者                                           
int namei(int blockNum, const char *name, DIRENTRY &entry) //在目录块blockNum中查找目录项name，找到返回1，并将目录项保存到entry中，未找到返回0
{
    DIRBLOCK dir;
    block_read(blockNum, &dir);
    while (true)
    {
        for (int i = 0; i < dir.entryNum; i++)
        {
            if (strcmp(dir.dirEntry[i].name, name) == 0)
            {
                entry = dir.dirEntry[i];
                return 1;
            }
        }
        if (dir.next == 0)
            break; //读取到目录文件结尾
        block_read(dir.next, &dir);
    }
    return 0;
}
int modifyEntry(int blockNum, const char *name, DIRENTRY &entry)
{
    DIRBLOCK dir;
    block_read(blockNum, &dir);
    int curBlockNum = blockNum;
    while (true)
    {
        for (int i = 0; i < dir.entryNum; i++)
        {
            if (strcmp(dir.dirEntry[i].name, name) == 0)
            {
                dir.dirEntry[i] = entry;
                block_write(curBlockNum, &dir);
                return 1;
            }
        }
        if (dir.next == 0)
            break; //读取到目录文件结尾
        curBlockNum = dir.next;
        block_read(dir.next, &dir);
    }
    return 0;
}
int insertEntry(int blockNum, DIRENTRY &entry) //增加目录项，插入成功返回1,失败返回0
{
    DIRBLOCK dir;
    int curBlockNum = blockNum;
    block_read(blockNum, &dir);
    if (dir.entryNum == MAX_ENTRY_NUM) //目录块空间不足
    {
        while (true) //寻找空闲位置
        {
            if (dir.next == 0) //没有空闲位置，申请一个新块
            {
                blockNum = curBlockNum;
                curBlockNum = get_block();
                if (curBlockNum == -1) //申请失败
                {
                    printf("文件系统空间不足\n");
                    return 0;
                }
                /*打开新申请的目录块*/
                dir.next = curBlockNum;
                block_write(blockNum, &dir);
                block_read(curBlockNum, &dir);
                /*写入文件项*/
                dir.entryNum = 0;
                dir.dirEntry[dir.entryNum++] = entry; //增加目录项
                dir.next = 0;
                block_write(curBlockNum, &dir);
                return 1;
            }
            curBlockNum = dir.next;
            block_read(curBlockNum, &dir);
            if (dir.entryNum == MAX_ENTRY_NUM)
                continue;
            else
            {
                dir.dirEntry[dir.entryNum++] = entry;
                block_write(curBlockNum, &dir);
                return 1;
            }
        }
    }
    /*有空间，直接写入*/
    dir.dirEntry[dir.entryNum++] = entry;
    block_write(curBlockNum, &dir);
    return 1;
}
int deleteEntry(int blockNum, const char *name) //删除目录项，成功返回1,失败返回0
{
    if (name[0] == '.')
        return 0;
    DIRBLOCK dir;
    int curBlockNum = blockNum;
    block_read(blockNum, &dir);
    while (true)
    {
        int i;
        for (i = 0; i < dir.entryNum; i++)
        {
            if (strcmp(dir.dirEntry[i].name, name) == 0)
            {
                cout << "dirEntry " << name << " delete success" << endl;
                break;
            }
        }
        if (i != dir.entryNum) //找到目录项，执行删除操作
        {
            for (int j = i + 1; j < dir.entryNum; j++)
            {
                dir.dirEntry[j - 1] = dir.dirEntry[j];
            }
            dir.entryNum--;
            block_write(curBlockNum, &dir);
            return 1;
        }
        if (dir.next == 0)
            break; //读取到目录文件结尾
        curBlockNum = dir.next;
        block_read(curBlockNum, &dir);
    }
    return 0;
}
void display_dir(int blockNum)
{
    DIRBLOCK dir;
    block_read(blockNum, &dir);
    while (true)
    {
        cout << "name\t\tkind\tsize\tblock\towner\t\tcreateTime" << endl;
        for (int i = 0; i < dir.entryNum; i++)
        {
            if(dir.dirEntry[i].name[0]=='.') continue;
            cout << dir.dirEntry[i].name << "\t";
            if(strlen(dir.dirEntry[i].name)<8) cout<<"\t";
            cout << dir.dirEntry[i].kind << "\t";
            if (dir.dirEntry[i].kind == 'd')
                cout << "\\"<< "\t";
            else
                cout << dir.dirEntry[i].fileSize << "\t";
            cout << dir.dirEntry[i].blockNum << "\t";
            if (dir.dirEntry[i].pride==1)
                cout << "root\t\t";
            else
                cout << USER << "\t";
            cout << ctime(&dir.dirEntry[i].create_date) << endl;
        }
        if (dir.next == 0)
            break;
        block_read(dir.next, &dir);
    }
    cout << endl;
}
