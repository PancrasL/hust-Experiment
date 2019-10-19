#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "sem.h"
int main(void)
{
    /*创建共享内存*/
    int shmid = shmget(111, sizeof(BUFF), IPC_CREAT | 0666); //创建缓冲区S
    if (shmid == -1)
        return 0; //缓冲区创建失败
    printf("share memory S create success\n");
    int shmid1 = shmget(112, sizeof(BUFF), IPC_CREAT | 0666); //创建缓冲区T
    if (shmid1 == -1)
        return 0; //缓冲区创建失败
    printf("share memory T create success\n");
    /*创建信号灯*/
    int semid = semget(222, 2, IPC_CREAT | 0666); //创建一个包含2个信号灯的信号灯集
    if (semid == -1)
        return 0; //信号灯创建失败
    printf("semaphore S create success\n");
    int semid1 = semget(223, 2, IPC_CREAT | 0666); //创建一个包含2个信号灯的信号灯集
    if (semid1 == -1)
        return 0; //信号灯创建失败
    printf("semaphore T create success\n");
    /*信号灯赋值*/
    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg); //第0个信号灯表示空缓冲区的个数，初值为1
    semctl(semid1, 0, SETVAL, arg);
    arg.val = 0;
    semctl(semid, 1, SETVAL, arg); //第1个信号灯表示满缓冲区的个数，初值为0
    semctl(semid1, 1, SETVAL, arg);
    int pid1, pid2, pid3;
    pid1 = fork();
    if (pid1 == 0)
    {
        if (execl("./build-get_pro-Desktop_Qt_5_11_3_GCC_64bit-Debug/get_pro", "my_get", NULL) == -1)
        {
            printf("子进程my_get创建失败\n");
            exit(-1);
        }
    }
    pid2=fork();
    if(pid2==0)
    {
        if (execl("./build-copy_pro-Desktop_Qt_5_11_3_GCC_64bit-Debug/copy_pro","my_copy",NULL) == -1)
        {
            printf("子进程my_copy创建失败\n");
            exit(-1);
        }
    }
    pid3=fork();
    if(pid3==0)
    {
        if (execl("./build-put_pro-Desktop_Qt_5_11_3_GCC_64bit-Debug/put_pro","sub3",NULL) == -1)
        {
            printf("子进程my_put创建失败\n");
            exit(-1);
        }
    }
    /*等待子进程结束*/
    wait(NULL);
    wait(NULL);
    wait(NULL);
    printf("子进程全部结束，主进程关闭\n");
    return 0;
}
