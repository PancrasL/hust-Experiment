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
#define LIST_INIT_SIZE 50
#define QUEUESIZE 100 //队列的大小
#define L_DATA_NAME "ListData"
#define T_DATA_NAME "TreeData"

typedef int status;

typedef struct {
	struct treedata * pT;
	int listlenth;
	int listsize;
}SqList;//顺序表，用于管理二叉树

typedef struct treedata {
	struct bitnode * pRoot;
	char  name[20];
}TreeData;//二叉树信息(线性表的结点)

typedef char TElemtype;//树结点的数据类型
typedef int KEY;//树结点的关键字类型
typedef struct elemType
{
	KEY key;
	TElemtype e;
}ElemType; //树结点中数据元素类型定义

typedef struct bitnode {
	struct bitnode * lchild;
	ElemType data;
	struct bitnode * rchild;
}BiTNode, *BiTree;//二叉链表结点定义



status InitBiTree(BiTree *T);
status DestroyBiTree(BiTree *T);
status CreateBiTree(BiTree *T, ElemType * &definition);
//definition：以"关键字 字符"形式给出前序遍历结果，空树用"0 #"表示
status ClearBiTree(BiTree *T);
status BiTreeEmpty(BiTree T);
status BiTreeDepth(BiTree T);
BiTNode *Root(BiTree T);
BiTNode *Value(BiTree T, KEY e);
status Assign(BiTree T, KEY e, ElemType value);
BiTNode * Parent(BiTree T, KEY e);
BiTNode * LeftChild(BiTree T, KEY e);
BiTNode * RightChild(BiTree T, KEY e);
BiTNode * LeftSibling(BiTree T, KEY e);
BiTNode * RightSibling(BiTree T, KEY e);

status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c);

status DeleteChild(BiTree T, BiTNode *p, int LR);

