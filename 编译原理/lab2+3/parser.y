%error-verbose
%locations
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);//可变长参数
void display(struct node *,int);
%}

%union{
    int type_int;
    float type_float;
    char type_char;
    char type_id[32];
    struct node *ptr;
};

//%type定义非终结符的语义值类型(对应union中成员ptr的类型，本实验中为一个树节点的指针)
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

%token <type_int> INT//指定INT的语义值是type_int,由词法分析得到的数值
%token <type_id> ID RELOP TYPE//指定ID、RELOP、TYPE的语义值是type_id,由词法分析得到的标识符字符
%token <type_float> FLOAT//指定FLOAT的语义是type_id,由词法分析得到的标识符字符串
%token <type_char> CHAR

//括号
%token LP RP LB RB LC RC 
//分隔符
%token SEMI COMMA

//运算符
%token PLUS MINUS STAR DIV ASSIGNOP AND OR NOT 
//关键字
%token IF ELSE WHILE RETURN 
//特殊运算符
%token INC DEC COMP_PLUS COMP_MINUS

/*指定优先级*/
%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left COMP_PLUS COMP_MINUS
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT INC DEC

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

//程序
program: ExtDefList {display($1,0);semantic_Analysis0($1);prnIR($1->code);}
        ;
		
//外部变量定义列表
ExtDefList: {$$=NULL;}
        |ExtDef ExtDefList {$$=mknode(EXT_DEF_LIST,$1,$2,NULL,yylineno);}							//形如int a;int b;int c;
        ;

//一个全局变量定义|一个函数定义|一个结构体定义
ExtDef: Specifier ExtDecList SEMI {$$=mknode(EXT_VAR_DEF,$1,$2,NULL,yylineno);}						//形如int a,b;
        |Specifier FuncDec CompSt {$$=mknode(FUNC_DEF,$1,$2,$3,yylineno);}							//形如int fun() {}
        |error SEMI               {$$=NULL;}
        ;

//类型描述符
Specifier: TYPE {$$=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);
        if(!strcmp($1,"int")) $$->type=INT;
        if(!strcmp($1,"float")) $$->type=FLOAT;
        if(!strcmp($1,"char")) $$->type=CHAR;}
        ;

//0个或多个变量，如a,b,c    (int a,b,c;)
//每一个EXT_DEFLIST的结点，其第一棵子树对应一个变量名(ID类型的结点)，第二棵子树对应剩下的外部变量名
ExtDecList: VarDec {$$=$1;}
        | VarDec COMMA ExtDecList {$$=mknode(EXT_DEC_LIST,$1,$3,NULL,yylineno);}
        ;
		
