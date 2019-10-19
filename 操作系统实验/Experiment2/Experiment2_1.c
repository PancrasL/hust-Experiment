#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<stdio.h>
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};
void P(int semid,int index);
void V(int semid,int index);
int semid;

void *subp1(void *arg);
void *subp2(void *arg);
int main()
{
    /*创建共享内存*/
    int shmid=shmget(100, 4, IPC_CREAT|0666);//创建一个大小为4字节(int)的共享内存
    if(shmid==-1) return 0;//创建失败
    /*创建信号灯*/
    int mykey=111;//指定一个key
    semid=semget(mykey, 2, IPC_CREAT|0666);//创建一个包含两个信号灯的信号灯集
    if(semid==-1) return 0;//信号灯创建失败
    /*信号灯赋值*/
    union semun arg;
    arg.val=1;
    semctl(semid,0,SETVAL,arg);//第一个信号灯表示缓冲区空，初值为1
    arg.val=0;
    semctl(semid,1,SETVAL,arg);//第二个信号灯表示缓冲区满，初值为0
    /*创建进程*/
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1==0)//子进程1执行内容
    {
        subp1(&shmid);
        return 1;
    }
    pid2=fork();
    if(pid2==0)//子进程2执行内容
    {
        subp2(&shmid);
        return 2;
    }
    /*等待两个子进程结束*/
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    
    /*删除信号灯*/
    if(semctl(semid,0,IPC_RMID,0)==-1)
        printf("sem delete fail\n");
    else printf("sem delete success\n");
    /*删除共享内存*/
    if(shmctl(shmid,IPC_RMID,0)==-1)
        printf("share memory delete fail\n");
    else printf("share memory delete success\n");
    
    return 0;
}
void P(int semid,int index)
{
	struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);//1:表示执行命令的个数
    return;
}
void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
	return;
}
void *subp1(void *arg)
{
    int *sum = (int *)shmat(*(int *)arg,NULL,SHM_W);
    *sum=0;
    int i;
	for(i=1;i<=100;i++)
    {
        P(semid,0);
        printf("process1 is calculating\n");
		*sum=*sum+i;
		V(semid,1);
	}
    return NULL;
}
void *subp2(void *arg)
{
    int *sum = (int *)shmat(*(int *)arg,NULL,SHM_R);
    int i=1;
    while(i<=100)
    {
        P(semid,1);
        printf("process2 output:%d\n\n",*sum);
        i++;
        V(semid,0);
    }
    return NULL;
}
