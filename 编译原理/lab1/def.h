enum node_kind
{
        EXT_DEF_LIST,
        EXT_VAR_DEF,
        FUNC_DEF,
        FUNC_DEC,
        EXT_DEC_LIST,
        STRUCT_TYPE_DEF,
        STRUCT_VAR_DEF,
        STRUCT_DEF,
        ARRAY_DEF,
		ARRAY_ITEM,
        STRUCT_SPECIFIER,
        PARAM_LIST,
        PARAM_DEC,
        VAR_DEF,
        DEC_LIST,
        DEF_LIST,
        COMP_STM,
        STM_LIST,
        EXP_STMT,
        IF_THEN,
        IF_THEN_ELSE,
        FUNC_CALL,
        ARGS
};

struct node {
	enum node_kind kind;		//表示节点类型
	union {
		  char type_id[32];     //标识符叶结点
		  int type_int;         //整常数叶结点
		  float type_float;       //浮点常数叶结点
		  char type_char[4];	//字符叶节点
		  int array_size[2];	//数组大小，最高支持二维
	      };
    struct node *ptr[3];            //子树
    char type[10],op[10];           //类型描述符的字符串值
    int pos;                        //数组元素的下标
};

struct node *mknode(int kind,struct node *first,struct node *second, struct node *third,int pos );//生成树节点
