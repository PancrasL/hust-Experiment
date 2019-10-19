#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#define WRONG -1
struct STACK {
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

void initSTACK(STACK *const p, int m)
{
	p->max = m;
	p->pos = 0;
	p->elems = (int *)malloc(m * sizeof(int));//动态分配内存
	if (!p->elems)//内存分配失败
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
	if (!p->elems)//内存分配失败
	{
		printf("memory allocation failed/n");
		exit(0);
	}
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//拷贝s中的数据到p中
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
	else//下标不合法
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
	if (p == &s) return p;//自身赋值
	p->max = s.max;
	p->pos = s.pos;
	p->elems = (int *)realloc(p->elems, s.max * sizeof(int));//重新分配内存
	if (!p->elems)//内存分配失败
	{
		printf("memory allocation failed/n");
		exit(0);
	}
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//拷贝数据
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

	char cmd = 1;//当前执行的命令
	int cur_index;//当前处理的字符串下标
	int end_index;//[cur_index,end_index)之间的数据均为命令的参数
	int error = 0;//错误标记
	cur_index = end_index = 1;
	while (end_index < argc)
	{
		cur_index = end_index++;
		cmd = argv[cur_index++][1];//当前执行的命令
		while (end_index < argc && !(argv[end_index][1] >= 'A' && argv[end_index][1] <= 'Z'))
		{
			end_index++;
		}//end_index定位到下一条命令
		int num = -1;
		STACK *pnew;

		//根据指令进行操作
		switch (cmd)
		{
		case 'S':
			num = atoi(argv[cur_index]);//获取参数
			if (num > 0)
			{
				p = new STACK;
				initSTACK(p, num);//初始化一个新栈
			}
			else error = 1;//num不合法
			break;
		case 'I':
			if (end_index - cur_index > p->max - p->pos)//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
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
			if (num > p->pos)//出栈元素个数>当前栈中元素个数
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
			initSTACK(pnew, *p);//拷贝新栈
			destroySTACK(p); delete p;//销毁旧栈
			p = pnew;
			break;
		case 'A':
			pnew = new STACK;
			num = atoi(argv[cur_index]);
			initSTACK(pnew, num);
			assign(pnew, *p);//赋值新栈
			destroySTACK(p); delete p;//销毁旧栈
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

		//输出执行完指令后的数据
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
