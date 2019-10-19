#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>
#include <math.h>


#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*��Ļ����*/
#define SCR_COL 80             /*��Ļ����*/

/**
 *�����ⷿ��Ϣ�����ṹ
 */
typedef struct renter_node {
    char id_card[20];           /**< ���֤��*/
    char name[20];             /**< ����*/
    char room_id[4];             /**< ��ס�ͷ����*/
    char date_in[18];             /**< ��סʱ��*/
    char date_out[18];             /**< �˷�ʱ��*/
    float months;                 /**< ��ס����*/
    float deposit;            /**< Ѻ��*/
    float shouldpay;            /**< Ӧ�ɷ���*/
    float realpay;            /**< ʵ�ɷ���*/
    struct renter_node *next;  /**< ָ����һ����ָ��*/
} RENTER_NODE;

/**
 *�ͷ�������Ϣ�����ṹ
 */
typedef struct room_node {
    char room_id[4];         /**< �ͷ����*/
    char tel[5];           /**< �绰����,8+�ͷ���*/
    char type;            /**< �ͷ����*/
    float area;       /**< �ͷ����*/
    float deposit;        /**< ÿ�����*/
    char balcony;              /**< �Ƿ�����̨��1�У�0��*/
    char in;              /**< y�п��ˣ�n�޿���*/
    struct ROOM_NODE *rnext;  /**< ָ����ͻ�����Ϣ֧����ָ��*/
    struct room_node *next;  /**< ָ����һ����ָ��*/
} ROOM_NODE;

/**
 *�ͷ�������Ϣ�����ṹ
 */
typedef struct class_node {
    char type;            /**< �ͷ����*/
    int pnum;              /**< �����ס����*/
    int rnum;                   /**< �ͷ�����*/
    int emptyr;          /**< �ͷ�δס����*/
    struct class_node *next;/**ָ����һ�ڵ�*/
    struct room_node *rnext;/**ָ��ͷ�������Ϣ�ڵ�*/

} CLASS_NODE;

/**
 *�ͷ�Ӫҵ��ͳ�ƽṹ
 */
typedef struct income {
    char type;//�ͷ����
    float sale[12];//��¼1-12�µ�����
    struct income *next;    	/**< ָ����һ����ָ��*/
} INCOME_NODE;
/**
 *�ͷ�Ӫҵ��ͳ�ƽṹ
 */
typedef struct room_info{
    char room_id[4];//�ͷ����
    char type;//�ͷ����
    float income;//�ͷ�����
    float months;//�����ڱ�����ס�ÿͷ�������
    float in_rate;//�ͷ���ס��
    struct room_info *next;//��һ�ڵ�
}ROOM_INFO;
/**
 *�����ס���ͳ�ƽṹ
 */
typedef struct renter_info{
    char id_card[20];/**���֤��*/
    char name[20];/**����*/
    float allmonths;/**��ס������*/
    float shouldpay;/**Ӧ���ܽ��*/
    float realpay;/**ʵ���ܽ��*/
    struct renter_info *next;/**ָ����һ���ڵ�*/
}RENTER_INFO;
/**
 *��Ļ������Ϣ�������ṹ
 */
