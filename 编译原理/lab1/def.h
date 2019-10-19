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
	enum node_kind kind;		//��ʾ�ڵ�����
	union {
		  char type_id[32];     //��ʶ��Ҷ���
		  int type_int;         //������Ҷ���
		  float type_float;       //���㳣��Ҷ���
		  char type_char[4];	//�ַ�Ҷ�ڵ�
		  int array_size[2];	//�����С�����֧�ֶ�ά
	      };
    struct node *ptr[3];            //����
    char type[10],op[10];           //�������������ַ���ֵ
    int pos;                        //����Ԫ�ص��±�
};

struct node *mknode(int kind,struct node *first,struct node *second, struct node *third,int pos );//�������ڵ�
