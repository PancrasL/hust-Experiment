#include"myStack.h"
class QUEUE: public STACK {//包含继承自父类中的栈s1
	STACK  s2;//其中s1执行入队操作，s2执行出队操作
public:
	QUEUE(int m);		//初始化队列：每个栈最多m个元素
	QUEUE(const QUEUE&s); 		//用队列s拷贝初始化队列
	operator int() const;			//返回队列的实际元素个数
	QUEUE& operator<<(int e); 		//将e入队列,并返回队列
	QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	int operator[](int x);		//返回下标为x的元素
	void print() const;			//打印队列
	~QUEUE();					//销毁队列

	bool isEmpty();//队空返回true
	bool isFull();//队满返回true
};
QUEUE::QUEUE(int m) :STACK(m), s2(m) {};
QUEUE::QUEUE(const QUEUE&s) :STACK(s.size()), s2(s.s2.size())
{
	*this = s;
};
QUEUE::operator int() const
{
	int i = this->STACK::operator int();
	return i + s2;//队列元素个数=s1元素个数+s2元素个数
}
QUEUE& QUEUE::operator<<(int e)
{
	if (this->STACK::operator int() == this->STACK::size())//s1满
	{
		if (s2 == 0)//若s2空，将s1中的元素倒入s2中
		{
			while (this->STACK::operator int() != 0)
			{
				int m;
				this->STACK::operator>>(m);
				s2 << m;
			}//出栈s1中的元素到s2中
			this->STACK::operator<<(e);
		}
		else
		{
			cout << "queue is full" << endl;
		}
	}
	else//s1非满
		this->STACK::operator<<(e);
	return *this;
}
QUEUE& QUEUE::operator>>(int &e)
{
	if (isEmpty())//队列为空
	{
		cout << "queue is empty" << endl;
	}
	else//队列非空
	{
		if (s2 == 0)//栈s2为空
		{
			while (this->STACK::operator int() != 0)
			{
				int m;
				this->STACK::operator>>(m);
				s2 << m;
			}//出栈s1中的元素到s2中
			s2 >> e;
		}
		else  //s2非空
		{
			s2 >> e;
		}
	}
	return *this;
}
QUEUE& QUEUE::operator=(const QUEUE&s)
{
	if (this == &s) return *this;
	(STACK&)(*this) = s;
	this->s2 = s.s2;
	return *this;
}
int QUEUE::operator[](int x)
{
	if (x >= operator int())//非法下标
	{
		cout << "invalid index" << endl;
		return WRONG;
	}
	if (s2)//s2非空
	{
		if (x < s2)//下标为x的元素在s2中
		{
			return s2[s2 - x - 1];
		}
		else//下标为x的元素在s1中
			return  this->STACK::operator[](x - s2);
	}
	else return this->STACK::operator[](x);
}
void QUEUE::print() const
{
	if (s2)//s2非空，先打印s2
	{
		int i = s2.operator int() - 1;
		while (i >= 0)
		{
			cout << "  " << s2[i];
			i--;
		}
	}
	if (this->STACK::operator int() != 0)//再打印s1
	{
		int i = 0;
		while (i < this->STACK::operator int())
		{
			cout << "  " << this->STACK::operator[](i);
			i++;
		}
	}
}
QUEUE::~QUEUE() {};
bool QUEUE::isEmpty()
{
	return operator int() == 0;//队列元素个数为0
}
bool QUEUE::isFull()
{
	return this->STACK::operator int() == this->STACK::size() && s2 != 0;//s1满且s2非空
}

bool isPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++) {
		if (n%i == 0) {
			return false;//不是素数
		}
	}
	return true;//是素数
}

int main(int argc, char* argv[])
{
	system("color f0");
	if (argc > 1)
	{
		QUEUE * p = NULL;
		char cmd;//当前执行的命令
		int cur_index;//当前参数的字符串下标
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
			QUEUE *pnew;

			//根据指令进行操作
			switch (cmd)
			{
			case 'S':
				num = atoi(argv[cur_index]);//获取参数
				if (num > 0)
				{
					p = new QUEUE(num);//初始化一个新栈
				}
				else error = 1;//num不合法
				break;
			case 'I':
				while (cur_index < end_index)
				{
					if (p->isFull()) { error = 1; break; }
					num = atoi(argv[cur_index++]);
					*p << num;
				}
				break;
			case 'O':
				num = atoi(argv[cur_index]);
				if (num > (*p))//出栈元素个数>当前栈中元素个数
					error = 1;
				else
				{
					while (num--)
					{
						int e;
						*p >> e;
					}
				}
				break;
			case 'C':
				pnew = new QUEUE(*p);//拷贝新栈
				delete p;//销毁旧栈
				p = pnew;
				break;
			case 'A':
				num = atoi(argv[cur_index]);
				pnew = new QUEUE(num);
				*pnew = *p;//赋值新栈
				delete p;//销毁旧栈
				p = pnew;
				break;
			case 'G':
				num = atoi(argv[cur_index]);
				if (num >= (*p)) //元素下标不合法
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
				cout << "  N  " << *p;
				break;
			case 'G':
				cout << "  G  " << (*p)[num];
				break;
			default:
				break;
			}
		}
	}
	else
	{
		while (true)
		{
			cout << "input the number of man and women:" << endl;
			int M, F;
			cin >> M >> F;
			if (M == F)
			{
				cout << "input error! can not input equal number!" << endl;
				continue;
			}
			if (!isPrime(M) || !isPrime(F))
			{
				cout << "input error! must input prime num!" << endl;
				continue;
			}
			cout << "input location of the man and the woman:" << endl;
			int manLocation, womanLocation;
			cin >> manLocation >> womanLocation;
			QUEUE man(M), woman(F);//男士队伍，女士队伍
			int i;
			/*初始化队伍*/
			for (i = 1; i <= M; i++)
				man << i;
			for (int i = 1; i <= F; i++)
				woman << i;
			int res = 1;
			/*模拟跳舞*/
			while (1)
			{
				int m, w;
				man >> m; woman >> w;
				if (m == manLocation && w == womanLocation) break;
				man << m; woman << w;
				res++;
				//if (res > 10000) { cout << "no answer" << endl; break; }
			}
			cout << "在第" << res << "支舞曲该男士可和该女士一起跳舞" << endl;
			system("pause");
		}
	}
	//system("pause");
	return 0;
}