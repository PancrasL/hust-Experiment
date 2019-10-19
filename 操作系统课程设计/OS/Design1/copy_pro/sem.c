#include<sem.h>
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
