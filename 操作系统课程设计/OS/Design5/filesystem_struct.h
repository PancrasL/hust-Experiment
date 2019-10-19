#ifndef FILESTRUCT
#define FILESTRUCT
#include <iostream>
#include <bitset>
#include <time.h>
using namespace std;
#define fileSystemPath "./data"
#define BLOCK_SIZE 512
#define BLOCK_NUM 512
#define ROOT_BLOCK_NUM 2 //根目录所在块
#define MAX_ENTRY_NUM (BLOCK_SIZE / sizeof(DIRENTRY))
#define USER "lvpengze"
#define PWD "123456"
struct SUPERBLOCK //超级块
{
    int block_size;     //块大小
    int block_num;      //块的总数量
    int block_use;      //已使用的块的数量
    int block_remain;   //未使用的块的数量
    int free_block[10]; //保存空闲块的编号
    int free_num;
    char space[BLOCK_SIZE - 14 * sizeof(int)]; //填充空白区，保证超级块的大小为BLOCK_SIZE
};
struct BITBLOCK //位试图块
{
    bitset<BLOCK_NUM * 8> bitmap; //位视图
};
struct DIRENTRY //目录表项
{
    char name[15];   //目录或者文件名称
    int pride;       //文件操作权限，0只读，1读写
    char kind;       //类型，文件为f，目录为d
    int fileSize;    //文件大小
    time_t create_date; //文件创建时间
    int blockNum;    //文件的第一个物理块地址
};
struct FILEBLOCK //数据文件块
{
    char data[BLOCK_SIZE - 2]; //数据
    short next;                //该文件的下一个文件块号
};
struct DIRBLOCK //目录文件块
{
    int entryNum;                                     //目录项个数
    DIRENTRY dirEntry[BLOCK_SIZE / sizeof(DIRENTRY)]; //目录项
    int next;                                         //num=0,该块为最后一个文件块，否则num标识下一个文件块号
    char space[BLOCK_SIZE - sizeof(dirEntry) - 4];    //保证大小为BLOCK_SIZE
};
#endif
