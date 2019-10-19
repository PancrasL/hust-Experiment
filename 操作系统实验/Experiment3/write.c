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

    /*从文件中读取信息放入到缓冲区中*/
    BUFF *pbuf = (BUFF *)shmat(shmid, NULL, SHM_W); //连接共享内存
    int index = 0;
    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL)
    {
        printf("%s打开失败\n", argv[1]);
        return -1;
    } //文件打开失败
    printf("%s打开成功\n", argv[1]);
    BUFF temp;
    while (1)
    {
        P(semid, 1);         //请求满缓冲区
        P(semid, 2);         //请求互斥访问缓冲区
        temp = pbuf[index++]; //取出数据
        V(semid, 2);         //结束互斥访问
        V(semid, 0);         //增加空缓冲区
        index %= BUFNUM;
        if (temp.length == 0) //文件已读取完毕
            break;
        fwrite(temp.data, temp.length, 1, fp);
    }
    fclose(fp); //关闭文件
    shmdt(pbuf); //断开共享内存连接
    return 0;
}
