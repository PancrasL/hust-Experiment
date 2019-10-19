/*��ͷ������ʽ�洢�ṹ�����Ա�ʵ��*/
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
}Lnode; //����Ԫ�����Ͷ���


typedef Lnode* SqList;//ͷָ��

status IntiaList(SqList  *L);//LΪָ��ͷָ���ָ��
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
status Loaddata(SqList *L, char *filename);//��������
status Savedata(SqList L, char *filename);//��������
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
		printf("    	  13. ���ļ��ж�ȡ����\n");
		printf("    	  14. �����������ļ�\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);
		getchar();
		L = list_verify(&L1, &L2);//ȷ����Ҫ�����ı�
		switch (op) {
		case 1:
			if (*L == NULL)//�����Ա����ڣ��򴴽�
			{
				if (IntiaList(L) == OK) printf("���Ա����ɹ���\n");
				else printf("���Ա���ʧ�ܣ�\n");
				//printf("%p", (*L)->next);
			}
			else printf("���Ա��Ѵ���\n");
			getchar(); getchar();
			break;
		case 2:
			if (*L)//�������
			{
				DestroyList(L);
				printf("�����ٳɹ�\n");
				//printf("%p", *L);
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 3:
			if (*L)//�������
			{
				ClearList(L);
				printf("����ճɹ�\n");
				//printf("%p", *L);
				//printf("%p", (*L)->next);
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 4:
			if (*L)//�������
			{
				if (ListEmpty(*L))
					printf("���Ա�Ϊ��\n");
				else printf("���Ա�Ϊ��\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 5:
			if (*L)//�������
			{
				int len;
				len = ListLength(*L);
				printf("��Ϊ%d\n", len);
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 6:
			if (*L)//�������
			{
				Elemtype e;
				printf("����Ԫ�����\n");
				scanf(" %d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L))//��iֵ��Ч
				{
					GetElem(*L, i, e);//��ȡλ��Ϊi��Ԫ��
					printf("λ��%d��Ԫ��ֵΪ:", i); visit(e);//�����ȡ��Ԫ��ֵ
				}
				else printf("iֵ��Ч\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 7:
			if (*L)//�������
			{
				Elemtype e;
				printf("����һ�����֣�Ϊe��ֵ\n");
				scanf("%d", &e);
				getchar();
				//�����һ����e����compare��ϵ��Ԫ��λ�򣬲�����λ��Ϊ0
				int order = LocateElem(*L, e, compare);
				if (order == 0)
					printf("���в�������e��ͬ��Ԫ��\n");
				else printf("��һ����e����compare��ϵ��Ԫ��λ����%d\n", order);
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 8:
			if (*L)//�������
			{
				Elemtype cur_e, pre_e;
				printf("����һ�����֣�Ϊcur_e��ֵ\n");
				scanf("%d", &cur_e);
				getchar();
				if (PriorElem(*L, cur_e, pre_e) == 1)//���cur_e����ǰ��
				{
					printf("cur_e��ǰ��Ϊ:"); visit(pre_e);
				}
				else printf("cur_e��ǰ��������\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 9:
			if (*L)//�������
			{
				Elemtype cur_e, next_e;
				printf("����һ�����֣�Ϊcur_e��ֵ\n");
				scanf("%d", &cur_e);
				getchar();
				if (NextElem(*L, cur_e, next_e) == 1)//���cur_e���ں��
				{
					printf("cur_e�ĺ��Ϊ:"); visit(next_e);
				}
				else printf("cur_e�ĺ�̲�����\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 10:
			if (*L)//�������
			{
				printf("����Ҫ�����λ��\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L) + 1)//iֵ�Ϸ�
				{
					Elemtype e;//�����Ԫ��
					printf("����һ�����֣�Ϊe��ֵ\n");
					scanf("%d", &e);
					getchar();
					if (ListInsert(*L, i, e))
						printf("����ɹ�\n");
					else printf("����ʧ��\n");
				}
				else printf("λ��i���Ϸ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 11:
			if (*L)//�������
			{
				printf("����Ҫɾ��������Ԫ��λ��\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(*L))//��iֵ�Ϸ�
				{
					Elemtype e;//����ɾ���Ľ������
					if (ListDelete(*L, i, e))
					{
						printf("ɾ���ɹ�\n");
						printf("ɾ����Ԫ��ֵΪ:"); visit(e);
					}
					else printf("ɾ��ʧ��\n");
				}
				else printf("λ��i���Ϸ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 12:
			if (*L)//�������
			{
				if (!ListTrabverse(*L, visit)) printf("���Ա��ǿձ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 13:
			if (*L == NULL || (*L)->next == NULL)//�������ڻ��Ϊ�գ����������
			{
				int status;
				if (*L == L1)//ѡ��L1
					status = Loaddata(L, FILENAME_L1);
				else if (*L == L2)//ѡ��L2
					status = Loaddata(L, FILENAME_L2);
				if (status)
					printf("���ݼ��سɹ�\n");
				else printf("���ݼ���ʧ��\n");
			}
			else printf("���Ѵ��ڣ������ٻ���պ��������\n");
			getchar(); getchar();
			break;
		case 14:
			if (*L)//�������
			{
				int status;
				if (*L == L1)//ѡ��L1
					status = Savedata(*L, FILENAME_L1);
				else if (*L == L2)//ѡ��L2
					status = Savedata(*L, FILENAME_L2);
				if (status)
					printf("���ݱ���ɹ�\n");
				else printf("���ݱ���ʧ��\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch	
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

 /*--------------------page 23 on textbook ----------------------------------*/
status IntiaList(SqList * L) {
	*L = (Lnode *)malloc(sizeof(Lnode));//ͷָ������һ���洢���
	if (*L)//�������ռ�ɹ�
		(*L)->next = NULL;//ͷ���ָ�����ÿ�
	else exit(OVERFLOW);//����ʧ��
	return OK;
}

status DestroyList(SqList * L)
{
	Lnode * L1;
	Lnode * temp;//�洢��һ���ͷŽڵ��nextֵ
	L1 = *L;//L1������������
	for (L1 = *L; L1 != NULL; L1 = temp)
	{
		temp = L1->next;//����nextֵ
		free(L1);//�����ͷ����Ա���ڴ�ռ�
	}
	*L = NULL;//ͷָ���ÿ�
	return OK;
}

status ClearList(SqList *L)
{
	Lnode * L1;
	Lnode * temp;//�洢��һ���ͷŽڵ��nextֵ
	L1 = *L;//L1������������
	for (L1 = (*L)->next; L1 != NULL; L1 = temp)//�ͷ�ͷ���֮��Ľ��
	{
		temp = L1->next;//����nextֵ
		free(L1);//�����ͷ����Ա���ڴ�ռ�
	}
	(*L)->next = NULL;//ͷ���ָ�����ÿ�
	return OK;
}

status ListEmpty(SqList L)
{
	if (L->next == NULL)//��ͷ����ָ����Ϊ��
		return TRUE;
	else return FALSE;
}

int ListLength(SqList L)
{
	Lnode *p;
	int count;
	for (p = L->next, count = 0; p != NULL; p = p->next)
		count++;//pÿ����һ�Σ�����1
	return count;
}

status GetElem(SqList L, int i, Elemtype & e)
{
	Lnode *p;
	int count;
	for (p = L->next, count = 1; count != i; p = p->next, count++);//��λ��i������Ԫ��
	e = p->data;//��ֵ
	return OK;
}

status LocateElem(SqList L, Elemtype e, status(*compare)(Elemtype *x, Elemtype *y))
{
	Lnode *p;
	int count;
	for (p = L->next, count = 1; p != NULL; p = p->next, count++)//���׽ڵ㿪ʼ�Ƚ�
		if (compare(&(p->data), &e) == 0)
			return count;
	return FALSE;//������ϣ�δ�ҵ�
}

status PriorElem(SqList L, Elemtype cur, Elemtype & pre_e)
{
	Lnode *p;
	Lnode *pr;//p��ǰ��
	p = L->next;//pָ���׽ڵ�
	if (p == NULL || p->data == cur)//�������Ϊ�ջ�cur���׽ڵ㣬������ǰ��
		return FALSE;
	pr = p;//prָ���׽ڵ�
	p = p->next;//pָ��ڶ����
	while (p != NULL)
	{
		if (p->data == cur)//���cur�ڱ���
		{
			pre_e = pr->data;//��ֵ
			return TRUE;
		}
		pr = p;
		p = p->next;
	}
	return FALSE;//����δ�ҵ�cur��cur��ǰ��
}

status NextElem(SqList L, Elemtype cur, Elemtype & next_e)
{
	Lnode *p;//p
	p = L->next;//pָ���׽ڵ�
	if (p == NULL)//�������Ϊ��
		return FALSE;

	while (p != NULL)
	{
		if (p->data == cur)//���cur�ڱ���
			break;
		p = p->next;
	}
	if (!p || !(p->next))//cur���������л�curΪ���һ�����
		return FALSE;
	else {
		next_e = (p->next)->data;//��ֵ
		return TRUE;
	}
}

status ListInsert(SqList L, int i, Elemtype e)
{
	int count;//��¼��ǰλ��
	Lnode *p;//ʹ��p�����������λ��i
	Lnode *q;
	for (p = L, count = 0; count < i - 1; p = p->next, count++);//��λ��ִ����Ϻ�pָ��λ��i��ǰ��
	q = (Lnode *)malloc(sizeof(Lnode));//Ϊ����Ľ�������ռ�
	q->data = e;//��e��������ֵ��q��������
	q->next = p->next;//������
	p->next = q;
	return OK;
}

status ListDelete(SqList L, int i, Elemtype & e)
{
	Lnode *p, *q;
	int count;
	for (p = L, count = 0; count < i - 1; p = p->next, count++);//��λ��ִ����Ϻ�pָ��λ��i��ǰ��
	q = p->next;//qָ��ɾ�����
	e = q->data;//��ֵ
	p->next = q->next;//����ָ����
	free(q);//ɾ�����
	return OK;
}

status ListTrabverse(SqList L, status(*visit)(Elemtype e)) {

	if (L->next == NULL)
		return 0;
	Lnode * p;
	printf("\n-------------------- all elements ------------------------------\n");
	for (p = L->next; p != NULL; p = p->next)//ʹ��visit�����׽�㼰��֮��Ľ��
		visit(p->data);
	printf("\n------------------------- end ----------------------------------\n");
	return 1;
}
status Loaddata(SqList *L, char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	if (*L == NULL)//�������ڣ��򴴽���ͷ���
		*L = (Lnode *)malloc(sizeof(Lnode));
	(*L)->next = NULL;//ͷ���ָ�����ÿ�
	Lnode newEle;
	Lnode *p, *q;
	q = *L;//qָ��Ҫ����λ�õ�ǰ�����
	while (fread(&newEle, sizeof(Lnode), 1, fp))//ÿ�ζ�ȡһ������Ԫ��
	{
		p = (Lnode *)malloc(sizeof(Lnode));//��̬����һ����㣬��Ϊ�½����뵽������
		*p = newEle;//Ϊ�½ڵ㸳ֵ
					//������
		p->next = q->next;
		q->next = p;
		q = p;//q����һ����㣬������һ�εĲ���
	}
	fclose(fp);
	return TRUE;//д�����

}
status Savedata(SqList L, char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "w")) == NULL)//���ļ�ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	Lnode *p;
	p = L->next;//pָ���׽��
	while (p)
	{
		fwrite(p, sizeof(Lnode), 1, fp);//�Զ����ƶ�дһ��д��һ����������
		p = p->next;
	}
	fclose(fp);//�ر��ļ�
	return TRUE;
}

status visit(Elemtype e)
{
	printf("%d ", e);
	return TRUE;
}

status compare(Elemtype *x, Elemtype *y)
{
	return (*x) - (*y);//��ͬ����0
}

SqList * list_verify(SqList *L1, SqList *L2)
{
	char Listname[9];
	do {
		printf("\n    ѡ����Ҫ�����ı�[L1,L2]: ");
		scanf("%s", Listname);
	} while (strcmp(Listname, "L1") && strcmp(Listname, "L2"));//ֻ����L1��L2��ѡ��
	SqList *plist;
	if (strcmp(Listname, "L1") == 0)
		plist = L1;
	else plist = L2;//plistΪ�û���ѡ�ı�

	return plist;
}
