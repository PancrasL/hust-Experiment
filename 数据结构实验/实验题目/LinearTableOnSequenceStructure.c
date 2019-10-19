/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <string.h>
/*------------------------------------------------------*/
typedef int status;
typedef struct{
	int item1;
}Elemtype;
typedef struct{
	Elemtype * elem;
	int length;
	int listsize;
}SqList;
/*------------------------------------------------------*/
status IntiaList(SqList * L);
status DestroyList(SqList * L);
status ClearList(SqList L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,Elemtype * e);
status LocatElem(SqList L,status (* compare)(Elemtype x,Elemtype y));
/*
status PriorElem(SqList L,Elemtype cur,Elemtype * pre_e);
status NextElem(SqList L,Elemtype cur,Elemtype * next_e);
*/
status ListInsert(SqList * L, Elemtype e);
status ListDelete(SqList * L,Elemtype * e);
status ListTrabverse(SqList L,void (* visit)(Elemtype e));
/*------------------------------------------------------*/
status equal(Elemtype x, Elemtype y);
void display(Elemtype e);
/*------------------------------------------------------*/
void menu(void);
/*------------------------------------------------------*/

void main(void){
	SqList L1,L2;
	int op=0;
	L1.elem=L2.elem=NULL;
	/*
	L1.elem=(Elemtype *) malloc(sizeof(Elemtype)*10);
	L1.length=4;
	L1.elem[0].item1=1;
	L1.elem[1].item1=2;
	L1.elem[2].item1=3;
	L1.elem[3].item1=4;
	*/
	do{
		 clrscr();
		 menu();
		 printf("          Please input your option[0-12]:");
		 scanf("%d",&op);
		 switch(op){
			 case 0: break;
			 case 1: printf("\n     here is IntiaList(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 2: printf("\n     here is DestroyList(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 3: printf("\n     here is ClearList(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 4: printf("\n     here is ListEmpty(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 5: printf("\n     here is ListLength() ,which  being realized\n");
							 getchar();getchar();
							 break;
			 case 6: printf("\n     here is GetElem(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 7: printf("\n     here is LocatElem(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 8: printf("\n     here is PriorElem(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 9: printf("\n     here is NextElem(),which  being realized\n");
							 getchar();getchar();
							 break;
			 case 10: printf("\n     here is ListInsert(),which  being realized\n");
								getchar();getchar();
								break;
			 case 11: printf("\n     here is ListDelete(),which  being realized\n");
								getchar();getchar();
								break;
			 case 12: {/*printf("\n     here is ListTrabverse(),which  being realized\n");*/

								 char tablename[9];
								 do{
										printf("\n    please specify liear table name[L1,L2]: ");
										scanf("%s",tablename);
								 }while(strcmp(tablename,"L1") && strcmp(tablename,"L2"));

								 if(!strcmp(tablename,"L1")){
									 if(!L1.elem)
											 printf("\n     liear table L1 does not exist!\n");
										 else if(!ListTrabverse(L1,display))
															printf("\n  this liear table is empty!\n");
								 }
								 if(!strcmp(tablename,"L2")){
									 if(!L2.elem)
											 printf("\n     liear table L2 does not exist!\n");
										 else if(!ListTrabverse(L2,display))
															printf("\n  this liear table is empty!\n");
								 }
								 getchar();getchar();
								 break;
								}
			 default: ;
		 }
	}while(op);
	printf("\n--------------------Welcome again!--------------------\n");
	getchar();getchar();
}

status IntiaList(SqList * L){

}

status DestroyList(SqList * L){

}

status ClearList(SqList L){
}

status ListEmpty(SqList L){

}

int ListLength(SqList L){

}

status GetElem(SqList L,int i,Elemtype * e){
}

status LocatElem(SqList L,status (* compare)(Elemtype ,Elemtype )){
}

/*
status PriorElem(SqList L,Elemtype cur,Elemtype * pre_e){
}
status NextElem(SqList L,Elemtype cur,Elemtype * next_e){
}
*/

status ListInsert(SqList * L, Elemtype e){
}

status ListDelete(SqList * L,Elemtype * e){
}

status ListTrabverse(SqList L, void (* visit)(Elemtype e)){
	int i;
	if(!L.length) return(0);
	printf("\n-------------all elements of liear table----------------\n");
	for(i=0;i<L.length;i++) visit(L.elem[i]);
	return(1);
}

/*------------------------------------------------------*/
void menu(void){
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocatElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");

}

/*------------------------------------------------------*/
status equal(Elemtype x, Elemtype y){
	return (x.item1==y.item1);
}

void display(Elemtype e){
	printf("%d ",e.item1);

}