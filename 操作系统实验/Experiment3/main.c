#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "sem.h"
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("参数错误\n");
        return -1;
    }
    /*创建共享内存*/
    int shmid = shmget(111, BUFNUM * sizeof(BUFF), IPC_CREAT | 0666); //创建连续的10个缓冲区
    if (shmid == -1)
        return 0; //缓冲区创建失败
    printf("share memory create success\n");
    /*创建信号灯*/
    int semid = semget(222, 3, IPC_CREAT | 0666); //创建一个包含3个信号灯的信号灯集
    if (semid == -1)
        return 0; //信号灯创建失败
    printf("semaphore create success\n");
    /*信号灯赋值*/
    union semun arg;
    arg.val = BUFNUM;
    semctl(semid, 0, SETVAL, arg); //第0个信号灯表示空缓冲区的个数，初值为BUFSIZE
    arg.val = 0;
    semctl(semid, 1, SETVAL, arg); //第1个信号灯表示满缓冲区的个数，初值为0
    arg.val = 1;
    semctl(semid, 2, SETVAL, arg); //第2个信号灯为访问缓冲区的互斥访问信号灯，初值为1

    /*创建进程*/
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) //创建子进程write
    {
        if (execl("./write", "write", argv[2], NULL) == -1)
        {
            printf("子进程write创建失败\n");
            exit(-1);
        }
    }
    pid2 = fork();
    if (pid2 == 0) //创建子进程read
    {
        if (execl("./read", "read", argv[1], NULL) == -1)
        {
            printf("子进程read创建失败\n");
            exit(-1);
        }
    }
    /*等待两个子进程结束*/
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    /*删除信号灯*/
    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        printf("semaphore delete fail\n");
    else
        printf("semaphore delete success\n");
    /*删除共享内存*/
    if (shmctl(shmid, IPC_RMID, 0) == -1)
        printf("share memory delete fail\n");
    else
        printf("share memory delete success\n");

    return 0;
}