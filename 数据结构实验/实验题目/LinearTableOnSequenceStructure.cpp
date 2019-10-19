/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*--------------------page 10 on textbook ----------------------------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

/*--------------------page 22 on textbook ----------------------------------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;
/*--------------------page 19 on textbook ----------------------------------*/
status IntiaList(SqList & L);
//status DestroyList(SqList & L);
//status ClearList(SqList &L);
//status ListEmpty(SqList L);
//int ListLength(SqList L);
//status GetElem(SqList L,int i,ElemType & e);
//status LocateElem(SqList L,ElemType e); //�򻯹�
//status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
//status NextElem(SqList L,ElemType cur,ElemType & next_e);
//status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L,int i,ElemType & e);
status ListTrabverse(SqList L);  //�򻯹�
/*------------------------------------------------------*/
void main(void){
  SqList L;
  int op=1;
  while(op){
	system("cls");
    printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
    printf("    ��ѡ����Ĳ���[0~12]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
		 if(IntiaList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
	   case 2:
		 printf("\n----DestroyList���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 3:
		 printf("\n----ClearList���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 4:
		 printf("\n----ListEmpty���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 5:
		 printf("\n----ListLength���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 6:
		 printf("\n----GetElem���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 7:
		 printf("\n----LocateElem���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 8:
		 printf("\n----PriorElem���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 9:
		 printf("\n----NextElem���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 10:
		 printf("\n----ListInsert���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 11:
		 printf("\n----ListDelete���ܴ�ʵ�֣�\n");     
		 getchar();getchar();
		 break;
	   case 12:
		 //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");     
		 if(!ListTrabverse(L)) printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;
	   case 0:
         break;
	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

/*--------------------page 23 on textbook ----------------------------------*/
status IntiaList(SqList & L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}



status ListTrabverse(SqList L){
   int i;
   printf("\n-------------------- all elements ------------------------------\n");
   for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
   printf("\n------------------------- end ----------------------------------\n");
   return L.length;
}