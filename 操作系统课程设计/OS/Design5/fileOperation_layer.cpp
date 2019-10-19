#include "fileOperation_layer.h"
#include "fileControl_layer.h"
#include <iostream>
#include <time.h>
extern int curDir;
extern int isRoot;
extern int dirOwner;
void show_file() //显示当前目录下的文件
{
    display_dir(curDir);
}
int mkdir(int blockNum, const char *filename) //在blockNum目录下创建目录
{
    DIRENTRY entry;
    if (namei(blockNum, filename, entry) == 1)
    {
        cout << "file " << filename << " is already exist, please choose another name" << endl;
        return 0;
    }
    /*创建目录项*/
    int num = get_block();
    if (num < 0)
    {
        cout << "no more room" << endl;
        return 0;
    }
    createEntry(entry, filename, 'd', 0, num);
    insertEntry(blockNum, entry);
    /*创建目录文件*/
    DIRBLOCK dir;
    dir.entryNum = 2;
    dir.next = 0;
    //生成本目录目录项
    createEntry(entry, ".", 'd', 0, num);
    dir.dirEntry[0] = entry;
    //生成父目录目录项
    createEntry(entry, "..", 'd', 0, blockNum);
    dir.dirEntry[1] = entry;
    block_write(num, &dir);
    return true;
}
void createEntry(DIRENTRY &entry, const char *name, char kind, int fileSize, int blockNum)
{
    strcpy(entry.name, name);
    entry.kind = kind;
    entry.fileSize = fileSize;
    entry.blockNum = blockNum;
    entry.pride = dirOwner;
    time_t now = time(0);
    entry.create_date = now;
}
int mkfile(int blockNum, const char *filename) //在当前目录下创建文件
{
    DIRENTRY entry;
    if (namei(blockNum, filename, entry) == 1)
    {
        cout << "file " << filename << " is already exist, please choose another name" << endl;
        return 0;
    }
    /*创建目录项*/
    int num = get_block();
    if (num < 0)
    {
        cout << "no more room" << endl;
        return 0;
    }
    FILEBLOCK file;
    file.next = 0;
    block_write(num, &file);
    createEntry(entry, filename, 'f', 0, num);
    insertEntry(blockNum, entry);
    return true;
}
int cd(int blockNum, const char *filename) //进入目录,成功返回1,失败返回0
{
    DIRENTRY entry;
    if (namei(blockNum, filename, entry) == 0) //文件不存在
    {
        cout << "file doesn't exist" << endl;
        return 0;
    }
    if (entry.kind != 'd')
    {
        cout << filename << " is not a dir" << endl;
        return 0;
    }
    curDir = entry.blockNum;
    dirOwner = entry.pride;
    return 1;
}

int rm(int blockNum, const char *filename) //删除当前目录下的filename文件，成功返回1,失败返回0
{
    DIRENTRY entry;
    if (strcmp(filename, "./") == 0) //清空当前目录
    {
        freeDir(blockNum, 0);
        return 1;
    }
    if (namei(curDir, filename, entry)) //当文件存在是删除该文件
    {
        if (entry.kind == 'd') //是目录，递归删除
        {
            freeDir(entry.blockNum, 1);
        }
        else //是文件，直接删除
        {
            freeFile(entry.blockNum);
        }
        deleteEntry(blockNum, filename); //删除目录项
    }
    return 1;
}
void freeDir(const int blockNum, int flag) //删除blockNum块下的所有文件
{
    if (blockNum == 0)
        return;
    DIRBLOCK dir;
    block_read(blockNum, &dir);
    for (int i = 0; i < dir.entryNum; i++)
    {
        DIRENTRY *pentry = &dir.dirEntry[i];
        if (pentry->name[0] == '.')
            continue;
        else if (pentry->kind == 'd') //是目录，递归删除
        {
            freeDir(pentry->blockNum, 1);
            deleteEntry(blockNum, pentry->name);
        }
        else //是文件，直接删除
        {
            freeFile(pentry->blockNum);
            deleteEntry(blockNum, pentry->name);
        }
    }
    int temp = dir.next;
    if (flag) //递归调用时把当前块也释放
    {
        free_block(blockNum);
        freeDir(temp, 1);
    }
    else //删除下一个块的内容
    {
        freeDir(temp, 1);
        block_read(blockNum, &dir);
        dir.next = 0;
        block_write(blockNum, &dir);
    }
}
void freeFile(int blockNum)
{
    FILEBLOCK file;
    block_read(blockNum, &file);
    while (file.next != 0)
    {
        int nextBlock = file.next;
        free_block(blockNum);
        blockNum = nextBlock;
        block_read(blockNum, &file);
    }
    free_block(blockNum);
}
int fileRead(int blockNum, vector<char> &v, int size)
{
    if (size == 0)
        return 0;
    FILEBLOCK file;
    while (blockNum)
    {
        block_read(blockNum, &file);
        for (int i = 0; i < sizeof(file.data); i++)
        {
            v.push_back(file.data[i]);
            if (--size == 0)
                break;
        }
        blockNum = file.next;
    }
    return 0;
}
int fileWrite(int blockNum, vector<char> &v, int size)
{
    FILEBLOCK file;
    file.next=0;
    int index = 0;
    while (size)
    {
        for (int i = 0; i < sizeof(file.data); i++)
        {
            file.data[i] = v[index++];
            if (--size == 0)
                break;
        }
        if (size) //数据未写完,申请一个新块
        {
            int num = get_block();
            file.next = num;
            block_write(blockNum, &file);
            blockNum = num;
            block_read(blockNum, &file);
            file.next = 0;
        }
    }
    block_write(blockNum, &file);
    return 0;
}
int chmod(int blockNum, const char *filename, int pride)
{
    DIRENTRY entry;
    if (namei(blockNum, filename, entry))
    {
        entry.pride = !(!pride);
        modifyEntry(blockNum, filename, entry);
    }
    else
        cout << filename << " doesn't exist" << endl;
    return 1;
}