%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void display(struct node *,int);//ǰ�������
%}

/*��������ֵ����*/
%union {
    int type_int;
    float type_float;
    char type_id[32];
	char type_char[4];
	struct node *ptr;
};

/*���ս������˵��*/
%type <ptr> program             //��ʼ�﷨��Ԫ
%type <ptr> ExtDefList          //0������ExtDef
%type <ptr> ExtDef              //һ��ȫ�ֱ������ṹ������Ķ���
%type <ptr> Specifier           //����������
%type <ptr> ExtDecList          //0��������������a,b,c    (int a,b,c;)
%type <ptr> FuncDec             //����ͷ
%type <ptr> CompSt              //������
%type <ptr> VarList             //�β��б�
%type <ptr> VarDec              //һ�������Ķ���
%type <ptr> ParamDec            //һ���βεĶ���
%type <ptr> Stmt                //һ�����
%type <ptr> StmList             //�������
%type <ptr> DefList             //�����������
%type <ptr> Def                 //һ����������
%type <ptr> DecList				//�����б�
%type <ptr> Dec					//һ������
%type <ptr> Exp                 //һ�����ʽ
%type <ptr> Args                //ʵ���б�


/*�ս������˵��*/
%token <type_int> INT
%token <type_id> ID RELOP ASSIGNOP TYPE AUTOINC AUTODEC
%token <type_float> FLOAT
%token <type_char> CHAR
//lex.l��ʹ�õ���������
%token LP RP LB RB LC RC                        //( ) [ ] { }
%token SEMI COMMA                               //; , 
%token PLUS MINUS STAR DIV                      //+ - * /
%token AND OR NOT                               //&& || !
%token IF ELSE WHILE RETURN
/*���ȼ��ͽ���Զ���*/
%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left AUTOINC AUTODEC
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%
//����
program: ExtDefList {printf("����\n");display($1,0);}       //display��ʾ�﷨��
        ;

//�ⲿ���������б�
ExtDefList: {$$=NULL;}
		| ExtDef ExtDefList  		{$$=mknode(EXT_DEF_LIST,$1,$2,NULL,yylineno);}		//����int a;int b;int c;

//һ��ȫ�ֱ�������|һ����������|һ���ṹ�嶨��
ExtDef:   Specifier ExtDecList SEMI	{$$=mknode(EXT_VAR_DEF,$1,$2,NULL,yylineno);}		//����int a,b;
		| Specifier FuncDec CompSt	{$$=mknode(FUNC_DEF,$1,$2,$3,yylineno);}			//����int fun() {}
		| error SEMI				{$$=NULL;printf("extern define error at line %d\n",yylineno);}
		;

//����������
Specifier: TYPE 					{$$=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy($$->type,$1);}//����int��float
		;
		
//0��������������a,b,c    (int a,b,c;)
ExtDecList: VarDec 					{$$=$1;}         									//���� a
		| VarDec COMMA ExtDecList	{$$=mknode(EXT_DEC_LIST,$1,$3,NULL,yylineno);}		//���� a,b,c
		| VarDec ASSIGNOP Exp		{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}//����a=1
        ;

