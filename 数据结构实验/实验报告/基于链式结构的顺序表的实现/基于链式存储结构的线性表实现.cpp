/*含头结点的链式存储结构的线性表实现*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

/*--------------------page 10 on textbook ----------------------------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define FILENAME_L1 "dataL1"
#define FILENAME_L2 "dataL2"

typedef int status;
typedef int Elemtype;
typedef struct lnode
{
	Elemtype data;
	lnode * next;
}Lnode; //数据元素类型定义


typedef Lnode* SqList;//头指针

status IntiaList(SqList  *L);//L为指向头指针的指针
status DestroyList(SqList * L);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, Elemtype & e);
status LocateElem(SqList L, Elemtype e, status(*compare)(Elemtype *x, Elemtype *y));
status PriorElem(SqList L, Elemtype cur, Elemtype & pre_e);
status NextElem(SqList L, Elemtype cur, Elemtype & next_e);
status ListInsert(SqList L, int i, Elemtype e);
status ListDelete(SqList L, int i, Elemtype & e);
status ListTrabverse(SqList L, status(*visit)(Elemtype e));
status Loaddata(SqList *L, char *filename);//加载数据
status Savedata(SqList L, char *filename);//保存数据
status visit(Elemtype e);
status compare(Elemtype *x, Elemtype *y);

SqList * list_verify(SqList *L1, SqList *L2);


/*------------------------------------------------------*/
void main(void) {
	SqList L1, L2;
	SqList *L;
	L1 = L2 = NULL;
	int op = 1;
	int i;
	while (op) {
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
		printf("    	  13. 从文件中读取数据\n");
		printf("    	  14. 保存数据至文件\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d", &op);
		getchar();
		L = list_verify(&L1, &L2);//确认需要操作的表
		switch (op) {
		case 1:
			if (*L == NULL)//若线性表不存在，则创建
			{
				if (IntiaList(L) == OK) printf("线性表创建成功！\n");
				else printf("线性表创建失败！\n");
				//printf("%p", (*L)->next);
			}
			else printf("线性表已存在\n");
			getchar(); getchar();
			break;
		case 2:
			if (*L)//若表存在
			{
				DestroyList(L);
				printf("表销毁成功\n");
				//printf("%p", *L);
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 3:
			if (*L)//若表存在
			{
				ClearList(L);
				printf("表清空成功\n");
				//printf("%p", *L);
				//printf("%p", (*L)->next);
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 4:
			if (*L)//若表存在
			{
				if (ListEmpty(*L))
					printf("线性表为空\n");
				else printf("线性表不为空\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 5:
			if (*L)//若表存在
			{
				int len;
				len = ListLength(*L);
				printf("表长为%d\n", len);
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 6:
			if (*L)//若表存在
			{
				Elemtype e;
				printf("输入元素序号\n");
				scanf(" %d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L))//若i值有效
				{
					GetElem(*L, i, e);//获取位序为i的元素
					printf("位序%d的元素值为:", i); visit(e);//输出获取的元素值
				}
				else printf("i值无效\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 7:
			if (*L)//若表存在
			{
				Elemtype e;
				printf("输入一个数字，为e赋值\n");
				scanf("%d", &e);
				getchar();
				//输出第一个与e满足compare关系的元素位序，不存在位序为0
				int order = LocateElem(*L, e, compare);
				if (order == 0)
					printf("表中不存在与e相同的元素\n");
				else printf("第一个与e满足compare关系的元素位序是%d\n", order);
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 8:
			if (*L)//若表存在
			{
				Elemtype cur_e, pre_e;
				printf("输入一个数字，为cur_e赋值\n");
				scanf("%d", &cur_e);
				getchar();
				if (PriorElem(*L, cur_e, pre_e) == 1)//如果cur_e存在前驱
				{
					printf("cur_e的前驱为:"); visit(pre_e);
				}
				else printf("cur_e的前驱不存在\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 9:
			if (*L)//若表存在
			{
				Elemtype cur_e, next_e;
				printf("输入一个数字，为cur_e赋值\n");
				scanf("%d", &cur_e);
				getchar();
				if (NextElem(*L, cur_e, next_e) == 1)//如果cur_e存在后继
				{
					printf("cur_e的后继为:"); visit(next_e);
				}
				else printf("cur_e的后继不存在\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 10:
			if (*L)//若表存在
			{
				printf("输入要插入的位置\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L) + 1)//i值合法
				{
					Elemtype e;//插入的元素
					printf("输入一个数字，为e赋值\n");
					scanf("%d", &e);
					getchar();
					if (ListInsert(*L, i, e))
						printf("插入成功\n");
					else printf("插入失败\n");
				}
				else printf("位置i不合法\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 11:
			if (*L)//若表存在
			{
				printf("输入要删除的数据元素位序\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L))//若i值合法
				{
					Elemtype e;//保存删除的结点数据
					if (ListDelete(*L, i, e))
					{
						printf("删除成功\n");
						printf("删除的元素值为:"); visit(e);
					}
					else printf("删除失败\n");
				}
				else printf("位置i不合法\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 12:
			if (*L)//若表存在
			{
				if (!ListTrabverse(*L, visit)) printf("线性表是空表！\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 13:
			if (*L == NULL || (*L)->next == NULL)//若表不存在或表为空，则加载数据
			{
				int status;
				if (*L == L1)//选择L1
					status = Loaddata(L, FILENAME_L1);
				else if (*L == L2)//选择L2
					status = Loaddata(L, FILENAME_L2);
				if (status)
					printf("数据加载成功\n");
				else printf("数据加载失败\n");
			}
			else printf("表已存在，请销毁或清空后加载数据\n");
			getchar(); getchar();
			break;
		case 14:
			if (*L)//若表存在
			{
				int status;
				if (*L == L1)//选择L1
					status = Savedata(*L, FILENAME_L1);
				else if (*L == L2)//选择L2
					status = Savedata(*L, FILENAME_L2);
				if (status)
					printf("数据保存成功\n");
				else printf("数据保存失败\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch	
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()

 /*--------------------page 23 on textbook ----------------------------------*/
status IntiaList(SqList * L) {
	*L = (Lnode *)malloc(sizeof(Lnode));//头指针申请一个存储结点
	if (*L)//如果分配空间成功
		(*L)->next = NULL;//头结点指针域置空
	else exit(OVERFLOW);//分配失败
	return OK;
}

status DestroyList(SqList * L)
{
	Lnode * L1;
	Lnode * temp;//存储上一个释放节点的next值
	L1 = *L;//L1用来遍历链表
	for (L1 = *L; L1 != NULL; L1 = temp)
	{
		temp = L1->next;//保存next值
		free(L1);//依次释放线性表的内存空间
	}
	*L = NULL;//头指针置空
	return OK;
}

status ClearList(SqList *L)
{
	Lnode * L1;
	Lnode * temp;//存储上一个释放节点的next值
	L1 = *L;//L1用来遍历链表
	for (L1 = (*L)->next; L1 != NULL; L1 = temp)//释放头结点之后的结点
	{
		temp = L1->next;//保存next值
		free(L1);//依次释放线性表的内存空间
	}
	(*L)->next = NULL;//头结点指针域置空
	return OK;
}

status ListEmpty(SqList L)
{
	if (L->next == NULL)//若头结点的指针域为空
		return TRUE;
	else return FALSE;
}

int ListLength(SqList L)
{
	Lnode *p;
	int count;
	for (p = L->next, count = 0; p != NULL; p = p->next)
		count++;//p每后移一次，表长加1
	return count;
}

status GetElem(SqList L, int i, Elemtype & e)
{
	Lnode *p;
	int count;
	for (p = L->next, count = 1; count != i; p = p->next, count++);//定位第i个数据元素
	e = p->data;//赋值
	return OK;
}

status LocateElem(SqList L, Elemtype e, status(*compare)(Elemtype *x, Elemtype *y))
{
	Lnode *p;
	int count;
	for (p = L->next, count = 1; p != NULL; p = p->next, count++)//从首节点开始比较
		if (compare(&(p->data), &e) == 0)
			return count;
	return FALSE;//遍历完毕，未找到
}

status PriorElem(SqList L, Elemtype cur, Elemtype & pre_e)
{
	Lnode *p;
	Lnode *pr;//p的前驱
	p = L->next;//p指向首节点
	if (p == NULL || p->data == cur)//如果链表为空或cur是首节点，不存在前驱
		return FALSE;
	pr = p;//pr指向首节点
	p = p->next;//p指向第二结点
	while (p != NULL)
	{
		if (p->data == cur)//如果cur在表中
		{
			pre_e = pr->data;//赋值
			return TRUE;
		}
		pr = p;
		p = p->next;
	}
	return FALSE;//表中未找到cur，cur无前驱
}

status NextElem(SqList L, Elemtype cur, Elemtype & next_e)
{
	Lnode *p;//p
	p = L->next;//p指向首节点
	if (p == NULL)//如果链表为空
		return FALSE;

	while (p != NULL)
	{
		if (p->data == cur)//如果cur在表中
			break;
		p = p->next;
	}
	if (!p || !(p->next))//cur不在链表中或cur为最后一个结点
		return FALSE;
	else {
		next_e = (p->next)->data;//赋值
		return TRUE;
	}
}

status ListInsert(SqList L, int i, Elemtype e)
{
	int count;//记录当前位置
	Lnode *p;//使用p遍历链表查找位置i
	Lnode *q;
	for (p = L, count = 0; count < i - 1; p = p->next, count++);//定位，执行完毕后p指向位置i的前驱
	q = (Lnode *)malloc(sizeof(Lnode));//为插入的结点声明空间
	q->data = e;//将e的数据域赋值给q的数据域
	q->next = p->next;//插入结点
	p->next = q;
	return OK;
}

status ListDelete(SqList L, int i, Elemtype & e)
{
	Lnode *p, *q;
	int count;
	for (p = L, count = 0; count < i - 1; p = p->next, count++);//定位，执行完毕后p指向位置i的前驱
	q = p->next;//q指向删除结点
	e = q->data;//赋值
	p->next = q->next;//更改指针域
	free(q);//删除结点
	return OK;
}

status ListTrabverse(SqList L, status(*visit)(Elemtype e)) {

	if (L->next == NULL)
		return 0;
	Lnode * p;
	printf("\n-------------------- all elements ------------------------------\n");
	for (p = L->next; p != NULL; p = p->next)//使用visit访问首结点及其之后的结点
		visit(p->data);
	printf("\n------------------------- end ----------------------------------\n");
	return 1;
}
status Loaddata(SqList *L, char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	if (*L == NULL)//若表不存在，则创建表及头结点
		*L = (Lnode *)malloc(sizeof(Lnode));
	(*L)->next = NULL;//头结点指针域置空
	Lnode newEle;
	Lnode *p, *q;
	q = *L;//q指向将要插入位置的前驱结点
	while (fread(&newEle, sizeof(Lnode), 1, fp))//每次读取一个数据元素
	{
		p = (Lnode *)malloc(sizeof(Lnode));//动态声明一个结点，作为新结点插入到链表中
		*p = newEle;//为新节点赋值
					//插入结点
		p->next = q->next;
		q->next = p;
		q = p;//q后移一个结点，进行下一次的插入
	}
	fclose(fp);
	return TRUE;//写入完毕

}
status Savedata(SqList L, char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "w")) == NULL)//打开文件失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	Lnode *p;
	p = L->next;//p指向首结点
	while (p)
	{
		fwrite(p, sizeof(Lnode), 1, fp);//以二进制读写一次写入一个结点的数据
		p = p->next;
	}
	fclose(fp);//关闭文件
	return TRUE;
}

status visit(Elemtype e)
{
	printf("%d ", e);
	return TRUE;
}

status compare(Elemtype *x, Elemtype *y)
{
	return (*x) - (*y);//相同返回0
}

SqList * list_verify(SqList *L1, SqList *L2)
{
	char Listname[9];
	do {
		printf("\n    选择需要操作的表[L1,L2]: ");
		scanf("%s", Listname);
	} while (strcmp(Listname, "L1") && strcmp(Listname, "L2"));//只能在L1，L2中选择
	SqList *plist;
	if (strcmp(Listname, "L1") == 0)
		plist = L1;
	else plist = L2;//plist为用户所选的表

	return plist;
}
