#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define BNAME "LVPENGZE"
#define BPASS "test"
#define N 10
#pragma inline
extern  void  QueryCommodity(struct commodity *,struct commodity *,short);
extern  void  ModifyCommodity(struct commodity *,struct commodity *,short);
extern  void  AVERAGR_PROFIT(struct commodity *,struct commodity *,short);
extern  void  PROFIT_RANKING(struct commodity *,struct commodity *,char);
extern  void  PRINT_IFO(struct commodity *,struct commodity *,short);
extern  void  ClearS(void);

void menu1(void);
void menu2(void);
void C_query_commodity(struct commodity*,struct commodity *,short);
struct commodity 
{
	char cname[10];//商品名
	short purchase_price;//购价
	short selling_price;//售价
	short total;//进货总数
	short sell;//售出数
	short prt;//利润率
};
struct shop
{
	char sname[6];//商店名
	struct commodity good[N];//商品信息
};
struct shop S[2];
int i, j;
struct commodity *pc,*temp1,*temp2;

int flat;
char AUTH;
char in_name[11];
char in_pwd[7];
char in_commodity[11];
char c;
char op;
int main(void)
{
	strcpy(S[0].sname, "SHOP1");
	strcpy(S[1].sname, "SHOP2");

	
	for (i = 0; i <= 1; i++)
	{
		pc = &(S[i].good[0]);
		strcpy(pc->cname, "PEN");
		pc->purchase_price = 10;
		pc->selling_price = 56;
		pc->total = 70;
		pc->sell = 50;
	}
	for (i = 0; i <= 1; i++)
	{
		pc = &(S[i].good[1]);
		strcpy(pc->cname, "BOOK");
		pc->purchase_price = 12;
		pc->selling_price = 30;
		pc->total = 25;
		pc->sell = 10;
	}
	for (i = 0; i <= 1; i++)
	{
		pc = &(S[i].good[2]);
		strcpy(pc->cname, "BAG");
		pc->purchase_price = 15;
		pc->selling_price = 30;
		pc->total = 30;
		pc->sell = 0;
	}
	for (i = 0; i <= 1; i++)
	{
		pc = &(S[i].good[3]);
		strcpy(pc->cname, "CUP");
		pc->purchase_price = 10;
		pc->selling_price = 23;
		pc->total = 40;
		pc->sell = 12;
	}
	for (i = 0; i <= 1; i++)
	{
		for (j = 4; j < N; j++)
		{
			pc = &(S[i].good[j]);
			strcpy(pc->cname, "TempValue");
			pc->purchase_price = 10;
			pc->selling_price = 10;
			pc->total = 10;
			pc->sell = 10;
		}
	}
Start:
	printf("Input your account:\n");
	gets(in_name);
	printf("Input your password:\n");
	gets(in_pwd);
	if (in_name[0] == 'q')//输入‘q'
	{
		return 0;
	}

	if (strlen(in_name) == 0)//输入回车
	{
		AUTH = 0;
	}
	else
	{
		while (!(strcmp(BNAME, in_name) == 0 && strcmp(BPASS, in_pwd) == 0))
		{
			printf("WRONG ACCOUNT!\n");
			goto Start;
		}
		printf("Login success\n");
		AUTH = 1;
	}
	if (AUTH == 1)
	{
		while (1)
		{
			ClearS();
			menu1();
			while (!scanf("%d", &op))
			{
				getchar();
			}
			getchar();
			switch (op)
			{
			
			case 1:C_query_commodity(&S[0].good[0],&S[1].good[0],N); break;
			case 2:ModifyCommodity(&S[0].good[0],&S[1].good[0],N); break;
			case 3:AVERAGR_PROFIT(&S[0].good[0],&S[1].good[0],N); break;
			case 4:PROFIT_RANKING(&S[0].good[0],&S[1].good[0],N); break;
			case 5:PRINT_IFO(&S[0].good[0],&S[1].good[0],N); break;
			case 6:return 0;
			default:printf("WRONG INPUT!\n");
				break;
			}
			getchar();
		}
	}
	else
	{
		while (1)
		{
			ClearS();
			menu2();
			while (!scanf("%d", &op))
			{
				getchar();
			}
			getchar();
			switch (op)
			{
			case 1: C_query_commodity(&S[0].good[0], &S[1].good[0], N); break;
			case 6:return 0;
			default:printf("WRONG INPUT!\n");
				break;
			}
			getchar();
		}
	}

}
void menu1(void)
{
	printf("            -------------------------------------------------------\n");
	printf("            |            Select your op:                          |\n");
	printf("            |            1.Query commodity information            |\n");
	printf("            |            2.Modify commodity information           |\n");
	printf("            |            3.Calculate average profit margin        |\n");
	printf("            |            4.Calculate profit rate ranking          |\n");
	printf("            |            5.Export all product information         |\n");
	printf("            |            6.Program exit                           |\n");
	printf("            -------------------------------------------------------\n");
}
void menu2(void)
{
	printf("            -------------------------------------------------------\n");
	printf("            |            Select your op:                          |\n");
	printf("            |            1.Query commodity information            |\n");
	printf("            |            6.Program exit                           |\n");
	printf("            -------------------------------------------------------\n");
}
void C_query_commodity(struct commodity* p1,struct commodity* p2,short num)
{
	flat = 0;
	while (!flat)
	{
		printf("Input the name of the commodity('q' to quit):\n\n");
		scanf("%s", in_commodity);
		temp1 = p1; temp2 = p2;
		if (in_commodity[0] == 'q')
			return;
		for (i = 0; i < num&&flat == 0; i++)
		{
			if (strcmp(in_commodity, temp1->cname) == 0)
				flat = 1;
			temp1++; temp2++;
		}
		if(flat==0)
			printf("Can't find the commodity,please input again\n\n");
	}
	temp1--;temp2--;
	printf("-----------------------------------\n");
	printf("Commodity Name: %s\n", temp1->cname);
	printf("Purchase Price: %d\n", temp1->purchase_price);
	printf("Selling Price: %d\n", temp1->selling_price);
	printf("Total Purchases: %d\n", temp1->total);
	printf("Sold Quantity: %d\n", temp1->sell);
	printf("Profit Rate: %d\n", temp1->prt);
	printf("-----------------------------------\n");
	printf("Commodity Name: %s\n", temp2->cname);
	printf("Purchase Price: %d\n", temp2->purchase_price);
	printf("Selling Price: %d\n", temp2->selling_price);
	printf("Total Purchases: %d\n", temp2->total);
	printf("Sold Quantity: %d\n", temp2->sell);
	printf("Ranking: %d\n", temp2->prt);
	putchar('\n');
	system("pause");
	return;
}