%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void display(struct node *,int);//前序遍历树
%}

/*定义语义值类型*/
%union {
    int type_int;
    float type_float;
    char type_id[32];
	char type_char[4];
	struct node *ptr;
};

/*非终结符类型说明*/
%type <ptr> program             //初始语法单元
%type <ptr> ExtDefList          //0个或多个ExtDef
%type <ptr> ExtDef              //一个全局变量、结构体或函数的定义
%type <ptr> Specifier           //类型描述符
%type <ptr> ExtDecList          //0个或多个变量，如a,b,c    (int a,b,c;)
%type <ptr> FuncDec             //函数头
%type <ptr> CompSt              //函数体
%type <ptr> VarList             //形参列表
%type <ptr> VarDec              //一个变量的定义
%type <ptr> ParamDec            //一个形参的定义
%type <ptr> Stmt                //一条语句
%type <ptr> StmList             //多条语句
%type <ptr> DefList             //多个变量定义
%type <ptr> Def                 //一条变量定义
%type <ptr> DecList				//变量列表
%type <ptr> Dec					//一个变量
%type <ptr> Exp                 //一个表达式
%type <ptr> Args                //实参列表


/*终结符类型说明*/
%token <type_int> INT
%token <type_id> ID RELOP ASSIGNOP TYPE AUTOINC AUTODEC
%token <type_float> FLOAT
%token <type_char> CHAR
//lex.l中使用到的类型码
%token LP RP LB RB LC RC                        //( ) [ ] { }
%token SEMI COMMA                               //; , 
%token PLUS MINUS STAR DIV                      //+ - * /
%token AND OR NOT                               //&& || !
%token IF ELSE WHILE RETURN
/*优先级和结合性定义*/
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
//程序
program: ExtDefList {printf("程序\n");display($1,0);}       //display显示语法树
        ;

//外部变量定义列表
ExtDefList: {$$=NULL;}
		| ExtDef ExtDefList  		{$$=mknode(EXT_DEF_LIST,$1,$2,NULL,yylineno);}		//形如int a;int b;int c;

//一个全局变量定义|一个函数定义|一个结构体定义
ExtDef:   Specifier ExtDecList SEMI	{$$=mknode(EXT_VAR_DEF,$1,$2,NULL,yylineno);}		//形如int a,b;
		| Specifier FuncDec CompSt	{$$=mknode(FUNC_DEF,$1,$2,$3,yylineno);}			//形如int fun() {}
		| error SEMI				{$$=NULL;printf("extern define error at line %d\n",yylineno);}
		;

//类型描述符
Specifier: TYPE 					{$$=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy($$->type,$1);}//形如int、float
		;
		
//0个或多个变量，如a,b,c    (int a,b,c;)
ExtDecList: VarDec 					{$$=$1;}         									//形如 a
		| VarDec COMMA ExtDecList	{$$=mknode(EXT_DEC_LIST,$1,$3,NULL,yylineno);}		//形如 a,b,c
		| VarDec ASSIGNOP Exp		{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}//形如a=1
        ;

