%{
#include<bits/stdc++.h>
#include "classes.h"
#include "parser.tab.h"
using namespace std;
extern union Node yylval;
int lineno = 0;
%}

digit [0-9]
hex_digit {digit}|[a-fA-F]
char [ -~]
character \'{char}\'
string (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])

%%
"class Program"            {return PROGRAM;}
"void"                     {yylval.identifier = strdup(yytext); return VOID;}
"return"                   {return RETURN;}
"int"                      {yylval.identifier = strdup(yytext); return TYPE;}
"boolean"                  {yylval.identifier = strdup(yytext); return TYPE;}
"callout"                  {return CALLOUT;}

"if"                       {return IF;}
"else"                     {return ELSE;}
"for"                      {return FOR;}
"break"                    {return BREAK;}
"continue"                 {return CONTINUE;}
"true"                     {yylval.identifier = strdup(yytext); return BOOL;}
"false"                    {yylval.identifier = strdup(yytext); return BOOL;}

"="                        {yylval.identifier = strdup(yytext); return EQ;}
"+="                       {yylval.identifier = strdup(yytext); return PLUSEQ;}
"-="                       {yylval.identifier = strdup(yytext); return MINUSEQ;}
"+"					               {yylval.identifier = strdup(yytext); return ADD;}
"-"					               {yylval.identifier = strdup(yytext); return SUB;}
"*"					               {yylval.identifier = strdup(yytext); return MUL;}
"/"					               {yylval.identifier = strdup(yytext); return DIV;}
"%"                        {yylval.identifier = strdup(yytext); return MOD;}
"!"                        {yylval.identifier = strdup(yytext); return NOT;}

"=="                       {yylval.identifier = strdup(yytext); return DOUBEQ;}
"!="                       {yylval.identifier = strdup(yytext); return NOTEQ;}
"&&"                       {yylval.identifier = strdup(yytext); return AND;}
"||"                       {yylval.identifier = strdup(yytext); return OR;}
"<="                       {yylval.identifier = strdup(yytext); return LE;}
"<"                        {yylval.identifier = strdup(yytext); return LT;}
">="                       {yylval.identifier = strdup(yytext); return GE;}
">"                        {yylval.identifier = strdup(yytext); return GT;}


"("					               {return OTB;}
")"					               {return CTB;}
"{"                        {return OFB;}
"}"                        {return CFB;}
"["                        {return OSB;}
"]"                        {return CSB;}
","                        {return COMMA;}
";"                        {return SEMICOL;}

[a-zA-Z][a-zA-Z0-9]*	     {yylval.identifier = strdup(yytext); return ID;}
"0x"{hex_digit}+|{digit}+  {yylval.value = atoi(yytext);  return INTEGER;}
{character}                {yylval.identifier = strdup(yytext); return CHAR;}
\"{string}*\"              {yylval.identifier = strdup(yytext); return STRING;}
[ \t]+				             { }
\n		     		             {++lineno;}
.					                 { printf("Line No %d: Unrecognized Character %s\n", lineno,yytext); }

%%
