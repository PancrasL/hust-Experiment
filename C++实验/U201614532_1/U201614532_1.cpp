#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#define WRONG -1
struct STACK {
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size(const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany(const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

void initSTACK(STACK *const p, int m)
{
	p->max = m;
	p->pos = 0;
	p->elems = (int *)malloc(m * sizeof(int));//��̬�����ڴ�
	if (!p->elems)//�ڴ����ʧ��
	{
		printf("memory allocation failed/n");
		exit(0);
	}
}
void initSTACK(STACK *const p, const STACK&s)
{
	p->max = s.max;
	p->pos = s.pos;
	p->elems = (int *)malloc(s.max * sizeof(int));
	if (!p->elems)//�ڴ����ʧ��
	{
		printf("memory allocation failed/n");
		exit(0);
	}
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//����s�е����ݵ�p��
}
int  size(const STACK *const p)
{
	return p->max;
}
int  howMany(const STACK *const p)
{
	return p->pos;
}
int  getelem(const STACK *const p, int x)
{
	if(x<p->pos)
		return p->elems[x];
	else//�±겻�Ϸ�
	{
		printf("Invalid index/n");
		return WRONG;
	}
}
STACK *const push(STACK *const p, int e)
{
	if (p->pos < p->max)
	{
		p->elems[p->pos] = e;
		p->pos++;
	}
	else
		printf("Stack is full/n");
	return p;
}
STACK *const pop(STACK *const p, int &e)
{
	if (p->pos > 0)
	{
		p->pos--;
		e = p->elems[p->pos];
	}
	else printf("Stack is empty/n");
	return p;
}
STACK *const assign(STACK*const p, const STACK&s)
{
	if (p == &s) return p;//����ֵ
	p->max = s.max;
	p->pos = s.pos;
	p->elems = (int *)realloc(p->elems, s.max * sizeof(int));//���·����ڴ�
	if (!p->elems)//�ڴ����ʧ��
	{
		printf("memory allocation failed/n");
		exit(0);
	}
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//��������
	return p;
}
void print(const STACK*const p)
{
	int i = 0;
	while (i<p->pos)
	{
		printf("  %d", p->elems[i]);
		i++;
	}
}
void destroySTACK(STACK*const p)
{
	free(p->elems);
	p->elems = NULL;
	p->pos = 0;
	p->max = 0;
}
int main(int argc, char* argv[])
{
	STACK * p = NULL;

	char cmd = 1;//��ǰִ�е�����
	int cur_index;//��ǰ������ַ����±�
	int end_index;//[cur_index,end_index)֮������ݾ�Ϊ����Ĳ���
	int error = 0;//������
	cur_index = end_index = 1;
	while (end_index < argc)
	{
		cur_index = end_index++;
		cmd = argv[cur_index++][1];//��ǰִ�е�����
		while (end_index < argc && !(argv[end_index][1] >= 'A' && argv[end_index][1] <= 'Z'))
		{
			end_index++;
		}//end_index��λ����һ������
		int num = -1;
		STACK *pnew;

		//����ָ����в���
		switch (cmd)
		{
		case 'S':
			num = atoi(argv[cur_index]);//��ȡ����
			if (num > 0)
			{
				p = new STACK;
				initSTACK(p, num);//��ʼ��һ����ջ
			}
			else error = 1;//num���Ϸ�
			break;
		case 'I':
			if (end_index - cur_index > p->max - p->pos)//��ջԪ�ظ���>=���Ԫ�ظ���-��ǰԪ�ظ���
				error = 1;
			else//����������ջ
			{
				while (cur_index < end_index)
				{
					num = atoi(argv[cur_index++]);
					push(p, num);
				}
			}
			break;
		case 'O':
			num = atoi(argv[cur_index]);
			if (num > p->pos)//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
				error = 1;
			else
			{
				while (num--)
				{
					int e;
					pop(p, e);
				}
			}
			break;
		case 'C':
			pnew = new STACK;
			initSTACK(pnew, *p);//������ջ
			destroySTACK(p); delete p;//���پ�ջ
			p = pnew;
			break;
		case 'A':
			pnew = new STACK;
			num = atoi(argv[cur_index]);
			initSTACK(pnew, num);
			assign(pnew, *p);//��ֵ��ջ
			destroySTACK(p); delete p;//���پ�ջ
			p = pnew;
			break;
		case 'G':
			num = atoi(argv[cur_index]);
			if (num >= p->pos) error = 1;
			break;
		default:
			break;
		}
		if (error == 1)
		{
			printf("  %c  E", cmd);
			break;
		}

		//���ִ����ָ��������
		switch (cmd)
		{
		case 'S':
			printf("S  %d", num);
			break;
		case 'I':
			printf("  I");
			print(p);
			break;
		case 'O':
			printf("  O");
			print(p);
			break;
		case 'C':
			printf("  C");
			print(p);
			break;
		case 'A':
			printf("  A");
			print(p);
			break;
		case 'N':
			printf("  N  %d", p->pos);
			break;
		case 'G':
			printf("  G  %d", p->elems[num]);
			break;
		default:
			break;
		}
	}
	delete p;
	//system("pause");
	return 0;
}