//��ʶ��
VarDec:  ID							{$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| VarDec LB INT RB 			{$$=mknode(ARRAY_DEF,$1,NULL,NULL,yylineno);$$->array_size[0]=$3;}//һά����
		;

//����ͷ
FuncDec: ID LP VarList RP  			{$$=mknode(FUNC_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//����f(int a,int b)
		|ID LP RP  					{$$=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//����f()
		;
//�β��б�
VarList: ParamDec 					{$$=$1;}     //�����β�
        | ParamDec COMMA  VarList 	{$$=mknode(PARAM_LIST,$1,$3,NULL,yylineno);}				//����β�
        ;
		
//һ���βεĶ���
ParamDec: Specifier VarDec        	{$$=mknode(PARAM_DEC,$1,$2,NULL,yylineno);}					//���� int a
        ;

//������
CompSt: LC DefList StmList RC    	{$$=mknode(COMP_STM,$2,$3,NULL,yylineno);}					//���� { ������ }
        ;

//����б�
StmList: {$$=NULL;}
        | Stmt StmList  			{$$=mknode(STM_LIST,$1,$2,NULL,yylineno);}					//һ��һ�����ӹ��ɵ�����
        ;
//һ�����
Stmt:   Exp SEMI  					{$$=mknode(EXP_STMT,$1,NULL,NULL,yylineno);}				//���ʽ����;��β�ľ���
        | CompSt  					{$$=$1;}													//{}�����ſ�
        | RETURN Exp SEMI   		{$$=mknode(RETURN,$2,NULL,NULL,yylineno);}					//return���
        | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE  {$$=mknode(IF_THEN,$3,$5,NULL,yylineno);}	//����if(a>b) ...
        | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(IF_THEN_ELSE,$3,$5,$7,yylineno);}			//����if(a>b) ...  else  ...
        | WHILE LP Exp RP Stmt 		{$$=mknode(WHILE,$3,$5,NULL,yylineno);}						//����while(a>b)  ...
        | error SEMI 				{$$=NULL;printf("statement error at line %d\n",yylineno);}
        ;
//�ֲ����������б�
DefList: {$$=NULL; }
		| Def DefList 				{$$=mknode(DEF_LIST,$1,$2,NULL,yylineno);}					//�����������飬���û�б�����������˾͸�ֵNULL
		;
//һ���ֲ���������
Def:  	Specifier DecList SEMI		{$$=mknode(VAR_DEF,$1,$2,NULL,yylineno);}					//float x,y=20;  �����������
		;
//0�������ֲ�����������a,b,c
DecList: Dec  {$$=$1;}
		| Dec COMMA DecList  		{$$=mknode(DEC_LIST,$1,$3,NULL,yylineno);}
		;
//һ���ֲ�����������a
Dec:	VarDec  {$$=$1;}
		| VarDec ASSIGNOP Exp  		{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}//int x,y=20�е�  x����y=20  ����
		;

//һ�����ʽ
Exp:    Exp ASSIGNOP Exp 			{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}
		| Exp AND Exp   			{$$=mknode(AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"AND");}
		| Exp OR Exp    			{$$=mknode(OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"OR");}
		| Exp RELOP Exp 			{$$=mknode(RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}//�ʷ�������ϵ�����������ֵ������$2��
		| Exp PLUS Exp  			{$$=mknode(PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"PLUS");}
		| Exp MINUS Exp 			{$$=mknode(MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"MINUS");}
		| Exp STAR Exp  			{$$=mknode(STAR,$1,$3,NULL,yylineno);strcpy($$->type_id,"STAR");}
		| Exp DIV Exp   			{$$=mknode(DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"DIV");}
		| LP Exp RP     			{$$=$2;}
		| MINUS Exp %prec UMINUS  	{$$=mknode(UMINUS,$2,NULL,NULL,yylineno);strcpy($$->type_id,"UMINUS");}//%precΪ�ù���ָ��һ�����ȼ�
		| AUTOINC Exp  				{$$=mknode(AUTOINC,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| AUTODEC Exp   			{$$=mknode(AUTODEC,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| Exp  AUTOINC  			{$$=mknode(AUTOINC,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
		| Exp  AUTODEC  			{$$=mknode(AUTODEC,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
		| NOT Exp       			{$$=mknode(NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"NOT");}   //��a<bʱ����
		| ID LP Args RP 			{$$=mknode(FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//�������� abc()  ()�е�����
		| ID LP RP      			{$$=NULL;}
		| VarDec LB INT RB {$$=mknode(ARRAY_ITEM,$1,NULL,NULL,yylineno);strcpy($$->type_id,"ARRAY_ITEM");$$->array_size[0]=$3;}//����
		| ID            			{$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| INT           			{$$=mknode(INT,NULL,NULL,NULL,yylineno);$$->type_int=$1;}
		| FLOAT         			{$$=mknode(FLOAT,NULL,NULL,NULL,yylineno);$$->type_float=$1;}
		| CHAR          			{$$=mknode(CHAR,NULL,NULL,NULL,yylineno);strcpy($$->type_char,$1);}
		;
//ʵ���б�
Args:	Exp COMMA Args				{$$=mknode(ARGS,$1,$3,NULL,yylineno);}	//abc(1+2,a*c)  ʵ�θ�����Ϊ����
		| Exp						{$$=$1;}//ֻ��һ��������Ҳ�������Args�����Ƴ�exp
		;

%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
	yylineno=1;
	yyparse();
	return 0;
}

int yyerror(char *s){
   printf("%s %s at line %d\n",s,yytext,yylineno);
   return 0;
 }