status PreOrderTraverse(BiTree T, void(*visit)(ElemType e));
status InOrderTraverse(BiTree T, void(*visit)(ElemType e));
status PostOrderTraverse(BiTree T, void(*visit)(ElemType e));
status LevelOrderTraverse(BiTree T, void(*visit)(ElemType e));
status SaveData(SqList L);
status SaveTree(BiTree T, FILE *fp);
status LoadData(SqList &L);
status LoadTree(BiTree &T, FILE *fp);
int SelectTree(SqList L);
void visit(ElemType e);
/*------------------------------------------------------*/
int main(void) {
	SqList L;
	L.pT = (TreeData *)malloc(LIST_INIT_SIZE * sizeof(TreeData));//线性表最多可管理LIST_INIT_SIZE棵树
	L.listsize = LIST_INIT_SIZE;
	L.listlenth = 0;

	int mytree;
	TreeData *pMyTree = NULL;
	int op = 1;
	int i;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. InitBiTree			11. LeftChild\n");
		printf("    	  2. DestroyBiTree		12. RightChild\n");
		printf("    	  3. CreateBiTree		13. LeftSibling \n");
		printf("    	  4. ClearBiTree		14. RightSibling\n");
		printf("    	  5. BiTreeEmpty		15. PreOrderTraverse\n");
		printf("    	  6. BiTreeDepth		16. InOrderTraverse\n");
		printf("    	  7. Root			17. PostOrderTraverse\n");
		printf("    	  8. Value			18. LevelOrderTraverse\n");
		printf("    	  9. Assign			19. InsertChild\n");
		printf("    	 10. Parent			20. DeleteChild\n");
		printf("    	 21. 保存树的数据		22. 加载树的数据\n");
		printf("    	 23. 更换管理的树\n");
		printf("    	 0. Exit\n");
		if (L.listlenth != 0)	printf("************************当前管理的树为%s**************************\n\n", pMyTree->name);
		else printf("************************当前没有树，请先初始化树或从文件中加载数据*******************\n\n");
		printf("------------------------------------------------------\n");
		printf("    请选择你的操作[0~23]:");
		scanf("%d", &op);

		if (L.listlenth == 0 && (op != 1 && op != 22))
		{
			printf("二叉树不存在，请先初始化树\n");
			getchar(); getchar();
			continue;
		}
		switch (op) {
		case 1:
		{
			if (L.listlenth >= L.listsize)
			{
				printf("空间不足，无法创建树\n");
				break;
			}

			InitBiTree(&(L.pT[L.listlenth].pRoot));//在线性表表尾创建一棵树
			printf("输入树的名称:\n");
			scanf_s("%s", L.pT[L.listlenth].name,20);
			mytree = L.listlenth;
			pMyTree = &L.pT[mytree];
			printf("二叉树%s创建成功！\n", L.pT[L.listlenth].name);
			L.listlenth++;//线性表同步创建一棵树

			getchar(); getchar();
			break;
		}
		case 2:
		{
			DestroyBiTree(&(pMyTree->pRoot));
			printf("二叉树%s销毁成功！\n", pMyTree->name);

			for (i = mytree; i < L.listlenth - 1; i++)
			{
				L.pT[i] = L.pT[i + 1];
			}
			L.listlenth--;//线性表同步删除一棵树
			mytree = 0;
			pMyTree = &L.pT[mytree];
			getchar(); getchar();
			break;
		}
		case 3:
		{
			ElemType def[500];//二叉树定义
			ElemType *definition = def;
			int i;
			i = 0;
			for (i = 0; i < 500; i++)
			{
				def[i].e = '#';
				def[i].key = 0;
			}//初始树结点定义均为空
			int N;
			i = 0;
			printf("输入数据组数:\n");
			scanf("%d", &N);
			if (N > 2000)
			{
				printf("数据量过大\n");
				system("pause");
				break;
			}
			printf("输入数据\n");
			while (N--)
			{
				scanf("%d %c", &def[i].key, &def[i].e);//读取树定义
				i++;
			}
			CreateBiTree(&pMyTree->pRoot, definition);
			printf("树%s创建成功\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 4:
		{
			printf("清空前树的前序遍历结果：\n");
			PreOrderTraverse(pMyTree->pRoot, visit);
			ClearBiTree(&pMyTree->pRoot);
			printf("树%s清空成功\n", pMyTree->name);
			printf("清空后树的前序遍历结果：\n");
			PreOrderTraverse(pMyTree->pRoot, visit);
			getchar(); getchar();
			break;
		}
		case 5:
		{
			if (BiTreeEmpty(pMyTree->pRoot))
				printf("树%s为空\n", pMyTree->name);
			else printf("树%s不为空\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 6:
		{
			printf("树%s的深度为%d\n", pMyTree->name, BiTreeDepth(pMyTree->pRoot));
			getchar(); getchar();
			break;
		}
		case 7:
		{
			if (pMyTree->pRoot) {//根节点非空
				BiTNode *p;
				p = Root(pMyTree->pRoot);
				printf("树%s的根结点关键字为%d，值为%c\n", pMyTree->name, p->data.key, p->data.e);
			}
			else printf("树%s为空\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 8:
		{
			if (pMyTree->pRoot)//根节点非空
			{
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				p = Value(pMyTree->pRoot, e);
				if (p)//结点在树中
					printf("关键字：%d 值：%c\n", p->data.key, p->data.e);
				else printf("关键字为%d的树结点不存在\n", e);
			}
			else printf("树%s为空\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			if (pMyTree->pRoot) //根节点非空
			{
				KEY key;
				ElemType value;
				printf("更改前结果:\n");
				PreOrderTraverse(pMyTree->pRoot, visit);//展示结果
				printf("输入结点的关键字:\n");
				scanf("%d", &key);
				printf("输入更改后的结点的关键字和值(格式如：1 c):\n");
				scanf("%d %c", &value.key, &value.e);
				if (Assign(pMyTree->pRoot, key, value))//赋值成功
				{
					printf("更改后结果:\n");
					char *p1 = "key";
					char *p2 = "data";
					printf("%10s%10s\n", p1, p2);
					PreOrderTraverse(pMyTree->pRoot, visit);//展示结果
				}
				else printf("结点不存在\n");
			}
			else printf("树%s为空\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 10:
		{
			if (pMyTree->pRoot)//根节点非空
			{
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				p = Parent(pMyTree->pRoot, e);
				if (p)//存在双亲结点
				{
					printf("双亲结点地址为：%p，数据为：%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("无双亲结点\n");
			}
			else printf("树%s为空\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 11:
		{
			if (pMyTree->pRoot == NULL)//根节点为空
				printf("树%s为空\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("该结点不在树中\n"); getchar(); getchar(); break;
				}//判断关键字为e的结点是否在树中,若不在树中跳出case
				p = LeftChild(pMyTree->pRoot, e);
				if (p)//如果有左孩子
				{
					printf("左孩子结点地址为：%p，数据为：%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("无左孩子\n");
			}
			getchar(); getchar();
			break;
		}
		case 12:
		{
			if (pMyTree->pRoot == NULL)
				printf("树%s为空\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("该结点不在树中\n"); getchar(); getchar(); break;
				}
				p = RightChild(pMyTree->pRoot, e);
				if (p)//如果有右孩子
				{
					printf("右孩子结点地址为：%p，数据为：%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("无右孩子\n");
			}
			getchar(); getchar();
			break;
		}
		case 13:
		{
			if (pMyTree->pRoot == NULL)
				printf("树%s为空\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("该结点不在树中\n"); getchar(); getchar(); break;
				}
				p = LeftSibling(pMyTree->pRoot, e);
				if (p)//有左兄弟
				{
					printf("该结点左兄弟地址为：%p，数据为：%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("无左兄弟\n");
			}
			getchar(); getchar();
			break;
		}
		case 14:
		{
			if (pMyTree->pRoot == NULL)
				printf("树%s为空\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("输入关键字\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("该结点不在树中\n"); getchar(); getchar(); break;
				}
				p = RightSibling(pMyTree->pRoot, e);
				if (p)
				{
					printf("该结点右兄弟地址为：%p，数据为：%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("无右兄弟\n");
			}
			getchar(); getchar();
			break;
		}
		case 15:
		{
			if (pMyTree->pRoot == NULL)
				printf("二叉树%s为空\n", pMyTree->name);
			else {
				char *p1 = "key";
				char *p2 = "data";
				printf("%10s%10s\n", p1, p2);
				PreOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar();
			break;
		}
		case 16:
		{
			if (pMyTree->pRoot == NULL)
				printf("二叉树%s为空\n", pMyTree->name);
			else {
				char *p1 = "key";
				char *p2 = "data";
				printf("%10s%10s\n", p1, p2);
				InOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar();
			break;
		}
		case 17:
		{
			if (pMyTree->pRoot == NULL)
				printf("二叉树%s为空\n", pMyTree->name);
			else {
				char *p1 = "key";
				char *p2 = "data";
				printf("%10s%10s\n", p1, p2);
				PostOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar();
			break;
		}
		case 18:
		{
			if (pMyTree->pRoot == NULL)
				printf("二叉树%s为空\n", pMyTree->name);
			else {
				char *p1 = "key";
				char *p2 = "data";
				printf("%10s%10s\n", p1, p2);
				LevelOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar();
			break;
		}
		case 19:
		{
			BiTNode *p;
			BiTree c;
			printf("请输入将要创建的子树\n");
			{
				ElemType def[500];//二叉树定义
				ElemType *definition = def;
				int i;
				i = 0;
				for (i = 0; i < 500; i++)
				{
					def[i].e = '#';
					def[i].key = 0;
				}//初始树结点定义均为空
				int N;
				i = 0;
				printf("输入数据组数:\n");
				scanf("%d", &N);
				if (N > 2000)
				{
					printf("数据量过大\n");
					system("pause");
					break;
				}
				printf("输入数据\n");
				while (N--)
				{
					scanf("%d %c", &def[i].key, &def[i].e);//读取树定义
					i++;
				}
				CreateBiTree(&c, definition);
				printf("子树c创建成功\n");
			}
			printf("子树c的前序遍历结果:\n");
			PreOrderTraverse(c, visit);
			int key, LR;
			printf("输入要插入子树的结点的关键字:");
			scanf("%d", &key);
			p = Value(pMyTree->pRoot, key);
			printf("输入要插入的位置：0.左子树 1.右子树");
			scanf("%d", &LR);
			if (LR != 0 && LR != 1)
			{
				printf("位置输入错误\n");
			}
			else if (c->rchild == NULL)
			{
				InsertChild(pMyTree->pRoot, p, LR, c);
				printf("子树插入成功,插入后的前序遍历结果：\n");
				PreOrderTraverse(pMyTree->pRoot, visit);

			}
			getchar(); getchar(); break;
		}
		case 20:
		{
			BiTNode *p;
			int key, LR;
			printf("输入要删除子树的结点的关键字:");
			scanf("%d", &key);
			p = Value(pMyTree->pRoot, key);
			printf("输入要删除的子树的位置：0.左子树 1.右子树");
			scanf("%d", &LR);
			if (LR != 0 && LR != 1)
			{
				printf("位置输入错误\n");
			}
			else
			{
				DeleteChild(pMyTree->pRoot, p, LR);
				printf("子树删除成功，删除后的前序遍历结果：\n");
				
				PreOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar(); break;
		}
		case 21:
		{
			SaveData(L);
			printf("数据保存成功\n");
			getchar(); getchar();
			break;
		}
		case 22:
		{
			if (L.listlenth)
				printf("线性表非空，无法初始化，请销毁树后再加载数据\n");
			else
			{
				if (LoadData(L))
					printf("数据加载成功\n");
				mytree = 0;
				pMyTree = &L.pT[mytree];
			}
			getchar(); getchar();
			break;
		}
		case 23:
		{
			mytree = SelectTree(L);//从TreeNum棵树中选择一棵树
			pMyTree = &L.pT[mytree];
			getchar(); getchar();
			break;
		}
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()

 /*--------------------page 23 on textbook ----------------------------------*/
status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}
status DestroyBiTree(BiTree *T)
{
	BiTNode *pnode = *T;//pnode指向树根
	if (pnode)//如果树存在
	{
		if (pnode->lchild)//如果有左孩子
			DestroyBiTree(&(pnode->lchild));
		if (pnode->rchild)//如果有右孩子
			DestroyBiTree(&(pnode->rchild));
		free(pnode);//释放根节点
	}
	return OK;
}
status CreateBiTree(BiTree *T, ElemType * &definition)
{
	if ((*definition).e == '#' && (*definition).key == 0)
	{
		*T = NULL;//# 0表示该节点无子树
		definition++;//definition指向下一个元素
	}
	else
	{
		if (!(*T = (BiTNode *)malloc(sizeof(BiTNode))))//声明一个树结点
			exit(OVERFLOW);//空间分配失败
		(*T)->data = *(definition++);//创建根节点,definition指向下一个元素
		CreateBiTree(&(*T)->lchild, definition);//创建左子树
		CreateBiTree(&(*T)->rchild, definition);//创建右子树
	}
	return OK;
}
status ClearBiTree(BiTree *T)
{
	BiTNode *pnode = *T;//pnode指向树根
	if (pnode)//如果树存在
	{
		if (pnode->lchild)//如果有左孩子
			ClearBiTree(&(pnode->lchild));
		if (pnode->rchild)//如果有右孩子
			ClearBiTree(&(pnode->rchild));
		free(pnode);//清空根结点
		*T = NULL;//置空树指针
	}
	return OK;
}
status BiTreeEmpty(BiTree T)
{
	if (T == NULL)
		return TRUE;
	else return FALSE;
}
BiTNode * Root(BiTree T)
{
	return T;
}
status BiTreeDepth(BiTree T)
{
	int i, j;
	if (!T)//如果树为空
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild); // 左子树深度
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);  // 右子树深度
	else
		j = 0;
	return i>j ? i + 1 : j + 1;
}
BiTNode *Value(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;
	while (top>-1) {
		p = stack[top--];//出栈
		if (p->data.key == e) return p;
		if (p->rchild) //如果有右孩子
			stack[++top] = p->rchild;//右孩子进栈
		if (p->lchild)//如果有左孩子 
			stack[++top] = p->lchild;
	}//栈空，未找到
	return NULL;
}
status Assign(BiTree T, KEY e, ElemType value)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;
	while (top>-1)
	{
		p = stack[top--];
		if (p->data.key == e)
			break;
		if (p->lchild) stack[++top] = p->lchild;
		if (p->rchild) stack[++top] = p->rchild;
	}
	if (p->data.key != e)//结点不存在
		return FALSE;
	else p->data = value;
	return TRUE;
}

BiTNode * Parent(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;//根节点进栈
	if (T->data.key == e)
		return NULL;//e为根节点
	while (top>-1)
	{
		p = stack[top--];//出栈
		if (p->lchild)
		{
			if (p->lchild->data.key == e)
				return p;
			stack[++top] = p->lchild;
		}
		if (p->rchild)
		{
			if (p->rchild->data.key == e)
				return p;
			stack[++top] = p->rchild;
		}
	}
	return NULL;
}
BiTNode * LeftChild(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;
	while (top>-1)
	{
		p = stack[top--];
		if (p->data.key == e)
			return p->lchild;
		if (p->lchild)
			stack[++top] = p->lchild;
		if (p->rchild)
			stack[++top] = p->rchild;
	}
	return NULL;
}
BiTNode * RightChild(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;
	while (top>-1)
	{
		p = stack[top--];
		if (p->data.key == e)
			return p->rchild;
		if (p->lchild)
			stack[++top] = p->lchild;
		if (p->rchild)
			stack[++top] = p->rchild;
	}
	return NULL;
}
BiTNode * LeftSibling(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;//根节点进栈
	if (T->data.key == e)
		return NULL;//e为根节点，无左兄弟
	while (top>-1)
	{
		p = stack[top--];//出栈
		if (p->lchild)
		{
			stack[++top] = p->lchild;
		}
		if (p->rchild)
		{
			if (p->rchild->data.key == e)//p的右孩子关键字为e
				return p->lchild;//返回p的左孩子
			stack[++top] = p->rchild;
		}
	}
	return NULL;//树中无关键字为e的结点，返回空
}
BiTNode * RightSibling(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;//根节点进栈
	if (T->data.key == e)
		return NULL;//e为根节点，无左兄弟
	while (top>-1)
	{
		p = stack[top--];//出栈

		if (p->lchild)
		{
			if (p->lchild->data.key == e) // p的左孩子关键字为e
				return p->rchild;//返回p的右孩子
			stack[++top] = p->lchild;
		}
		if (p->rchild)
		{
			stack[++top] = p->rchild;
		}
	}
	return NULL;//树中无关键字为e的结点，返回空
}
status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c)
{
	BiTNode *temp;
	if (LR == 0)//c插入到p的左子树
	{
		temp = p->lchild;//p的原左子树地址
		p->lchild = c;//c插入到p的左子树
		c->rchild = temp;//p的原左子树插入到c的右子树
	}
	else//c插入到p的右子树
	{
		temp = p->rchild;
		p->rchild = c;
		c->rchild = temp;
	}
	return OK;
}
status DeleteChild(BiTree T, BiTNode *p, int LR)
{
	if (LR == 0)//删除p的左子树
	{
		ClearBiTree(&p->lchild);
	}
	else//删除p的右子树
	{
		ClearBiTree(&p->rchild);
	}
	return OK;
}
status PreOrderTraverse(BiTree T, void(*visit)(ElemType e))
{
	if (T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
	return OK;
}
status InOrderTraverse(BiTree T, void(*visit)(ElemType e))
{
	if (T)
	{
		InOrderTraverse(T->lchild, visit);
		visit(T->data);
		InOrderTraverse(T->rchild, visit);
	}
	return OK;
}
status PostOrderTraverse(BiTree T, void(*visit)(ElemType e))
{
	if (T)
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
	}
	return OK;
}
status LevelOrderTraverse(BiTree T, void(*visit)(ElemType e))
{
	int head, tail;
	BiTree queue[QUEUESIZE], p;
	head = 0; tail = 0;//队空：head==tail,队满：(tail+1)%QUEUESIZE==head
	queue[tail++] = T;//根节点进队
	while (tail != head && (tail + 1) % QUEUESIZE != head)//队非空且非满
	{
		p = queue[head];//出队
		head = (head + 1) % QUEUESIZE;
		visit(p->data);
		if (p->lchild)
		{//左孩子进队
			queue[tail] = p->lchild;
			tail = (tail + 1) % QUEUESIZE;
		}
		if (p->rchild)
		{//右孩子进队
			queue[tail] = p->rchild;
			tail = (tail + 1) % QUEUESIZE;
		}
	}
	return OK;
}

int SelectTree(SqList L)
{
	int i, op;
	printf("请重新选择管理的树(1-%d)\n", L.listlenth);
	for (i = 1; i <= L.listlenth; i++)
	{
		printf("    	 %d. %s\n", i, L.pT[i - 1].name);
	}
	scanf("%d", &op);
	return op - 1;
}
void visit(ElemType e)
{
	printf("%10d%10c\n", e.key, e.e);
}
status SaveData(SqList L)
{
	FILE *fp;
	/*保存线性表信息*/
	if ((fp = fopen(L_DATA_NAME, "w")) == NULL)//打开文件失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	fwrite(L.pT, sizeof(TreeData), L.listlenth, fp);//线性表数据一次性写入到文件中
	fclose(fp);
	/*保存树结点信息*/
	fp = fopen(T_DATA_NAME, "w");
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		SaveTree(L.pT[i].pRoot, fp);
	}
	fclose(fp);

	return TRUE;
}
status SaveTree(BiTree T, FILE *fp)
{
	if (T)
	{
		fprintf(fp, "%d %c\n", T->data.key, T->data.e);
		SaveTree(T->lchild, fp);
		SaveTree(T->rchild, fp);
	}
	else
	{
		fprintf(fp, "0 #\n");
	}
	return OK;
}
status LoadData(SqList &L)
{
	/*写入线性表数据*/
	FILE *fp;
	if ((fp = fopen(L_DATA_NAME, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}

	while (fread(&L.pT[L.listlenth], sizeof(TreeData), 1, fp))
	{
		L.listlenth++;//准备写入下一个数据
	}
	fclose(fp);

	/*写入二叉树数据*/
	if ((fp = fopen(T_DATA_NAME, "r")) == NULL)//文件打开失败
	{
		printf("File open error\n ");
		return FALSE;
	}
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		LoadTree(L.pT[i].pRoot, fp);
	}
	return TRUE;//写入完毕
}
status LoadTree(BiTree &T, FILE *fp)
{
	int key; char c;
	fscanf(fp, "%d %c", &key, &c);
	if (key == 0 && c == '#')
	{
		T = NULL;//# 0表示该节点无子树
	}
	else
	{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))//声明一个树结点
			exit(OVERFLOW);//空间分配失败
		T->data.key = key;
		T->data.e = c;
		LoadTree(T->lchild, fp);//加载左子树
		LoadTree(T->rchild, fp);//加载右子树
	}
	return OK;
}