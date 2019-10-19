/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
/*--------------------page 10 on textbook ----------------------------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define FILENAME "data"//数据保存的文件名

typedef int status;
typedef int ElemType; //数据元素类型定义

/*--------------------page 22 on textbook ----------------------------------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
/*--------------------page 19 on textbook ----------------------------------*/
status InitiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType & e);
status LocatElem(SqList L, ElemType e, status(*compare)(ElemType x, ElemType y));
status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
status NextElem(SqList L,ElemType cur,ElemType & next_e);
status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L,int i,ElemType & e);
status ListTrabverse(SqList L, status(*visit)(ElemType e));
status compare(ElemType x, ElemType y);
status Loaddata(SqList &L);//加载数据
status Savedata(SqList L);
status visit(ElemType e);
/*------------------------------------------------------*/
int main(void){
	SqList L;
	L.elem = NULL;
	int i;//插入位置
	int op = 1;
	int flat = 1;//表不存在
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
		switch (op) {
		case 1:
			if (!L.elem&&flat)//若线性表不存在，则创建
			{
				if (InitiaList(L) == OK) {
					printf("线性表创建成功！\n");
					flat = 0;//表已创建
				}
				else printf("线性表创建失败！\n");
			}
			else printf("线性表已存在\n");
			getchar(); getchar();
			break;
		case 2:
			if (L.elem)//若表存在
			{
				DestroyList(L);
				printf("表销毁成功\n");
				flat = 1;
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 3:
			if (L.elem)//若表存在
			{
				ClearList(L);
				printf("表置空成功\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();

			break;
		case 4:
			if (L.elem)//若表存在
			{
				if (ListEmpty(L) == 1)
					printf("表为空\n");
				else printf("表不为空\n");
			}
			else printf("表不存在\n");
			getchar();
			break;
		case 5:
			if (L.elem)//若表存在
			{
				printf("表长为%d\n", ListLength(L));
			}
			else printf("表不存在\n");
			getchar();
			break;
		case 6:
			ElemType e;
			if (L.elem)//表存在
			{
				printf("输入元素序号\n");
				scanf(" %d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L))//若i值有效
				{
					GetElem(L, i, e);//获取位序为i的元素
					printf("位序%d的元素值为%d", i, e);//输出获取的元素值
				}
				else printf("i值无效\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 7:
			if (L.elem)
			{
				ElemType e;
				printf("输入一个数字，为e赋值\n");
				scanf("%d", &e);
				getchar();

				//输出第一个与e满足compare关系的元素位序，不存在位序为0
				int order = LocatElem(L, e, compare);
				if (order == 0)
					printf("表中不存在与e相同的元素\n");
				else printf("第一个与e相同的元素位序是%d\n", order);
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 8:
			if (L.elem)//若表存在
			{
				ElemType cur_e, pre_e;
				printf("输入一个数字，为cur_e赋值\n");
				scanf("%d", &cur_e);
				getchar();
				if (PriorElem(L, cur_e, pre_e) == 1)//如果cur_e存在前驱
					printf("cur_e的前驱为%d\n", pre_e);
				else printf("cur_e的前驱不存在\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 9:
			if (L.elem)//若表存在
			{
				ElemType cur_e, next_e;
				printf("输入一个数字，为cur_e赋值\n");
				scanf("%d", &cur_e);
				getchar();
				if (NextElem(L, cur_e, next_e) == 1)//如果cur_e存在后继
					printf("cur_e的后继为%d\n", next_e);
				else printf("cur_e的后继不存在\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 10:
			if (L.elem)//若表存在
			{
				printf("输入要插入的位置\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L) + 1)//i值合法
				{
					ElemType e;//插入的元素
					printf("输入一个数字，为e赋值\n");
					scanf("%d", &e);
					getchar();
					if (ListInsert(L, i, e))
						printf("插入成功\n");
					else printf("插入失败\n");
				}
				else printf("位置i不合法\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 11:
			if (L.elem)//表存在
			{
				printf("输入要删除的数据元素位序\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L))
				{
					ElemType e;//删除的元素存放在e中
					getchar();
					if (ListDelete(L, i, e))
					{
						printf("删除成功\n");
						printf("删除的元素值为%d", e);
					}
					else printf("删除失败\n");
				}

				else printf("位置i不合法\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 12:
			if (L.elem)//若表存在
			{
				if (!ListTrabverse(L, visit)) printf("线性表是空表！\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 13:
			if (L.elem)//若表存在
			{
				if (Loaddata(L))
					printf("数据加载成功\n");
				else printf("数据加载失败\n");
			}
			else printf("表不存在\n");
			getchar(); getchar();
			break;
		case 14:
			if (L.elem)//若表存在
			{
				if (Savedata(L))
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
status InitiaList(SqList & L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);//如果内存不足创建失败，则异常退出
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;//创建成功
}
status DestroyList(SqList & L) {
	free(L.elem);//释放空间
	L.elem = NULL;//表址指向空
	L.length = L.listsize = 0;//表厂及表大小置0

	return TRUE;//销毁成功
}
status ClearList(SqList & L) {
	L.length = 0;//置表长为0
	return TRUE;
}
status ListEmpty(SqList L) {
	if (L.length == 0)
		return TRUE;//如果L为空表(即表长==0)，返回TRUE;
	else return FALSE;//否则返回FALSE;
}

status ListLength(SqList L) {
	return L.length;//返回元素个数
}

status GetElem(SqList L, int i, ElemType & e) {
		e = L.elem[i - 1];//使用取址公式定位第i个元素并赋值给e
		return OK;
}

status LocatElem(SqList L, ElemType e, status(*compare)(ElemType x, ElemType y))
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (compare(L.elem[i], e) == 0)//compare函数比较两个参数，相同返回0
			return i + 1;//返回第一个与e满足关系compare的数据元素的位序
	}
	return FALSE;//不存在返回0
}

status PriorElem(SqList L, ElemType cur, ElemType & pre_e) {
	int order = LocatElem(L, cur, compare);//查找cur元素获取其序号（cur不在表中order为0）
	if (order > 1)//如果cur在L中且不为第一个元素
	{
		pre_e = L.elem[order - 2];//cur的前驱值赋给&pre_e
		return TRUE;
	}
	return FALSE;
}
status NextElem(SqList L, ElemType cur, ElemType & next_e) {
	int order = LocatElem(L, cur, compare);//查找cur元素获取其序号
	if (order >= 1 && order<L.length)//如果cur在L中且不为最后一个元素
	{
		next_e = L.elem[order];//cur的后继值赋给&next_e
		return TRUE;
	}
	return FALSE;
}


status ListInsert(SqList & L, int i, ElemType e) {
	if (L.length + 1 >= L.listsize)//空间已满，增配空间
	{
		ElemType * newbase;
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (newbase == NULL)
			return FALSE;//分配失败
		L.elem = newbase;//新基址
		L.listsize += LISTINCREMENT;//增加容量
	}
	//i之后的元素依次后移
	ElemType *in_i = &(L.elem[i - 1]);//in_i指向将要插入的位置
	ElemType *cur;
	for (cur = &(L.elem[L.length - 1]); cur >= in_i; cur--)
		*(cur + 1) = *cur;
	*in_i = e;//i处插入e
	L.length++;//表长加1
	return TRUE;
}

status ListDelete(SqList & L, int i, ElemType & e)
{
	e = L.elem[i - 1];//赋值e
	ElemType *tail = &L.elem[L.length - 1];//tail指向表尾的位置
	ElemType *cur;
	for (cur = &(L.elem[i - 1]); cur < tail; cur++)
		*cur = *(cur + 1);//i之后的元素依次前移
	L.length--;//表长减1
	return TRUE;
}


status ListTrabverse(SqList L, status(*visit)(ElemType e)) {
		int i;
		printf("\n-------------------- all elements ------------------------------\n");
		for (i = 0; i < L.length; i++)
		{
			if (!visit(L.elem[i])) return ERROR;//如果visit失败，则退出
		}
		printf("\n------------------------- end ----------------------------------\n");

   return L.length;//遍历完毕，返回遍历的元素个数
}
status compare(ElemType x, ElemType y)
{/*通过内存比较判断x和y元素,相等返回0，x<y返回0-，x>y返回0+*/
	return memcmp(&x, &y, sizeof(ElemType));
}
status Loaddata(SqList &L)
{
	FILE *fp;
	L.length = 0;
	if ((fp = fopen(FILENAME, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))//每次读取一个数据元素，顺序写入打顺序表中
	{
		if (L.length + 1 >= L.listsize)//空间已满，增配空间
		{
			ElemType * newbase;
			newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
			if (newbase == NULL)
				return FALSE;//分配失败
			L.elem = newbase;//新基址
			L.listsize += LISTINCREMENT;//增加容量
		}
		L.length++;//准备写入下一个元素
	}
	fclose(fp);
	return TRUE;//写入完毕

}
status Savedata(SqList L)
{
	FILE *fp;
	if ((fp = fopen(FILENAME, "w")) == NULL)//打开文件失败
	{
		printf("File open erroe\n ");
		return FALSE;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);//从地址L.elem开始，往后sizeof(ElemType)*L.length个字节的数据一次性写入到文件中
	fclose(fp);//关闭文件
	return TRUE;
}
status visit(ElemType e)
{
	printf("%d ", e);
	return TRUE;
}
