%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
#include "stdio.h"
int yycolumn=1;
#define YY_USER_ACTION yylloc.first_line=yylloc.last_line=yylineno; yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union{
    int type_int;
    int type_float;
    int type_char;
    char type_id[32];
    struct node *pr;
}YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

id [A-Za-z][A-Za-z0-9]*
int [0-9]+
float ([0-9]*\.[0-9]+)|([0-9]+\.)
char \'.\'

%%
{int}       {yylval.type_int=atoi(yytext);return INT;}
{float}     {yylval.type_float=atof(yytext);return FLOAT;}
{char}      {yylval.type_char=yytext[1];return CHAR;}
"int"       {strcpy(yylval.type_id, yytext);return TYPE;}
"float"     {strcpy(yylval.type_id, yytext);return TYPE;}
"char"      {strcpy(yylval.type_id, yytext);return TYPE;}

"return"    {return RETURN;}
"if"        {return IF;}
"else"      {return ELSE;}
"while"     {return WHILE;}

{id}        {strcpy(yylval.type_id, yytext);return ID;}//由于关键词的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面
";"         {return SEMI;}
","         {return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);return RELOP;}
"="         {return ASSIGNOP;}
"++"        {return INC;}
"+="        {return COMP_PLUS;}
"+"         {return PLUS;}
"--"        {return DEC;}
"-="        {return COMP_MINUS;}
"-"         {return MINUS;}
"*"         {return STAR;}
"/"         {return DIV;}
"&&"        {return AND;}
"||"        {return OR;}
"!"         {return NOT;}
"("         {return LP;}
")"         {return RP;}
"["         {return LB;}
"]"         {return RB;}
"{"         {return LC;}
"}"         {return RC;}
[\n]        {yycolumn=1;}//每到新的一行列数置1
[ \r\t]     {}
(\/\/).*    {}//匹配注释//
.           {printf("ERROR:未定义的字符 %s at line %d colemn %d\n",yytext,yylineno,yycolumn);}
%%

/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}
*/

int yywrap()
{
return 1;
}

