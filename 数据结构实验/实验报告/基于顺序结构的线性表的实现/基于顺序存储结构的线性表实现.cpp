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
#define FILENAME "data"//���ݱ�����ļ���

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
status Loaddata(SqList &L);//��������
status Savedata(SqList L);
status visit(ElemType e);
/*------------------------------------------------------*/
int main(void){
	SqList L;
	L.elem = NULL;
	int i;//����λ��
	int op = 1;
	int flat = 1;//������
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
		switch (op) {
		case 1:
			if (!L.elem&&flat)//�����Ա����ڣ��򴴽�
			{
				if (InitiaList(L) == OK) {
					printf("���Ա����ɹ���\n");
					flat = 0;//���Ѵ���
				}
				else printf("���Ա���ʧ�ܣ�\n");
			}
			else printf("���Ա��Ѵ���\n");
			getchar(); getchar();
			break;
		case 2:
			if (L.elem)//�������
			{
				DestroyList(L);
				printf("�����ٳɹ�\n");
				flat = 1;
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 3:
			if (L.elem)//�������
			{
				ClearList(L);
				printf("���ÿճɹ�\n");
			}
			else printf("������\n");
			getchar(); getchar();

			break;
		case 4:
			if (L.elem)//�������
			{
				if (ListEmpty(L) == 1)
					printf("��Ϊ��\n");
				else printf("��Ϊ��\n");
			}
			else printf("������\n");
			getchar();
			break;
		case 5:
			if (L.elem)//�������
			{
				printf("��Ϊ%d\n", ListLength(L));
			}
			else printf("������\n");
			getchar();
			break;
		case 6:
			ElemType e;
			if (L.elem)//�����
			{
				printf("����Ԫ�����\n");
				scanf(" %d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L))//��iֵ��Ч
				{
					GetElem(L, i, e);//��ȡλ��Ϊi��Ԫ��
					printf("λ��%d��Ԫ��ֵΪ%d", i, e);//�����ȡ��Ԫ��ֵ
				}
				else printf("iֵ��Ч\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 7:
			if (L.elem)
			{
				ElemType e;
				printf("����һ�����֣�Ϊe��ֵ\n");
				scanf("%d", &e);
				getchar();

				//�����һ����e����compare��ϵ��Ԫ��λ�򣬲�����λ��Ϊ0
				int order = LocatElem(L, e, compare);
				if (order == 0)
					printf("���в�������e��ͬ��Ԫ��\n");
				else printf("��һ����e��ͬ��Ԫ��λ����%d\n", order);
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 8:
			if (L.elem)//�������
			{
				ElemType cur_e, pre_e;
				printf("����һ�����֣�Ϊcur_e��ֵ\n");
				scanf("%d", &cur_e);
				getchar();
				if (PriorElem(L, cur_e, pre_e) == 1)//���cur_e����ǰ��
					printf("cur_e��ǰ��Ϊ%d\n", pre_e);
				else printf("cur_e��ǰ��������\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 9:
			if (L.elem)//�������
			{
				ElemType cur_e, next_e;
				printf("����һ�����֣�Ϊcur_e��ֵ\n");
				scanf("%d", &cur_e);
				getchar();
				if (NextElem(L, cur_e, next_e) == 1)//���cur_e���ں��
					printf("cur_e�ĺ��Ϊ%d\n", next_e);
				else printf("cur_e�ĺ�̲�����\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 10:
			if (L.elem)//�������
			{
				printf("����Ҫ�����λ��\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L) + 1)//iֵ�Ϸ�
				{
					ElemType e;//�����Ԫ��
					printf("����һ�����֣�Ϊe��ֵ\n");
					scanf("%d", &e);
					getchar();
					if (ListInsert(L, i, e))
						printf("����ɹ�\n");
					else printf("����ʧ��\n");
				}
				else printf("λ��i���Ϸ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 11:
			if (L.elem)//�����
			{
				printf("����Ҫɾ��������Ԫ��λ��\n");
				scanf("%d", &i);
				getchar();
				if (i >= 1 && i <= ListLength(L))
				{
					ElemType e;//ɾ����Ԫ�ش����e��
					getchar();
					if (ListDelete(L, i, e))
					{
						printf("ɾ���ɹ�\n");
						printf("ɾ����Ԫ��ֵΪ%d", e);
					}
					else printf("ɾ��ʧ��\n");
				}

				else printf("λ��i���Ϸ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 12:
			if (L.elem)//�������
			{
				if (!ListTrabverse(L, visit)) printf("���Ա��ǿձ�\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 13:
			if (L.elem)//�������
			{
				if (Loaddata(L))
					printf("���ݼ��سɹ�\n");
				else printf("���ݼ���ʧ��\n");
			}
			else printf("������\n");
			getchar(); getchar();
			break;
		case 14:
			if (L.elem)//�������
			{
				if (Savedata(L))
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
status InitiaList(SqList & L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);//����ڴ治�㴴��ʧ�ܣ����쳣�˳�
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;//�����ɹ�
}
status DestroyList(SqList & L) {
	free(L.elem);//�ͷſռ�
	L.elem = NULL;//��ַָ���
	L.length = L.listsize = 0;//�������С��0

	return TRUE;//���ٳɹ�
}
status ClearList(SqList & L) {
	L.length = 0;//�ñ�Ϊ0
	return TRUE;
}
status ListEmpty(SqList L) {
	if (L.length == 0)
		return TRUE;//���LΪ�ձ�(����==0)������TRUE;
	else return FALSE;//���򷵻�FALSE;
}

status ListLength(SqList L) {
	return L.length;//����Ԫ�ظ���
}

status GetElem(SqList L, int i, ElemType & e) {
		e = L.elem[i - 1];//ʹ��ȡַ��ʽ��λ��i��Ԫ�ز���ֵ��e
		return OK;
}

status LocatElem(SqList L, ElemType e, status(*compare)(ElemType x, ElemType y))
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (compare(L.elem[i], e) == 0)//compare�����Ƚ�������������ͬ����0
			return i + 1;//���ص�һ����e�����ϵcompare������Ԫ�ص�λ��
	}
	return FALSE;//�����ڷ���0
}

status PriorElem(SqList L, ElemType cur, ElemType & pre_e) {
	int order = LocatElem(L, cur, compare);//����curԪ�ػ�ȡ����ţ�cur���ڱ���orderΪ0��
	if (order > 1)//���cur��L���Ҳ�Ϊ��һ��Ԫ��
	{
		pre_e = L.elem[order - 2];//cur��ǰ��ֵ����&pre_e
		return TRUE;
	}
	return FALSE;
}
status NextElem(SqList L, ElemType cur, ElemType & next_e) {
	int order = LocatElem(L, cur, compare);//����curԪ�ػ�ȡ�����
	if (order >= 1 && order<L.length)//���cur��L���Ҳ�Ϊ���һ��Ԫ��
	{
		next_e = L.elem[order];//cur�ĺ��ֵ����&next_e
		return TRUE;
	}
	return FALSE;
}


status ListInsert(SqList & L, int i, ElemType e) {
	if (L.length + 1 >= L.listsize)//�ռ�����������ռ�
	{
		ElemType * newbase;
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (newbase == NULL)
			return FALSE;//����ʧ��
		L.elem = newbase;//�»�ַ
		L.listsize += LISTINCREMENT;//��������
	}
	//i֮���Ԫ�����κ���
	ElemType *in_i = &(L.elem[i - 1]);//in_iָ��Ҫ�����λ��
	ElemType *cur;
	for (cur = &(L.elem[L.length - 1]); cur >= in_i; cur--)
		*(cur + 1) = *cur;
	*in_i = e;//i������e
	L.length++;//����1
	return TRUE;
}

status ListDelete(SqList & L, int i, ElemType & e)
{
	e = L.elem[i - 1];//��ֵe
	ElemType *tail = &L.elem[L.length - 1];//tailָ���β��λ��
	ElemType *cur;
	for (cur = &(L.elem[i - 1]); cur < tail; cur++)
		*cur = *(cur + 1);//i֮���Ԫ������ǰ��
	L.length--;//����1
	return TRUE;
}


status ListTrabverse(SqList L, status(*visit)(ElemType e)) {
		int i;
		printf("\n-------------------- all elements ------------------------------\n");
		for (i = 0; i < L.length; i++)
		{
			if (!visit(L.elem[i])) return ERROR;//���visitʧ�ܣ����˳�
		}
		printf("\n------------------------- end ----------------------------------\n");

   return L.length;//������ϣ����ر�����Ԫ�ظ���
}
status compare(ElemType x, ElemType y)
{/*ͨ���ڴ�Ƚ��ж�x��yԪ��,��ȷ���0��x<y����0-��x>y����0+*/
	return memcmp(&x, &y, sizeof(ElemType));
}
status Loaddata(SqList &L)
{
	FILE *fp;
	L.length = 0;
	if ((fp = fopen(FILENAME, "r")) == NULL)//�ļ���ʧ��
	{
		printf("File open error\n ");
		return FALSE;
	}
	while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))//ÿ�ζ�ȡһ������Ԫ�أ�˳��д���˳�����
	{
		if (L.length + 1 >= L.listsize)//�ռ�����������ռ�
		{
			ElemType * newbase;
			newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
			if (newbase == NULL)
				return FALSE;//����ʧ��
			L.elem = newbase;//�»�ַ
			L.listsize += LISTINCREMENT;//��������
		}
		L.length++;//׼��д����һ��Ԫ��
	}
	fclose(fp);
	return TRUE;//д�����

}
status Savedata(SqList L)
{
	FILE *fp;
	if ((fp = fopen(FILENAME, "w")) == NULL)//���ļ�ʧ��
	{
		printf("File open erroe\n ");
		return FALSE;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);//�ӵ�ַL.elem��ʼ������sizeof(ElemType)*L.length���ֽڵ�����һ����д�뵽�ļ���
	fclose(fp);//�ر��ļ�
	return TRUE;
}
status visit(ElemType e)
{
	printf("%d ", e);
	return TRUE;
}
