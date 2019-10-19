
#include<stdbool.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<time.h>
#include<windows.h>
#define ACCOUNTDATA "account_data"//�˻���
#define RELATIONDATA "relation_data"//�û���ϵ����˿�����ѡ���Ȥ�ȣ�
#define HOBBYDATA "hobby_data"//���ü�
#define L_DATA_NAME "ListData"//�༯�Ϲ�������Ա���Ϣ
#define T_DATA_NAME "SetData"//������Ϣ
#define LH 1 //���
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ�
#define TRUE 1
#define FALSE 0
#define X0 50//AVL��ͼ�λ���ʾʱ���ڵ��λ��
#define OK 1
#define OVERFLOW 0
#define FLAT -100//��Ϊ���ϴ洢��Ϣ�Ľ�����
#define LIST_INIT_SIZE 50//�ɹ������󼯺�����

typedef int Status;
typedef struct Info {
	int id;
	char name[20];
	struct BSTNode * friends;//���Ѽ�
	struct BSTNode * fans;//��˿��
	struct BSTNode * follows;//��ע�˼�
	struct BSTNode * hobby;//���ü�
}Info;//data��
typedef struct BSTNode {
	Info data;
	int bf;//ƽ������
	struct BSTNode *lchild, *rchild;//���Һ���
}BSTNode, *BSTree;
typedef struct {
	struct setdata * pT;
	int listlenth;
	int listsize;
}SqList;//˳������ڹ���༯��

typedef struct setdata {
	struct BSTNode * pRoot;
	char  name[20];
}SetData;//������Ϣ(���Ա�Ľ��)
/*ƽ�����*/
void L_Rotate(BSTree &p);//����
void R_Rotate(BSTree &p);//����
void LeftBalance(BSTree &T);//��ƽ�⴦��
void RightBalance(BSTree &T);//��ƽ�⴦��
/*AVL���Ļ�������*/
Status InitAVL(BSTree &T);//����AVL��
Status InsertAVL(BSTree &T, Info e, bool &taller);//������
Status DestroyAVL(BSTree &T);//����AVL��
Status DeleteAVL(BSTree& T, int key, bool& shorter);//ɾ��AVL���н��
BSTNode * SearchAVL(BSTree& T, int key);//��AVL���в��ҹؼ���Ϊkey�Ľ��
Status InOrderTraverse(BSTree T, Status(*visit)(Info e));//�������
/*���ϵĻ�������*/
Status set_init(BSTree &T);//��ʼ������
Status set_destroy(BSTree &T);//���ټ���
Status set_insert(BSTree &T, Info e);//����Ԫ��
Status set_remove(BSTree &T, int key);//ɾ��Ԫ��
Status set_intersection(BSTree T1, BSTree T2, BSTree &T3);//��T1��T2�Ľ�������T3��
Status set_union(BSTree &T1, BSTree T2);//��T1��T2�Ĳ����������T1��
Status set_difference(BSTree T1, BSTree T2, BSTree &T3);//�󼯺�T1�뼯��T2�Ĳ�(T1-T2)�����ڼ���T��
int set_size(BSTree T);//���ϴ���
BSTNode * set_member(BSTree T, int key);//���ϳ�Ա
Status set_subset(BSTree T1, BSTree T2);//�����Ӽ�
Status set_equal(BSTree T1, BSTree T2);//�������
Status set_traverse(BSTree T, Status(*visit)(Info e));//���ϱ���
/*������ʾ����*/
void menu1(void);//���ϲ�����ʾ�˵�
void set_display(void);//������ʾ
void printKey(BSTree p, int x, int y);//��������(x,y)��������p�Ĺؼ���
void graphAVL(BSTree T, int x, int l, int y);//��AVL��ͼ�λ���ʾ��x,yΪ��������꣬lΪ���������Һ��������룩
void setxy(short x, short y);  //��λ��굽��x��y��
Status visit(Info e);
int SelectSet(SqList L);
int get_cursor_x(void);//��ȡ��ǰ��������
int get_cursor_y(void);//��ȡ��ǰ���������
Status SaveSetData(SqList L);
Status LoadSetData(SqList &L);
Status SaveSet(BSTree T, FILE *fp);
Status LoadSet(BSTree &T, FILE *fp);
/*�˼ʹ�ϵģ�⺯��*/
void menu2(void);//�˼ʹ�ϵģ����ʾ�˵�
void apply_display(void);//Ӧ����ʾ
Status destroy_accountset(BSTree &T);//ɾ���˻�����
Status data_input(BSTree T, Info &in);//Ϊ����T�в�����½ڵ�����data,�ɹ�����TRUE��ʧ�ܷ���FALSE
int confirm_save(void);//ȷ���Ƿ񱣴棬�Ƿ���1���񷵻�0
int select_display(void);//ȷ����ʾ����,������ʾ����1��Ӧ����ʾ����2���˳�����0
void maintain_data(BSTree &Account,BSTree Hobby);//ά���û���Ϣ
void common_follow(BSTree Account);//��ͬ��ע
void common_friend(BSTree Account);//��ͬ����
void second_friend(BSTree Account);//���Ⱥ���
void S_friend(BSTree Account, BSTree p, BSTree &T);//���*p�Ķ��Ⱥ��ѣ��������T��
void common_hobby(BSTree Account,BSTree Hobby);//��ͬ����
Status save_account(BSTree T, FILE  *fp);//�����˻���Ϣ
Status save_hobby(BSTree T,FILE *fp);//������Ȥ����
Status save_relation(BSTree T, FILE *fp);//�����˻���ϵ1
Status save_rela(BSTree T, FILE *fp);//�����˻���ϵ2
Status load_account(BSTree &T, FILE *fp);//�����˻���Ϣ
Status load_relation(BSTree &T, FILE *fp);//���ع�ϵ��Ϣ
Status load_hobby(BSTree &Hobby,FILE *fp);//������Ȥ����
Status load_data(BSTree &Account, BSTree &Hobby);//��������
Status save_data(BSTree Account, BSTree Hobby);//��������
void account_data(BSTree Account, BSTree Hobby);//��ʾ�û��Ĺ�ע�ˡ����ѡ���˿����Ȥ
void print_account_data(BSTree Account, BSTree T);//����T�е��û�id��Account�в�����Ӧ���û���������ʾ
void proc(void);

void AVL_display(void);
void menu3(void);