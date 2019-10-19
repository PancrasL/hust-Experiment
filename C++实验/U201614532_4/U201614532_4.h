#include<iostream>
#define WRONG -1;
using namespace std;
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多存m个元素
	STACK(const STACK&s); 			//用栈s拷贝初始化栈
	virtual int  size() const;			//返回栈的最大元素个数max
	virtual operator int() const;			//返回栈的实际元素个数pos
	virtual int operator[] (int x) const;	//取下标x处的栈元素，第1个元素x=0
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;			//打印栈
	virtual ~STACK();					//销毁栈
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
STACK::operator int() const
{
	return pos;
}
int STACK::operator[] (int x) const
{
	if (x<pos)
		return elems[x];
	else
	{
		cout << "Invalid index" << endl;
		return WRONG;
	}
}
STACK& STACK::operator<<(int e)
{
	if (pos < max)//栈未满
	{
		elems[pos++] = e;
	}
	else cout << "Stack is full" << endl;
	return *this;
}
STACK& STACK::operator>>(int &e)
{
	if (pos>0)//栈非空
		e = elems[--pos];
	else cout << "Stack is empty" << endl;
	return *this;
}
STACK& STACK::operator=(const STACK&s)
{
	if (this == &s) return *this;
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
