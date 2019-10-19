#include<iostream>
#define WRONG -1;
using namespace std;
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ������m��Ԫ��
	STACK(const STACK&s); 			//��ջs������ʼ��ջ
	virtual int  size() const;			//����ջ�����Ԫ�ظ���max
	virtual operator int() const;			//����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[] (int x) const;	//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;			//��ӡջ
	virtual ~STACK();					//����ջ
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
	if (pos < max)//ջδ��
	{
		elems[pos++] = e;
	}
	else cout << "Stack is full" << endl;
	return *this;
}
STACK& STACK::operator>>(int &e)
{
	if (pos>0)//ջ�ǿ�
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
		elems[i] = s.elems[i];//����Ԫ��
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
