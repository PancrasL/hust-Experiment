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
#define QUEUESIZE 100 //���еĴ�С
#define L_DATA_NAME "ListData"
#define T_DATA_NAME "TreeData"

typedef int status;

typedef struct {
	struct treedata * pT;
	int listlenth;
	int listsize;
}SqList;//˳������ڹ��������

typedef struct treedata {
	struct bitnode * pRoot;
	char  name[20];
}TreeData;//��������Ϣ(���Ա�Ľ��)

typedef char TElemtype;//��������������
typedef int KEY;//�����Ĺؼ�������
typedef struct elemType
{
	KEY key;
	TElemtype e;
}ElemType; //�����������Ԫ�����Ͷ���

typedef struct bitnode {
	struct bitnode * lchild;
	ElemType data;
	struct bitnode * rchild;
}BiTNode, *BiTree;//���������㶨��



status InitBiTree(BiTree *T);
status DestroyBiTree(BiTree *T);
status CreateBiTree(BiTree *T, ElemType * &definition);
//definition����"�ؼ��� �ַ�"��ʽ����ǰ����������������"0 #"��ʾ
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
	L.pT = (TreeData *)malloc(LIST_INIT_SIZE * sizeof(TreeData));//���Ա����ɹ���LIST_INIT_SIZE����
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
		printf("    	 21. ������������		22. ������������\n");
		printf("    	 23. �����������\n");
		printf("    	 0. Exit\n");
		if (L.listlenth != 0)	printf("************************��ǰ�������Ϊ%s**************************\n\n", pMyTree->name);
		else printf("************************��ǰû���������ȳ�ʼ��������ļ��м�������*******************\n\n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~23]:");
		scanf("%d", &op);

		if (L.listlenth == 0 && (op != 1 && op != 22))
		{
			printf("�����������ڣ����ȳ�ʼ����\n");
			getchar(); getchar();
			continue;
		}
		switch (op) {
		case 1:
		{
			if (L.listlenth >= L.listsize)
			{
				printf("�ռ䲻�㣬�޷�������\n");
				break;
			}

			InitBiTree(&(L.pT[L.listlenth].pRoot));//�����Ա��β����һ����
			printf("������������:\n");
			scanf_s("%s", L.pT[L.listlenth].name,20);
			mytree = L.listlenth;
			pMyTree = &L.pT[mytree];
			printf("������%s�����ɹ���\n", L.pT[L.listlenth].name);
			L.listlenth++;//���Ա�ͬ������һ����

			getchar(); getchar();
			break;
		}
		case 2:
		{
			DestroyBiTree(&(pMyTree->pRoot));
			printf("������%s���ٳɹ���\n", pMyTree->name);

			for (i = mytree; i < L.listlenth - 1; i++)
			{
				L.pT[i] = L.pT[i + 1];
			}
			L.listlenth--;//���Ա�ͬ��ɾ��һ����
			mytree = 0;
			pMyTree = &L.pT[mytree];
			getchar(); getchar();
			break;
		}
		case 3:
		{
			ElemType def[500];//����������
			ElemType *definition = def;
			int i;
			i = 0;
			for (i = 0; i < 500; i++)
			{
				def[i].e = '#';
				def[i].key = 0;
			}//��ʼ����㶨���Ϊ��
			int N;
			i = 0;
			printf("������������:\n");
			scanf("%d", &N);
			if (N > 2000)
			{
				printf("����������\n");
				system("pause");
				break;
			}
			printf("��������\n");
			while (N--)
			{
				scanf("%d %c", &def[i].key, &def[i].e);//��ȡ������
				i++;
			}
			CreateBiTree(&pMyTree->pRoot, definition);
			printf("��%s�����ɹ�\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 4:
		{
			printf("���ǰ����ǰ����������\n");
			PreOrderTraverse(pMyTree->pRoot, visit);
			ClearBiTree(&pMyTree->pRoot);
			printf("��%s��ճɹ�\n", pMyTree->name);
			printf("��պ�����ǰ����������\n");
			PreOrderTraverse(pMyTree->pRoot, visit);
			getchar(); getchar();
			break;
		}
		case 5:
		{
			if (BiTreeEmpty(pMyTree->pRoot))
				printf("��%sΪ��\n", pMyTree->name);
			else printf("��%s��Ϊ��\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 6:
		{
			printf("��%s�����Ϊ%d\n", pMyTree->name, BiTreeDepth(pMyTree->pRoot));
			getchar(); getchar();
			break;
		}
		case 7:
		{
			if (pMyTree->pRoot) {//���ڵ�ǿ�
				BiTNode *p;
				p = Root(pMyTree->pRoot);
				printf("��%s�ĸ����ؼ���Ϊ%d��ֵΪ%c\n", pMyTree->name, p->data.key, p->data.e);
			}
			else printf("��%sΪ��\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 8:
		{
			if (pMyTree->pRoot)//���ڵ�ǿ�
			{
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				p = Value(pMyTree->pRoot, e);
				if (p)//���������
					printf("�ؼ��֣�%d ֵ��%c\n", p->data.key, p->data.e);
				else printf("�ؼ���Ϊ%d������㲻����\n", e);
			}
			else printf("��%sΪ��\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 9:
		{
			if (pMyTree->pRoot) //���ڵ�ǿ�
			{
				KEY key;
				ElemType value;
				printf("����ǰ���:\n");
				PreOrderTraverse(pMyTree->pRoot, visit);//չʾ���
				printf("������Ĺؼ���:\n");
				scanf("%d", &key);
				printf("������ĺ�Ľ��Ĺؼ��ֺ�ֵ(��ʽ�磺1 c):\n");
				scanf("%d %c", &value.key, &value.e);
				if (Assign(pMyTree->pRoot, key, value))//��ֵ�ɹ�
				{
					printf("���ĺ���:\n");
					char *p1 = "key";
					char *p2 = "data";
					printf("%10s%10s\n", p1, p2);
					PreOrderTraverse(pMyTree->pRoot, visit);//չʾ���
				}
				else printf("��㲻����\n");
			}
			else printf("��%sΪ��\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 10:
		{
			if (pMyTree->pRoot)//���ڵ�ǿ�
			{
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				p = Parent(pMyTree->pRoot, e);
				if (p)//����˫�׽��
				{
					printf("˫�׽���ַΪ��%p������Ϊ��%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("��˫�׽��\n");
			}
			else printf("��%sΪ��\n", pMyTree->name);
			getchar(); getchar();
			break;
		}
		case 11:
		{
			if (pMyTree->pRoot == NULL)//���ڵ�Ϊ��
				printf("��%sΪ��\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("�ý�㲻������\n"); getchar(); getchar(); break;
				}//�жϹؼ���Ϊe�Ľ���Ƿ�������,��������������case
				p = LeftChild(pMyTree->pRoot, e);
				if (p)//���������
				{
					printf("���ӽ���ַΪ��%p������Ϊ��%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("������\n");
			}
			getchar(); getchar();
			break;
		}
		case 12:
		{
			if (pMyTree->pRoot == NULL)
				printf("��%sΪ��\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("�ý�㲻������\n"); getchar(); getchar(); break;
				}
				p = RightChild(pMyTree->pRoot, e);
				if (p)//������Һ���
				{
					printf("�Һ��ӽ���ַΪ��%p������Ϊ��%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("���Һ���\n");
			}
			getchar(); getchar();
			break;
		}
		case 13:
		{
			if (pMyTree->pRoot == NULL)
				printf("��%sΪ��\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("�ý�㲻������\n"); getchar(); getchar(); break;
				}
				p = LeftSibling(pMyTree->pRoot, e);
				if (p)//�����ֵ�
				{
					printf("�ý�����ֵܵ�ַΪ��%p������Ϊ��%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("�����ֵ�\n");
			}
			getchar(); getchar();
			break;
		}
		case 14:
		{
			if (pMyTree->pRoot == NULL)
				printf("��%sΪ��\n", pMyTree->name);
			else {
				BiTNode *p;
				KEY e;
				printf("����ؼ���\n");
				scanf(" %d", &e);
				if (!Value(pMyTree->pRoot, e))
				{
					printf("�ý�㲻������\n"); getchar(); getchar(); break;
				}
				p = RightSibling(pMyTree->pRoot, e);
				if (p)
				{
					printf("�ý�����ֵܵ�ַΪ��%p������Ϊ��%d %c\n", p, p->data.key, p->data.e);
				}
				else printf("�����ֵ�\n");
			}
			getchar(); getchar();
			break;
		}
		case 15:
		{
			if (pMyTree->pRoot == NULL)
				printf("������%sΪ��\n", pMyTree->name);
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
				printf("������%sΪ��\n", pMyTree->name);
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
				printf("������%sΪ��\n", pMyTree->name);
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
				printf("������%sΪ��\n", pMyTree->name);
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
			printf("�����뽫Ҫ����������\n");
			{
				ElemType def[500];//����������
				ElemType *definition = def;
				int i;
				i = 0;
				for (i = 0; i < 500; i++)
				{
					def[i].e = '#';
					def[i].key = 0;
				}//��ʼ����㶨���Ϊ��
				int N;
				i = 0;
				printf("������������:\n");
				scanf("%d", &N);
				if (N > 2000)
				{
					printf("����������\n");
					system("pause");
					break;
				}
				printf("��������\n");
				while (N--)
				{
					scanf("%d %c", &def[i].key, &def[i].e);//��ȡ������
					i++;
				}
				CreateBiTree(&c, definition);
				printf("����c�����ɹ�\n");
			}
			printf("����c��ǰ��������:\n");
			PreOrderTraverse(c, visit);
			int key, LR;
			printf("����Ҫ���������Ľ��Ĺؼ���:");
			scanf("%d", &key);
			p = Value(pMyTree->pRoot, key);
			printf("����Ҫ�����λ�ã�0.������ 1.������");
			scanf("%d", &LR);
			if (LR != 0 && LR != 1)
			{
				printf("λ���������\n");
			}
			else if (c->rchild == NULL)
			{
				InsertChild(pMyTree->pRoot, p, LR, c);
				printf("��������ɹ�,������ǰ����������\n");
				PreOrderTraverse(pMyTree->pRoot, visit);

			}
			getchar(); getchar(); break;
		}
		case 20:
		{
			BiTNode *p;
			int key, LR;
			printf("����Ҫɾ�������Ľ��Ĺؼ���:");
			scanf("%d", &key);
			p = Value(pMyTree->pRoot, key);
			printf("����Ҫɾ����������λ�ã�0.������ 1.������");
			scanf("%d", &LR);
			if (LR != 0 && LR != 1)
			{
				printf("λ���������\n");
			}
			else
			{
				DeleteChild(pMyTree->pRoot, p, LR);
				printf("����ɾ���ɹ���ɾ�����ǰ����������\n");
				
				PreOrderTraverse(pMyTree->pRoot, visit);
			}
			getchar(); getchar(); break;
		}
		case 21:
		{
			SaveData(L);
			printf("���ݱ���ɹ�\n");
			getchar(); getchar();
			break;
		}
		case 22:
		{
			if (L.listlenth)
				printf("���Ա�ǿգ��޷���ʼ���������������ټ�������\n");
			else
			{
				if (LoadData(L))
					printf("���ݼ��سɹ�\n");
				mytree = 0;
				pMyTree = &L.pT[mytree];
			}
			getchar(); getchar();
			break;
		}
		case 23:
		{
			mytree = SelectTree(L);//��TreeNum������ѡ��һ����
			pMyTree = &L.pT[mytree];
			getchar(); getchar();
			break;
		}
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

 /*--------------------page 23 on textbook ----------------------------------*/
status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}
status DestroyBiTree(BiTree *T)
{
	BiTNode *pnode = *T;//pnodeָ������
	if (pnode)//���������
	{
		if (pnode->lchild)//���������
			DestroyBiTree(&(pnode->lchild));
		if (pnode->rchild)//������Һ���
			DestroyBiTree(&(pnode->rchild));
		free(pnode);//�ͷŸ��ڵ�
	}
	return OK;
}
status CreateBiTree(BiTree *T, ElemType * &definition)
{
	if ((*definition).e == '#' && (*definition).key == 0)
	{
		*T = NULL;//# 0��ʾ�ýڵ�������
		definition++;//definitionָ����һ��Ԫ��
	}
	else
	{
		if (!(*T = (BiTNode *)malloc(sizeof(BiTNode))))//����һ�������
			exit(OVERFLOW);//�ռ����ʧ��
		(*T)->data = *(definition++);//�������ڵ�,definitionָ����һ��Ԫ��
		CreateBiTree(&(*T)->lchild, definition);//����������
		CreateBiTree(&(*T)->rchild, definition);//����������
	}
	return OK;
}
status ClearBiTree(BiTree *T)
{
	BiTNode *pnode = *T;//pnodeָ������
	if (pnode)//���������
	{
		if (pnode->lchild)//���������
			ClearBiTree(&(pnode->lchild));
		if (pnode->rchild)//������Һ���
			ClearBiTree(&(pnode->rchild));
		free(pnode);//��ո����
		*T = NULL;//�ÿ���ָ��
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
	if (!T)//�����Ϊ��
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild); // ���������
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);  // ���������
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
		p = stack[top--];//��ջ
		if (p->data.key == e) return p;
		if (p->rchild) //������Һ���
			stack[++top] = p->rchild;//�Һ��ӽ�ջ
		if (p->lchild)//��������� 
			stack[++top] = p->lchild;
	}//ջ�գ�δ�ҵ�
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
	if (p->data.key != e)//��㲻����
		return FALSE;
	else p->data = value;
	return TRUE;
}

BiTNode * Parent(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;//���ڵ��ջ
	if (T->data.key == e)
		return NULL;//eΪ���ڵ�
	while (top>-1)
	{
		p = stack[top--];//��ջ
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
	stack[++top] = T;//���ڵ��ջ
	if (T->data.key == e)
		return NULL;//eΪ���ڵ㣬�����ֵ�
	while (top>-1)
	{
		p = stack[top--];//��ջ
		if (p->lchild)
		{
			stack[++top] = p->lchild;
		}
		if (p->rchild)
		{
			if (p->rchild->data.key == e)//p���Һ��ӹؼ���Ϊe
				return p->lchild;//����p������
			stack[++top] = p->rchild;
		}
	}
	return NULL;//�����޹ؼ���Ϊe�Ľ�㣬���ؿ�
}
BiTNode * RightSibling(BiTree T, KEY e)
{
	int top = -1;
	BiTree stack[100], p;
	stack[++top] = T;//���ڵ��ջ
	if (T->data.key == e)
		return NULL;//eΪ���ڵ㣬�����ֵ�
	while (top>-1)
	{
		p = stack[top--];//��ջ

		if (p->lchild)
		{
			if (p->lchild->data.key == e) // p�����ӹؼ���Ϊe
				return p->rchild;//����p���Һ���
			stack[++top] = p->lchild;
		}
		if (p->rchild)
		{
			stack[++top] = p->rchild;
		}
	}
	return NULL;//�����޹ؼ���Ϊe�Ľ�㣬���ؿ�
}
status InsertChild(BiTree T, BiTNode *p, int LR, BiTree c)
{
	BiTNode *temp;
	if (LR == 0)//c���뵽p��������
	{
		temp = p->lchild;//p��ԭ��������ַ
		p->lchild = c;//c���뵽p��������
		c->rchild = temp;//p��ԭ���������뵽c��������
	}
	else//c���뵽p��������
	{
		temp = p->rchild;
		p->rchild = c;
		c->rchild = temp;
	}
	return OK;
}
status DeleteChild(BiTree T, BiTNode *p, int LR)
{
	if (LR == 0)//ɾ��p��������
	{
		ClearBiTree(&p->lchild);
	}
	else//ɾ��p��������
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
	head = 0; tail = 0;//�ӿգ�head==tail,������(tail+1)%QUEUESIZE==head
	queue[tail++] = T;//���ڵ����
	while (tail != head && (tail + 1) % QUEUESIZE != head)//�ӷǿ��ҷ���
	{
		p = queue[head];//����
		head = (head + 1) % QUEUESIZE;
		visit(p->data);
		if (p->lchild)
		{//���ӽ���
			queue[tail] = p->lchild;
			tail = (tail + 1) % QUEUESIZE;
		}
		if (p->rchild)
		{//�Һ��ӽ���
			queue[tail] = p->rchild;
			tail = (tail + 1) % QUEUESIZE;
		}
	}
	return OK;
}

int SelectTree(SqList L)
{
	int i, op;
	printf("������ѡ��������(1-%d)\n", L.listlenth);
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
	/*�������Ա���Ϣ*/
	if ((fp = fopen(L_DATA_NAME, "w")) == NULL)//���ļ�ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	fwrite(L.pT, sizeof(TreeData), L.listlenth, fp);//���Ա�����һ����д�뵽�ļ���
	fclose(fp);
	/*�����������Ϣ*/
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
	/*д�����Ա�����*/
	FILE *fp;
	if ((fp = fopen(L_DATA_NAME, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}

	while (fread(&L.pT[L.listlenth], sizeof(TreeData), 1, fp))
	{
		L.listlenth++;//׼��д����һ������
	}
	fclose(fp);

	/*д�����������*/
	if ((fp = fopen(T_DATA_NAME, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	int i;
	for (i = 0; i < L.listlenth; i++)
	{
		LoadTree(L.pT[i].pRoot, fp);
	}
	return TRUE;//д�����
}
status LoadTree(BiTree &T, FILE *fp)
{
	int key; char c;
	fscanf(fp, "%d %c", &key, &c);
	if (key == 0 && c == '#')
	{
		T = NULL;//# 0��ʾ�ýڵ�������
	}
	else
	{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))//����һ�������
			exit(OVERFLOW);//�ռ����ʧ��
		T->data.key = key;
		T->data.e = c;
		LoadTree(T->lchild, fp);//����������
		LoadTree(T->rchild, fp);//����������
	}
	return OK;
}