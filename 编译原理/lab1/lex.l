%{
#include "exp.tab.h"
#include "string.h"
#include "def.h"
#include "stdio.h"
int yycolumn=1;
typedef union {
    int type_int;
    float type_float;
    char type_id[32];
    char type_char[4];
    struct node *ptr;
}YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

id [A-Za-z][A-Za-z0-9]*
int [0-9]+
float [+-]?([0-9]+\.)|([0-9]*\.[0-9]+)
char \'.\'

%%
{int}       {yylval.type_int = atoi(yytext); return INT;}
{float}     {yylval.type_float = atof(yytext); return FLOAT;}
{char}      {strcpy(yylval.type_char, yytext); return CHAR;}
"int"       {strcpy(yylval.type_id, yytext); return TYPE;}
"float"     {strcpy(yylval.type_id, yytext); return TYPE;}
"char"      {strcpy(yylval.type_id, yytext); return TYPE;}
"return"    {return RETURN;}
"if"        {return IF;}
"else"      {return ELSE;}
"while"     {return WHILE;}

{id}        {strcpy(yylval.type_id, yytext); return ID;}
";"         {return SEMI;}
","         {return COMMA;}
"++"        {strcpy(yylval.type_id, yytext);return AUTOINC;}
"--"        {strcpy(yylval.type_id, yytext);return AUTODEC;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);return RELOP;}
"="|"+="|"*="|"-="|"/="    {strcpy(yylval.type_id, yytext);return ASSIGNOP;}
"+"         {return PLUS;}
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
[\n]        {yycolumn = 1;}//每到新的一行列数置1
[ \r\t]     {}
(\/\/).*    {}//匹配注释
.           {printf("ERROR:未定义的字符 %s at line %d colemn %d\n",yytext,yylineno,yycolumn);}

%%
/*
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