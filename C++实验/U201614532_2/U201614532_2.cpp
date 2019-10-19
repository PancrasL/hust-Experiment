#include<iostream>
using namespace std;
#define WRONG -1;
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size() const;		//返回栈的最大元素个数max
	int  howMany() const;	//返回栈的实际元素个数pos
	int  getelem(int x) const;	//取下标x处的栈元素
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
	void print() const;		//打印栈
	~STACK();				//销毁栈
};
STACK::STACK(int m) : elems(new int[m]), max(m), pos(0) {};
STACK::STACK(const STACK&s) : elems(new int[s.max]), max(s.max), pos(s.pos) {
	for (int i = 0; i < s.pos; i++)
		elems[i] = s.elems[i];
};
int STACK::size() const
{
	return max;
}
int STACK::howMany() const
{
	return pos;
}
int STACK::getelem (int x) const
{
	if (x<pos)
		return elems[x];
	else
	{	
		cout << "Invalid index" << endl;
		return WRONG;
	}
}
STACK& STACK::push(int e)
{
	if (pos < max)//栈未满
	{
		elems[pos++] = e;
	}
	else cout << "Stack is full" << endl;
	return *this;
}
STACK& STACK::pop(int &e)
{
	if (pos>0)//栈非空
		e = elems[--pos];
	else cout << "Stack is empty" << endl;
	return *this;
}
STACK& STACK::assign(const STACK&s)
{
	if (this == &s) return *this;//自身赋值
	*(int *)&max = s.max;
	pos = s.pos;
	delete elems;
	*(int **)&elems = new int[s.max];
	for (int i = 0; i < s.pos; i++)
		elems[i] = s.elems[i];//拷贝元素
	return *this;
}
void STACK::print() const
{
	using namespace std;
	int i = 0;
	while (i<pos)
	{
		cout << "  " << elems[i++];
	}
}
STACK::~STACK()
{
	delete[] elems;
}
int main(int argc, char* argv[])
{
	STACK * p = NULL;

	char cmd;//当前执行的命令
	int cur_index;//当前参数的字符串下标
	int end_index;//[cur_index,end_index)之间的数据均为命令的参数
	int error = 0;//错误标记
	cur_index = end_index = 1;
	while (end_index < argc)
	{
		cur_index = end_index++;
		cmd = argv[cur_index++][1];//当前执行的命令
		while (end_index<argc&&!(argv[end_index][1] >= 'A' && argv[end_index][1] <= 'Z'))
		{
			end_index++;
		}//end_index定位到下一条命令
		int num=-1;
		STACK *pnew;

		//根据指令进行操作
		switch (cmd)
		{
		case 'S':
			num = atoi(argv[cur_index]);//获取参数
			if (num > 0)
			{
				p = new STACK(num);//初始化一个新栈
			}
			else error = 1;//num不合法
			break;
		case 'I':
			if (end_index - cur_index > p->size() - p->howMany())//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
			{
				while (cur_index < end_index)
				{
					num = atoi(argv[cur_index++]);
					p->push(num);
				}
			}
			break;
		case 'O':
			num = atoi(argv[cur_index]);
			if (num > p->howMany())//出栈元素个数>当前栈中元素个数
				error = 1;
			else
			{
				while (num--)
				{
					int e;
					p->pop(e);
				}
			}
			break;
		case 'C':
			pnew = new STACK(*p);//拷贝新栈
			delete p;//销毁旧栈
			p = pnew;
			break;
		case 'A':
			num = atoi(argv[cur_index]);
			pnew = new STACK(num);
			pnew->assign(*p);//赋值新栈
			delete p;//销毁旧栈
			p = pnew;
			break;
		case 'G':
			num = atoi(argv[cur_index]);
			if (num >= p->howMany()) //元素下标不合法
				error = 1;
			break;
		default:
			break;
		}
		if (error == 1)//命令出错
		{
			cout << "  " << cmd << "  E";
			break;
		}

		//输出执行完指令后的数据
		switch (cmd)
		{
		case 'S':
			cout << "S  " << num;
			break;
		case 'I':
			cout << "  I";
			p->print();
			break;
		case 'O':
			cout << "  O";
			p->print();
			break;
		case 'C':
			cout << "  C";
			p->print();
			break;
		case 'A':
			cout << "  A";
			p->print();
			break;
		case 'N':
			cout << "  N  " << p->howMany();
			break;
		case 'G':
			cout << "  G  " << p->getelem(num);
			break;
		default:
			break;
		}
	}
	//system("pause");
	return 0;
}