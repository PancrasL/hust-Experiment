#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define MSEEAGE_SIZE 1024
#define TIME 5

void handle_main(int sig);
void kill_1(int sig);
void kill_2(int sig);

//child process id
int pid1, pid2;

int main(int argc, char *argv[])
{
    /*创建无名管道*/
    int piped[2];
    pipe(piped); //0为读管道，1为写管道
    /*设置中断信号*/
    signal(SIGINT, handle_main);
    alarm(TIME + 1);
    signal(SIGALRM, handle_main);
    /*创建进程1*/
    pid1 = fork();
    /*pid1*/
    if (pid1 == 0)
    {
        /*设置软中断信号*/
        signal(SIGINT, SIG_IGN); //忽略SIGINT
        signal(SIGUSR1, kill_1); //收到SIGUSR1时杀死进程

        close(piped[0]); //关闭读管道
        char msg[MSEEAGE_SIZE];
        int counter = 1; //计数器
        while (1)
        {
            sleep(1);                                     //等待1秒
            sprintf(msg, "I send you %u times", counter); //生成消息
            write(piped[1], msg, strlen(msg) + 1);        //写入消息到管道
            counter++;
        }
    }

    pid2 = fork();
    /*pid2*/
    if (pid2 == 0)
    {
        /*设置软中断信号*/
        signal(SIGINT, SIG_IGN); //忽略 SIGINT
        signal(SIGUSR1, kill_2); //收到SIGUSR1时杀死线程

        /*接收消息*/
        char msg[MSEEAGE_SIZE];
        close(piped[1]); //关闭写管道

        int size;
        while (1)
        {
            size = read(piped[0], msg, MSEEAGE_SIZE);
            if (size < 0)
                return -1;       //出错
            printf("%s\n", msg); //输出信息
        }
    }
    close(piped[0]);
    close(piped[1]);
    /*等待子进程结束*/
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("Parent Process is Killed!\n");
    return 0;
}

void handle_main(int sig)
{
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
    return;
}
void kill_1(int sig)
{
    printf("Child Process 1 is Killed by Parent!\n");
    exit(0);
}
void kill_2(int sig)
{
    printf("Child Process 2 is Killed by Parent!\n");
    exit(0);
}
