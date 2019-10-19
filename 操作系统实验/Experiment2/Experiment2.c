#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
void P(int semid,int index);
void V(int semid,int index);
int semid;
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};
void *subp1(void *arg);
void *subp2(void *arg);
int sum;
pthread_t p1,p2;
int main()
{
    /*创建信号灯*/
    semid=semget(111, 2, IPC_CREAT|0666);//创建一个包含2个信号灯的信号灯集
    if(semid==-1) return 0;//信号灯创建失败
    /*信号灯赋值*/
    union semun arg;
    arg.val=1;
    semctl(semid,0,SETVAL,arg);//第一个信号灯表示缓冲区空，初值为1
    arg.val=0;
    semctl(semid,1,SETVAL,arg);//第二个信号灯表示缓冲区满，初值为0
    /*创建线程*/
    pthread_create(&p1,NULL,subp1,NULL);
    pthread_create(&p2,NULL,subp2,NULL);
    /*等待两个线程结束*/
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    /*删除信号灯*/
    if(semctl(semid,0,IPC_RMID,0)==-1)
        printf("sem delete fail\n");
    else printf("sem delete success\n");
    return 0;
}
void P(int semid,int index)
{
	struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);//1:表示执行命令的个数
}
void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
}
void *subp1(void *arg)
{
    int i;
	for(i=1;i<=100;i++)
    {
        P(semid,0);
        printf("thread1 is calculating\n");
		sum+=i;
		V(semid,1);
	}
}
void *subp2(void *arg)
{
    int i=1;
    while(i<=100)
    {
        P(semid,1);
        printf("thread2 output:%d\n\n",sum);
        i++;
        V(semid,0);
    }
}