//标识符，标识符符号串存放节点的type_id
VarDec: ID {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
        | VarDec LB INT RB {$$=mknode(ARRAY_DEF,$1,NULL,NULL,yylineno);$$->array_size[0]=$3;}//一维数组
		;
		
//函数头
FuncDec: ID LP VarList RP {$$=mknode(FUNC_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
        |ID LP RP         {$$=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
        ;  
		
//形参列表
VarList: ParamDec                {$$=mknode(PARAM_LIST,$1,NULL,NULL,yylineno);}
        | ParamDec COMMA VarList {$$=mknode(PARAM_LIST,$1,$3,NULL,yylineno);}
        ;
		
//一个形参的定义
ParamDec: Specifier VarDec {$$=mknode(PARAM_DEC,$1,$2,NULL,yylineno);}
        ;
		
//函数体
CompSt: LC DefList StmList RC {$$=mknode(COMP_STM,$2,$3,NULL,yylineno);}
        ;
		
//语句列表
StmList: {$$=NULL;}  
        | Stmt StmList {$$=mknode(STM_LIST,$1,$2,NULL,yylineno);}
        ;
		
//一条语句
Stmt: Exp SEMI                        {$$=mknode(EXP_STMT,$1,NULL,NULL,yylineno);}
        | CompSt                      {$$=$1;}//复合语句结点直接最为语句结点，不再生成新的结点
        | RETURN Exp SEMI             {$$=mknode(RETURN,$2,NULL,NULL,yylineno);}
        | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE {$$=mknode(IF_THEN,$3,$5,NULL,yylineno);}
        | IF LP Exp RP Stmt ELSE Stmt {$$=mknode(IF_THEN_ELSE,$3,$5,$7,yylineno);}
        | WHILE LP Exp RP Stmt        {$$=mknode(WHILE,$3,$5,NULL,yylineno);}
        ;
		
//局部变量定义列表
DefList: {$$=NULL;}
        | Def DefList {$$=mknode(DEF_LIST,$1,$2,NULL,yylineno);}
        ;
		
//一个局部变量定义
Def: Specifier DecList SEMI {$$=mknode(VAR_DEF,$1,$2,NULL,yylineno);}
        ;
		
//0个或多个局部变量，形如a,b,c
DecList: Dec                {$$=mknode(DEC_LIST,$1,NULL,NULL,yylineno);}
        | Dec COMMA DecList {$$=mknode(DEC_LIST,$1,$3,NULL,yylineno);}
        ;
		
//一个局部变量，形如a
Dec: VarDec {$$=$1;}
        | VarDec ASSIGNOP Exp {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"ASSIGNOP");}
        ;
		
//一个表达式
Exp: Exp ASSIGNOP Exp   {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
        | Exp AND Exp   {$$=mknode(AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"AND");}
        | Exp OR Exp    {$$=mknode(OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"OR");}
        | Exp RELOP Exp {$$=mknode(RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
        | Exp PLUS Exp  {$$=mknode(PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"PLUS");}
        | Exp MINUS Exp {$$=mknode(MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"MINUS");}
        | Exp STAR Exp  {$$=mknode(STAR,$1,$3,NULL,yylineno);strcpy($$->type_id,"STAR");}
        | Exp DIV Exp   {$$=mknode(DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"DIV");}
        | LP Exp RP     {$$=$2;}
        | MINUS Exp %prec UMINUS   {$$=mknode(UMINUS,$2,NULL,NULL,yylineno);strcpy($$->type_id,"UMINUS");}
        | Exp COMP_PLUS Exp        {$$=mknode(COMP_PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"COMP_PLUS");}
        | Exp COMP_MINUS Exp        {$$=mknode(COMP_MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"COMP_MINUS");}
        | Exp INC       {$$=mknode(INC,$1,NULL,NULL,yylineno);strcpy($$->type_id,"POST_INC");}
        | Exp DEC       {$$=mknode(DEC,$1,NULL,NULL,yylineno);strcpy($$->type_id,"POST_DEC");}
        | INC Exp       {$$=mknode(INC,$2,NULL,NULL,yylineno);strcpy($$->type_id,"PRE_INC");}
        | DEC Exp       {$$=mknode(DEC,$2,NULL,NULL,yylineno);strcpy($$->type_id,"PRE_DEC");}
        | NOT Exp       {$$=mknode(NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"NOT");}
        | ID LP Args RP {$$=mknode(FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
        | ID LP RP      {$$=mknode(FUNC_CALL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
        | VarDec LB INT RB {$$=mknode(ARRAY_DEF,$1,NULL,NULL,yylineno);strcpy($$->type_id,"ARRAY_DEF");$$->array_size[0]=$3;}
		| ID            {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
        | INT           {$$=mknode(INT,NULL,NULL,NULL,yylineno);$$->type_int=$1;$$->type=INT;}
        | FLOAT         {$$=mknode(FLOAT,NULL,NULL,NULL,yylineno);$$->type_float=$1;$$->type=FLOAT;}
        | CHAR          {$$=mknode(CHAR,NULL,NULL,NULL,yylineno);$$->type_char=$1;$$->type=CHAR;}
        ;
		
//实参列表
Args: Exp COMMA Args    {$$=mknode(ARGS,$1,$3,NULL,yylineno);}
        | Exp           {$$=mknode(ARGS,$1,NULL,NULL,yylineno);}
        ;
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 1;
	yylineno=1;
	yyparse();
	return 0;
}

#include <stdarg.h>
void yyerror(const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}	
