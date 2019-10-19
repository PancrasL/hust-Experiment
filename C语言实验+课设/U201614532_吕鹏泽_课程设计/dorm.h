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

#define SCR_ROW 25             /*屏幕行数*/
#define SCR_COL 80             /*屏幕列数*/

/**
 *客人租房信息链结点结构
 */
typedef struct renter_node {
    char id_card[20];           /**< 身份证号*/
    char name[20];             /**< 姓名*/
    char room_id[4];             /**< 入住客房编号*/
    char date_in[18];             /**< 入住时间*/
    char date_out[18];             /**< 退房时间*/
    float months;                 /**< 入住月数*/
    float deposit;            /**< 押金*/
    float shouldpay;            /**< 应缴费用*/
    float realpay;            /**< 实缴费用*/
    struct renter_node *next;  /**< 指向下一结点的指针*/
} RENTER_NODE;

/**
 *客房基本信息链结点结构
 */
typedef struct room_node {
    char room_id[4];         /**< 客房编号*/
    char tel[5];           /**< 电话号码,8+客房号*/
    char type;            /**< 客房类别*/
    float area;       /**< 客房面积*/
    float deposit;        /**< 每月租金*/
    char balcony;              /**< 是否有阳台，1有，0无*/
    char in;              /**< y有客人，n无客人*/
    struct ROOM_NODE *rnext;  /**< 指向租客基本信息支链的指针*/
    struct room_node *next;  /**< 指向下一结点的指针*/
} ROOM_NODE;

/**
 *客房分类信息链结点结构
 */
typedef struct class_node {
    char type;            /**< 客房类别*/
    int pnum;              /**< 最多入住人数*/
    int rnum;                   /**< 客房套数*/
    int emptyr;          /**< 客房未住套数*/
    struct class_node *next;/**指向下一节点*/
    struct room_node *rnext;/**指向客房基本信息节点*/

} CLASS_NODE;

/**
 *客房营业额统计结构
 */
typedef struct income {
    char type;//客房类别
    float sale[12];//记录1-12月的收入
    struct income *next;    	/**< 指向下一结点的指针*/
} INCOME_NODE;
/**
 *客房营业额统计结构
 */
typedef struct room_info{
    char room_id[4];//客房编号
    char type;//客房类别
    float income;//客房收入
    float months;//客人在本年入住该客房总月数
    float in_rate;//客房入住率
    struct room_info *next;//下一节点
}ROOM_INFO;
/**
 *租客入住情况统计结构
 */
typedef struct renter_info{
    char id_card[20];/**身份证号*/
    char name[20];/**姓名*/
    float allmonths;/**入住总月数*/
    float shouldpay;/**应付总金额*/
    float realpay;/**实付总金额*/
    struct renter_info *next;/**指向下一个节点*/
}RENTER_INFO;
/**
 *屏幕窗口信息链结点结点结构
 */
typedef struct layer_node {
    char LayerNo;            /**< 弹出窗口层数*/
    SMALL_RECT rcArea;       /**< 弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /**< 弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
 *标签束结构
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< 标签字符串数组首地址*/
    COORD *pLoc;           /**< 标签定位数组首地址*/
    int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
 *热区结构
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
    char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /**< 热区序号数组首地址*/
    int num;               /**< 热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/
CLASS_NODE *gp_head = NULL;                     /*主链头指针*/


char *gp_sys_name = "房屋出租信息管理系统";    /*系统名称*/
char *gp_room_info_filename = "room.dat";        /*客房信息数据文件*/
char *gp_renter_info_filename = "renter.dat";  /*租客信息数据文件*/
char *gp_class_info_filename = "class.dat";      /*分类信息数据文件*/


char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[X] 退出    Alt+X",//

                       "插入客房分类信息",
                       "修改客房分类信息",
                       "删除客房分类信息",
                       "插入客房基本信息",
                       "修改客房基本信息",
                       "删除客房基本信息",
                       "插入客人租房信息",
                       "修改客人租房信息",
                       "删除客人租房信息",           /*空串用来在弹出菜单中分隔子菜单项，下同*/

                       "客房分类信息查询功能",
                       "客房基本信息查询功能",
                       "客人租房信息查询功能",
                       "[S] 客房基本信息代码",
                       "[T] 客房类别代码",

                       "统计每种类别的客房总数、入住数、未住数",
                       "按月统计本年度各类客房的营业额",
                       "输入年份，统计该年所有客房的营业额、入住月数、入住率",
                       "统计出租月数最多的 10 个客人租房信息",
                       "统计当前所有客房租金及入住情况",

                       "[T] 帮助主题",
                       "[A] 关于...",
                       "清空屏幕"
                      };

int ga_sub_menu_count[] = {2, 9, 5, 5, 3};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/


HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/

int LoadCode(char *filename, char **ppbuffer);  /*代码表加载*/
int CreatList(CLASS_NODE **pphead);              /*数据链表初始化*/
void InitInterface(void);                 /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(CLASS_NODE **pphd);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(CLASS_NODE *phd);                  /*退出系统*/
BOOL ShowModule(char **pString, int n);

BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*保存数据*/
BOOL ExitSys(void);            /*退出系统*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutDorm(void);          /*关于系统*/


BOOL Query(void);      /*查询客房基本信息字符信息*/


/**查找客房节点*/
ROOM_NODE * seekroom(CLASS_NODE *hd,char * r_id);
/**查找租客节点*/
RENTER_NODE * seekrenter(CLASS_NODE *hd,char *date,char * id_card);
/**查找prenter_info指向链表中是id_card，存在返回id_card所在的节点，不存在返回NULL**/
RENTER_INFO * search_renter_info(RENTER_INFO * hd,char *id_card);
/**将租房月数统计链表按租房月数降序排序*/
void sortrenter_info(RENTER_INFO *hd);
/**查询客房类别代码*/
BOOL QueryTypeInfo(void);
/**更新房屋入住情况*/
void Maintain_in(void);
/**统计两个日期之间的月数*/
float Maintain_month(char * date_in,char * date_out);
/**判断日期是否在指定范围之内，是返回1，不是返回0*/
int Judgedate(char *date_in,char *date_out,char *date);


/**输出客房分类信息*/
void printclass(CLASS_NODE *pclass);
/**插入客房分类信息*/
BOOL Insertclass();
/**修改客房分类信息*/
BOOL Maintainclass();
/**删除客房分类信息*/
BOOL Delclass();
/**查询客房分类信息*/
BOOL Queryclass();

/**输出客房基本信息*/
void printroom(ROOM_NODE *proom);
/**插入客房基本信息*/
BOOL Insertroom();
/**修改客房基本信息*/
BOOL Maintainroom();
/**删除客房基本信息*/
BOOL Delroom();
/**查询客房基本信息*/
BOOL Queryroom();

/**输出租客信息*/
void printrenter(RENTER_NODE *prenter);
/**插入租客信息*/
BOOL Insertrenter();
/**修改租客信息*/
BOOL Maintainrenter();
/**删除租客信息*/
BOOL Delrenter();
/**查询租客信息*/
BOOL Queryrenter();

/**统计每种类别的客房总数、入住数、未住数*/
BOOL Staclass();
/**按月统计本年度各类客房的营业额*/
BOOL Staincome();
/**输入年份，统计该年所有客房的营业额、入住月数、入住率*/
BOOL Staroom_info();
/**统计出租月数最多的 10 个客人租房信息*/
BOOL Starenter_info();
/**统计当前所有客房租金及入住情况*/
BOOL Sta_in();

BOOL Clear();

#endif /**< TYPE_H_INCLUDED*/
