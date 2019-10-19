#include<iostream>
using namespace std;
#define WRONG -1;
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); //��ջs������ʼ��ջ
	int  size() const;		//����ջ�����Ԫ�ظ���max
	int  howMany() const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem(int x) const;	//ȡ�±�x����ջԪ��
	STACK& push(int e); 	//��e��ջ,������ջ
	STACK& pop(int &e); 	//��ջ��e,������ջ
	STACK& assign(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	void print() const;		//��ӡջ
	~STACK();				//����ջ
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
	if (pos < max)//ջδ��
	{
		elems[pos++] = e;
	}
	else cout << "Stack is full" << endl;
	return *this;
}
STACK& STACK::pop(int &e)
{
	if (pos>0)//ջ�ǿ�
		e = elems[--pos];
	else cout << "Stack is empty" << endl;
	return *this;
}
STACK& STACK::assign(const STACK&s)
{
	if (this == &s) return *this;//����ֵ
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
int main(int argc, char* argv[])
{
	STACK * p = NULL;

	char cmd;//��ǰִ�е�����
	int cur_index;//��ǰ�������ַ����±�
	int end_index;//[cur_index,end_index)֮������ݾ�Ϊ����Ĳ���
	int error = 0;//������
	cur_index = end_index = 1;
	while (end_index < argc)
	{
		cur_index = end_index++;
		cmd = argv[cur_index++][1];//��ǰִ�е�����
		while (end_index<argc&&!(argv[end_index][1] >= 'A' && argv[end_index][1] <= 'Z'))
		{
			end_index++;
		}//end_index��λ����һ������
		int num=-1;
		STACK *pnew;

		//����ָ����в���
		switch (cmd)
		{
		case 'S':
			num = atoi(argv[cur_index]);//��ȡ����
			if (num > 0)
			{
				p = new STACK(num);//��ʼ��һ����ջ
			}
			else error = 1;//num���Ϸ�
			break;
		case 'I':
			if (end_index - cur_index > p->size() - p->howMany())//��ջԪ�ظ���>=���Ԫ�ظ���-��ǰԪ�ظ���
				error = 1;
			else//����������ջ
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
			if (num > p->howMany())//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
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
			pnew = new STACK(*p);//������ջ
			delete p;//���پ�ջ
			p = pnew;
			break;
		case 'A':
			num = atoi(argv[cur_index]);
			pnew = new STACK(num);
			pnew->assign(*p);//��ֵ��ջ
			delete p;//���پ�ջ
			p = pnew;
			break;
		case 'G':
			num = atoi(argv[cur_index]);
			if (num >= p->howMany()) //Ԫ���±겻�Ϸ�
				error = 1;
			break;
		default:
			break;
		}
		if (error == 1)//�������
		{
			cout << "  " << cmd << "  E";
			break;
		}

		//���ִ����ָ��������
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