#include"myStack.h"
class QUEUE: public STACK {//�����̳��Ը����е�ջs1
	STACK  s2;//����s1ִ����Ӳ�����s2ִ�г��Ӳ���
public:
	QUEUE(int m);		//��ʼ�����У�ÿ��ջ���m��Ԫ��
	QUEUE(const QUEUE&s); 		//�ö���s������ʼ������
	operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	QUEUE& operator<<(int e); 		//��e�����,�����ض���
	QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	int operator[](int x);		//�����±�Ϊx��Ԫ��
	void print() const;			//��ӡ����
	~QUEUE();					//���ٶ���

	bool isEmpty();//�ӿշ���true
	bool isFull();//��������true
};
QUEUE::QUEUE(int m) :STACK(m), s2(m) {};
QUEUE::QUEUE(const QUEUE&s) :STACK(s.size()), s2(s.s2.size())
{
	*this = s;
};
QUEUE::operator int() const
{
	int i = this->STACK::operator int();
	return i + s2;//����Ԫ�ظ���=s1Ԫ�ظ���+s2Ԫ�ظ���
}
QUEUE& QUEUE::operator<<(int e)
{
	if (this->STACK::operator int() == this->STACK::size())//s1��
	{
		if (s2 == 0)//��s2�գ���s1�е�Ԫ�ص���s2��
		{
			while (this->STACK::operator int() != 0)
			{
				int m;
				this->STACK::operator>>(m);
				s2 << m;
			}//��ջs1�е�Ԫ�ص�s2��
			this->STACK::operator<<(e);
		}
		else
		{
			cout << "queue is full" << endl;
		}
	}
	else//s1����
		this->STACK::operator<<(e);
	return *this;
}
QUEUE& QUEUE::operator>>(int &e)
{
	if (isEmpty())//����Ϊ��
	{
		cout << "queue is empty" << endl;
	}
	else//���зǿ�
	{
		if (s2 == 0)//ջs2Ϊ��
		{
			while (this->STACK::operator int() != 0)
			{
				int m;
				this->STACK::operator>>(m);
				s2 << m;
			}//��ջs1�е�Ԫ�ص�s2��
			s2 >> e;
		}
		else  //s2�ǿ�
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
	if (x >= operator int())//�Ƿ��±�
	{
		cout << "invalid index" << endl;
		return WRONG;
	}
	if (s2)//s2�ǿ�
	{
		if (x < s2)//�±�Ϊx��Ԫ����s2��
		{
			return s2[s2 - x - 1];
		}
		else//�±�Ϊx��Ԫ����s1��
			return  this->STACK::operator[](x - s2);
	}
	else return this->STACK::operator[](x);
}
void QUEUE::print() const
{
	if (s2)//s2�ǿգ��ȴ�ӡs2
	{
		int i = s2.operator int() - 1;
		while (i >= 0)
		{
			cout << "  " << s2[i];
			i--;
		}
	}
	if (this->STACK::operator int() != 0)//�ٴ�ӡs1
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
	return operator int() == 0;//����Ԫ�ظ���Ϊ0
}
bool QUEUE::isFull()
{
	return this->STACK::operator int() == this->STACK::size() && s2 != 0;//s1����s2�ǿ�
}

bool isPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++) {
		if (n%i == 0) {
			return false;//��������
		}
	}
	return true;//������
}

int main(int argc, char* argv[])
{
	system("color f0");
	if (argc > 1)
	{
		QUEUE * p = NULL;
		char cmd;//��ǰִ�е�����
		int cur_index;//��ǰ�������ַ����±�
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
			QUEUE *pnew;

			//����ָ����в���
			switch (cmd)
			{
			case 'S':
				num = atoi(argv[cur_index]);//��ȡ����
				if (num > 0)
				{
					p = new QUEUE(num);//��ʼ��һ����ջ
				}
				else error = 1;//num���Ϸ�
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
				if (num > (*p))//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
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
				pnew = new QUEUE(*p);//������ջ
				delete p;//���پ�ջ
				p = pnew;
				break;
			case 'A':
				num = atoi(argv[cur_index]);
				pnew = new QUEUE(num);
				*pnew = *p;//��ֵ��ջ
				delete p;//���پ�ջ
				p = pnew;
				break;
			case 'G':
				num = atoi(argv[cur_index]);
				if (num >= (*p)) //Ԫ���±겻�Ϸ�
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
			QUEUE man(M), woman(F);//��ʿ���飬Ůʿ����
			int i;
			/*��ʼ������*/
			for (i = 1; i <= M; i++)
				man << i;
			for (int i = 1; i <= F; i++)
				woman << i;
			int res = 1;
			/*ģ������*/
			while (1)
			{
				int m, w;
				man >> m; woman >> w;
				if (m == manLocation && w == womanLocation) break;
				man << m; woman << w;
				res++;
				//if (res > 10000) { cout << "no answer" << endl; break; }
			}
			cout << "�ڵ�" << res << "֧��������ʿ�ɺ͸�Ůʿһ������" << endl;
			system("pause");
		}
	}
	//system("pause");
	return 0;
}