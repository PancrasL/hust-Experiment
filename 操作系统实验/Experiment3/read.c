#include "sem.h"
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    /*使用相同的id获取信号灯组和缓冲区组*/
    int shmid = shmget(111, BUFNUM * sizeof(BUFF), IPC_CREAT | 0666);
    int semid = semget(222, 3, IPC_CREAT | 0666);

    /*从缓冲区中读取信息存放到文件中*/
    BUFF *pbuf = (BUFF *)shmat(shmid, NULL, SHM_R);
    int index = 0;
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("%s打开失败\n", argv[1]);
        return -1;
    } //文件打开失败
    printf("%s打开成功\n", argv[1]);
    BUFF temp;
    int len = 1;
    while (len)
    {
        len = fread(temp.data, 1, sizeof(temp.data), fp);
        temp.length = len;    //从文件中读取一个缓冲区大小的数据块，将实际1数据长度保存到len中

        P(semid, 0);          //请求空缓冲区
        P(semid, 2);          //请求互斥访问缓冲区
        pbuf[index++] = temp; //存放数据到缓冲区中
        V(semid, 1);          //增加满缓冲区个数
        V(semid, 2);          //结束互斥访问
        
        index %= BUFNUM;
    }
    fclose(fp);  //关闭文件
    shmdt(pbuf); //断开共享内存连接
    return 0;
}
