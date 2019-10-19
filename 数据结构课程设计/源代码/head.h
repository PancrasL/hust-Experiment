
#include<stdbool.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<time.h>
#include<windows.h>
#define ACCOUNTDATA "account_data"//账户集
#define RELATIONDATA "relation_data"//用户关系（粉丝、朋友、兴趣等）
#define HOBBYDATA "hobby_data"//爱好集
#define L_DATA_NAME "ListData"//多集合管理的线性表信息
#define T_DATA_NAME "SetData"//集合信息
#define LH 1 //左高
#define EH 0 //等高
#define RH -1 //右高
#define TRUE 1
#define FALSE 0
#define X0 50//AVL树图形化显示时根节点的位置
#define OK 1
#define OVERFLOW 0
#define FLAT -100//作为集合存储信息的结束符
#define LIST_INIT_SIZE 50//可管理的最大集合数量

typedef int Status;
typedef struct Info {
	int id;
	char name[20];
	struct BSTNode * friends;//朋友集
	struct BSTNode * fans;//粉丝集
	struct BSTNode * follows;//关注人集
	struct BSTNode * hobby;//爱好集
}Info;//data域
typedef struct BSTNode {
	Info data;
	int bf;//平衡因子
	struct BSTNode *lchild, *rchild;//左右孩子
}BSTNode, *BSTree;
typedef struct {
	struct setdata * pT;
	int listlenth;
	int listsize;
}SqList;//顺序表，用于管理多集合

typedef struct setdata {
	struct BSTNode * pRoot;
	char  name[20];
}SetData;//集合信息(线性表的结点)
/*平衡调节*/
void L_Rotate(BSTree &p);//左旋
void R_Rotate(BSTree &p);//右旋
void LeftBalance(BSTree &T);//左平衡处理
void RightBalance(BSTree &T);//右平衡处理
/*AVL树的基本运算*/
Status InitAVL(BSTree &T);//创建AVL树
Status InsertAVL(BSTree &T, Info e, bool &taller);//插入结点
Status DestroyAVL(BSTree &T);//销毁AVL树
Status DeleteAVL(BSTree& T, int key, bool& shorter);//删除AVL树中结点
BSTNode * SearchAVL(BSTree& T, int key);//在AVL树中查找关键字为key的结点
Status InOrderTraverse(BSTree T, Status(*visit)(Info e));//中序遍历
/*集合的基本运算*/
Status set_init(BSTree &T);//初始化集合
Status set_destroy(BSTree &T);//销毁集合
Status set_insert(BSTree &T, Info e);//插入元素
Status set_remove(BSTree &T, int key);//删除元素
Status set_intersection(BSTree T1, BSTree T2, BSTree &T3);//求T1与T2的交，存在T3中
Status set_union(BSTree &T1, BSTree T2);//求T1与T2的并，结果存在T1中
Status set_difference(BSTree T1, BSTree T2, BSTree &T3);//求集合T1与集合T2的差(T1-T2)，存在集合T中
int set_size(BSTree T);//集合代销
BSTNode * set_member(BSTree T, int key);//集合成员
Status set_subset(BSTree T1, BSTree T2);//集合子集
Status set_equal(BSTree T1, BSTree T2);//集合相等
Status set_traverse(BSTree T, Status(*visit)(Info e));//集合遍历
/*集合演示函数*/
void menu1(void);//集合操作演示菜单
void set_display(void);//集合演示
void printKey(BSTree p, int x, int y);//在命令行(x,y)处输出结点p的关键字
void graphAVL(BSTree T, int x, int l, int y);//将AVL树图形化显示（x,y为根结点坐标，l为根结点的左右孩子相距距离）
void setxy(short x, short y);  //定位光标到（x，y）
Status visit(Info e);
int SelectSet(SqList L);
int get_cursor_x(void);//获取当前光标横坐标
int get_cursor_y(void);//获取当前光标纵坐标
Status SaveSetData(SqList L);
Status LoadSetData(SqList &L);
Status SaveSet(BSTree T, FILE *fp);
Status LoadSet(BSTree &T, FILE *fp);
/*人际关系模拟函数*/
void menu2(void);//人际关系模拟演示菜单
void apply_display(void);//应用演示
Status destroy_accountset(BSTree &T);//删除账户集合
Status data_input(BSTree T, Info &in);//为集合T中插入的新节点输入data,成功返回TRUE，失败返回FALSE
int confirm_save(void);//确认是否保存，是返回1，否返回0
int select_display(void);//确认演示功能,集合演示返回1，应用演示返回2，退出返回0
void maintain_data(BSTree &Account,BSTree Hobby);//维护用户信息
void common_follow(BSTree Account);//共同关注
void common_friend(BSTree Account);//共同好友
void second_friend(BSTree Account);//二度好友
void S_friend(BSTree Account, BSTree p, BSTree &T);//添加*p的二度好友，结果存在T中
void common_hobby(BSTree Account,BSTree Hobby);//共同爱好
Status save_account(BSTree T, FILE  *fp);//保存账户信息
Status save_hobby(BSTree T,FILE *fp);//保存兴趣集合
Status save_relation(BSTree T, FILE *fp);//保存账户关系1
Status save_rela(BSTree T, FILE *fp);//保存账户关系2
Status load_account(BSTree &T, FILE *fp);//加载账户信息
Status load_relation(BSTree &T, FILE *fp);//加载关系信息
Status load_hobby(BSTree &Hobby,FILE *fp);//加载兴趣集合
Status load_data(BSTree &Account, BSTree &Hobby);//加载数据
Status save_data(BSTree Account, BSTree Hobby);//保存数据
void account_data(BSTree Account, BSTree Hobby);//显示用户的关注人、朋友、粉丝、兴趣
void print_account_data(BSTree Account, BSTree T);//根据T中的用户id在Account中查找相应的用户姓名并显示
void proc(void);

void AVL_display(void);
void menu3(void);