typedef struct layer_node {
    char LayerNo;            /**< �������ڲ���*/
    SMALL_RECT rcArea;       /**< ����������������*/
    CHAR_INFO *pContent;     /**< �������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
 *��ǩ���ṹ
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;           /**< ��ǩ��λ�����׵�ַ*/
    int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
 *�����ṹ
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
    char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /**< ������������׵�ַ*/
    int num;               /**< ��������*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*����������Ϣ����ͷ*/
CLASS_NODE *gp_head = NULL;                     /*����ͷָ��*/


char *gp_sys_name = "���ݳ�����Ϣ����ϵͳ";    /*ϵͳ����*/
char *gp_room_info_filename = "room.dat";        /*�ͷ���Ϣ�����ļ�*/
char *gp_renter_info_filename = "renter.dat";  /*�����Ϣ�����ļ�*/
char *gp_class_info_filename = "class.dat";      /*������Ϣ�����ļ�*/


char *ga_main_menu[] = {"�ļ�(F)",             /*ϵͳ���˵���*/
    	                "����ά��(M)",
                        "���ݲ�ѯ(Q)",
                        "����ͳ��(S)",
                        "����(H)"
                       };

char *ga_sub_menu[] = {"[S] ���ݱ���",          /*ϵͳ�Ӳ˵���*/
                       "[X] �˳�    Alt+X",//

                       "����ͷ�������Ϣ",
                       "�޸Ŀͷ�������Ϣ",
                       "ɾ���ͷ�������Ϣ",
                       "����ͷ�������Ϣ",
                       "�޸Ŀͷ�������Ϣ",
                       "ɾ���ͷ�������Ϣ",
                       "��������ⷿ��Ϣ",
                       "�޸Ŀ����ⷿ��Ϣ",
                       "ɾ�������ⷿ��Ϣ",           /*�մ������ڵ����˵��зָ��Ӳ˵����ͬ*/

                       "�ͷ�������Ϣ��ѯ����",
                       "�ͷ�������Ϣ��ѯ����",
                       "�����ⷿ��Ϣ��ѯ����",
                       "[S] �ͷ�������Ϣ����",
                       "[T] �ͷ�������",

                       "ͳ��ÿ�����Ŀͷ���������ס����δס��",
                       "����ͳ�Ʊ���ȸ���ͷ���Ӫҵ��",
                       "������ݣ�ͳ�Ƹ������пͷ���Ӫҵ���ס��������ס��",
                       "ͳ�Ƴ����������� 10 �������ⷿ��Ϣ",
                       "ͳ�Ƶ�ǰ���пͷ������ס���",

                       "[T] ��������",
                       "[A] ����...",
                       "�����Ļ"
                      };

int ga_sub_menu_count[] = {2, 9, 5, 5, 3};  /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char gc_sys_state = '\0';   /*��������ϵͳ״̬���ַ�*/


HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/

int LoadCode(char *filename, char **ppbuffer);  /*��������*/
int CreatList(CLASS_NODE **pphead);              /*���������ʼ��*/
void InitInterface(void);                 /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(CLASS_NODE **pphd);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(CLASS_NODE *phd);                  /*�˳�ϵͳ*/
BOOL ShowModule(char **pString, int n);

BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*��������*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/
BOOL HelpTopic(void);          /*��������*/
BOOL AboutDorm(void);          /*����ϵͳ*/


BOOL Query(void);      /*��ѯ�ͷ�������Ϣ�ַ���Ϣ*/


/**���ҿͷ��ڵ�*/
ROOM_NODE * seekroom(CLASS_NODE *hd,char * r_id);
/**������ͽڵ�*/
RENTER_NODE * seekrenter(CLASS_NODE *hd,char *date,char * id_card);
/**����prenter_infoָ����������id_card�����ڷ���id_card���ڵĽڵ㣬�����ڷ���NULL**/
RENTER_INFO * search_renter_info(RENTER_INFO * hd,char *id_card);
/**���ⷿ����ͳ�������ⷿ������������*/
void sortrenter_info(RENTER_INFO *hd);
/**��ѯ�ͷ�������*/
BOOL QueryTypeInfo(void);
/**���·�����ס���*/
void Maintain_in(void);
/**ͳ����������֮�������*/
float Maintain_month(char * date_in,char * date_out);
/**�ж������Ƿ���ָ����Χ֮�ڣ��Ƿ���1�����Ƿ���0*/
int Judgedate(char *date_in,char *date_out,char *date);


/**����ͷ�������Ϣ*/
void printclass(CLASS_NODE *pclass);
/**����ͷ�������Ϣ*/
BOOL Insertclass();
/**�޸Ŀͷ�������Ϣ*/
BOOL Maintainclass();
/**ɾ���ͷ�������Ϣ*/
BOOL Delclass();
/**��ѯ�ͷ�������Ϣ*/
BOOL Queryclass();

/**����ͷ�������Ϣ*/
void printroom(ROOM_NODE *proom);
/**����ͷ�������Ϣ*/
BOOL Insertroom();
/**�޸Ŀͷ�������Ϣ*/
BOOL Maintainroom();
/**ɾ���ͷ�������Ϣ*/
BOOL Delroom();
/**��ѯ�ͷ�������Ϣ*/
BOOL Queryroom();

/**��������Ϣ*/
void printrenter(RENTER_NODE *prenter);
/**���������Ϣ*/
BOOL Insertrenter();
/**�޸������Ϣ*/
BOOL Maintainrenter();
/**ɾ�������Ϣ*/
BOOL Delrenter();
/**��ѯ�����Ϣ*/
BOOL Queryrenter();

/**ͳ��ÿ�����Ŀͷ���������ס����δס��*/
BOOL Staclass();
/**����ͳ�Ʊ���ȸ���ͷ���Ӫҵ��*/
BOOL Staincome();
/**������ݣ�ͳ�Ƹ������пͷ���Ӫҵ���ס��������ס��*/
BOOL Staroom_info();
/**ͳ�Ƴ����������� 10 �������ⷿ��Ϣ*/
BOOL Starenter_info();
/**ͳ�Ƶ�ǰ���пͷ������ס���*/
BOOL Sta_in();

BOOL Clear();

#endif /**< TYPE_H_INCLUDED*/