//标识符
VarDec:  ID							{$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| VarDec LB INT RB 			{$$=mknode(ARRAY_DEF,$1,NULL,NULL,yylineno);$$->array_size[0]=$3;}//一维数组
		;

//函数头
FuncDec: ID LP VarList RP  			{$$=mknode(FUNC_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//形如f(int a,int b)
		|ID LP RP  					{$$=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//形如f()
		;
//形参列表
VarList: ParamDec 					{$$=$1;}     //单个形参
        | ParamDec COMMA  VarList 	{$$=mknode(PARAM_LIST,$1,$3,NULL,yylineno);}				//多个形参
        ;
		
//一个形参的定义
ParamDec: Specifier VarDec        	{$$=mknode(PARAM_DEC,$1,$2,NULL,yylineno);}					//形如 int a
        ;

//函数体
CompSt: LC DefList StmList RC    	{$$=mknode(COMP_STM,$2,$3,NULL,yylineno);}					//形如 { 函数体 }
        ;

//语句列表
StmList: {$$=NULL;}
        | Stmt StmList  			{$$=mknode(STM_LIST,$1,$2,NULL,yylineno);}					//一个一个句子构成的语句块
        ;
//一条语句
Stmt:   Exp SEMI  					{$$=mknode(EXP_STMT,$1,NULL,NULL,yylineno);}				//表达式并以;结尾的句子
        | CompSt  					{$$=$1;}													//{}大括号块
        | RETURN Exp SEMI   		{$$=mknode(RETURN,$2,NULL,NULL,yylineno);}					//return语句
        | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE  {$$=mknode(IF_THEN,$3,$5,NULL,yylineno);}	//形如if(a>b) ...
        | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(IF_THEN_ELSE,$3,$5,$7,yylineno);}			//形如if(a>b) ...  else  ...
        | WHILE LP Exp RP Stmt 		{$$=mknode(WHILE,$3,$5,NULL,yylineno);}						//形如while(a>b)  ...
        | error SEMI 				{$$=NULL;printf("statement error at line %d\n",yylineno);}
        ;
//局部变量定义列表
DefList: {$$=NULL; }
		| Def DefList 				{$$=mknode(DEF_LIST,$1,$2,NULL,yylineno);}					//变量声明语句块，如果没有变量定义语句了就赋值NULL
		;
//一个局部变量定义
Def:  	Specifier DecList SEMI		{$$=mknode(VAR_DEF,$1,$2,NULL,yylineno);}					//float x,y=20;  变量定义语句
		;
//0个或多个局部变量，形如a,b,c
DecList: Dec  {$$=$1;}
		| Dec COMMA DecList  		{$$=mknode(DEC_LIST,$1,$3,NULL,yylineno);}
		;
//一个局部变量，形如a
Dec:	VarDec  {$$=$1;}
		| VarDec ASSIGNOP Exp  		{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}//int x,y=20中的  x或者y=20  部分
		;

//一个表达式
Exp:    Exp ASSIGNOP Exp 			{$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}
		| Exp AND Exp   			{$$=mknode(AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"AND");}
		| Exp OR Exp    			{$$=mknode(OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"OR");}
		| Exp RELOP Exp 			{$$=mknode(RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}//词法分析关系运算符号自身值保存在$2中
		| Exp PLUS Exp  			{$$=mknode(PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"PLUS");}
		| Exp MINUS Exp 			{$$=mknode(MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"MINUS");}
		| Exp STAR Exp  			{$$=mknode(STAR,$1,$3,NULL,yylineno);strcpy($$->type_id,"STAR");}
		| Exp DIV Exp   			{$$=mknode(DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"DIV");}
		| LP Exp RP     			{$$=$2;}
		| MINUS Exp %prec UMINUS  	{$$=mknode(UMINUS,$2,NULL,NULL,yylineno);strcpy($$->type_id,"UMINUS");}//%prec为该规则指定一个优先级
		| AUTOINC Exp  				{$$=mknode(AUTOINC,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| AUTODEC Exp   			{$$=mknode(AUTODEC,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| Exp  AUTOINC  			{$$=mknode(AUTOINC,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
		| Exp  AUTODEC  			{$$=mknode(AUTODEC,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
		| NOT Exp       			{$$=mknode(NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"NOT");}   //！a<b时调用
		| ID LP Args RP 			{$$=mknode(FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数调用 abc()  ()中的内容
		| ID LP RP      			{$$=NULL;}
		| VarDec LB INT RB {$$=mknode(ARRAY_ITEM,$1,NULL,NULL,yylineno);strcpy($$->type_id,"ARRAY_ITEM");$$->array_size[0]=$3;}//数组
		| ID            			{$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
		| INT           			{$$=mknode(INT,NULL,NULL,NULL,yylineno);$$->type_int=$1;}
		| FLOAT         			{$$=mknode(FLOAT,NULL,NULL,NULL,yylineno);$$->type_float=$1;}
		| CHAR          			{$$=mknode(CHAR,NULL,NULL,NULL,yylineno);strcpy($$->type_char,$1);}
		;
//实参列表
Args:	Exp COMMA Args				{$$=mknode(ARGS,$1,$3,NULL,yylineno);}	//abc(1+2,a*c)  实参个数可为任意
		| Exp						{$$=$1;}//只有一个参数，也把上面的Args最终推成exp
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