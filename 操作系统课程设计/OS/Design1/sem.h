
#ifndef COORDIH_H_
#define COORDIH_H_
#include<sys/sem.h>
#define BUFSIZE 512
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};
struct buff
{
    char data[BUFSIZE];
};
typedef struct buff BUFF;
void P(int semid,int index);
void V(int semid,int index);
#endif
