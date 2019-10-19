#ifndef BLOCKMANAGE
#define BLOCKMANAGE
#include <iostream>
#include <memory.h>
#include <fstream>
#include <stdlib.h>
#include "filesystem_struct.h"
using namespace std;
int block_write(int blockNum, void *fb); //向块blockNum中写入以fb开始，长度为BLOCK_SIZE字节的数据

int block_read(int blockNum, void *fb); //将块blockNum中的数据读取到以fb开始，长度至少为BLOCK_SIZE字节的缓冲区中
int get_block(); //获取空闲块
void free_block(int blockNum); //回收空闲块
bool reformat(); //格式化文件系统
void display_free_1();
void display_free_2();
#endif