%{
#include "classes.h"
#include<bits/stdc++.h>
extern FILE *yyin;
int yylex (void);
class Program* start = NULL;
class Visitor *vis = new Traverse();
void yyerror (char const *s);
extern union Node yylval;
extern int errors;
%}
%start program

%token<identifier> TYPE
%token<identifier> VOID
%token<identifier> ID
%token<identifier> BOOL CHAR STRING
%token<identifier> EQ PLUSEQ MINUSEQ
%token<value> INTEGER

%token PROGRAM COMMA SEMICOL CALLOUT RETURN
%token OTB CTB OSB CSB OFB CFB
%token IF ELSE FOR BREAK CONTINUE


%token<identifier> DOUBEQ NOTEQ
%token<identifier> AND OR
%token<identifier> LT GT LE GE
%token<identifier> ADD SUB
%token<identifier> MUL DIV MOD
%token<identifier> NOT


%left DOUBEQ NOTEQ
%left AND OR
%left LT GT LE GE
%left ADD SUB
%left MUL DIV MOD
%left NOT

%type<program> program
%type<field_decls> field_declarations
%type<field_decl> field_declaration
%type<out_decls> out_declarations
%type<method_decls> method_declarations
%type<method_decl> method_declaration
%type<method_args> method_args
%type<block> block
%type<var_decls> var_declarations
%type<var_decl> var_declaration
%type<statements> statements
%type<statement> statement
%type<assign_op> assign_op
%type<location> location
%type<expression> expr
%type<literal> literal
%type<methodcall> method_call
%type<expressions> expressions
%type<calloutargs> callout_args
%type<calloutarg> callout_arg
%%

program : PROGRAM OFB field_declarations method_declarations CFB {$$ = new Program($3,$4);start=$$;errors=0;}

field_declarations :{$$ = new Field_decls();}
										|field_declarations field_declaration SEMICOL {$$->push($2);}

field_declaration  : TYPE out_declarations {$$ = new Field_decl($1,$2);}


out_declarations :    ID {$$ = new Out_decls();$$->push($1);}
										| out_declarations COMMA ID {$$->push($3);}
										| ID OSB INTEGER CSB {$$ = new Out_decls();$$->push($1,$3);}
										| out_declarations COMMA ID OSB INTEGER CSB {$$->push($3,$5);}

method_declarations: {$$ = new Method_decls();}
									| method_declaration method_declarations { $2->push($1); $$ = $2;}
method_declaration : TYPE ID OTB CTB block {$$ = new Method_decl($1,$2,$5);}
										 | VOID ID OTB CTB block {$$ = new Method_decl($1,$2,$5);}
 										 | TYPE ID OTB method_args CTB block {$$ = new Method_decl($1,$2,$4,$6);}
										 | VOID ID OTB method_args CTB block {$$ = new Method_decl($1,$2,$4,$6);}
method_args : TYPE ID {$$ = new Method_args(); $$->push($1,$2);}
						 | method_args COMMA TYPE ID {$$->push($3,$4);}

block :  OFB var_declarations statements CFB { $$ = new Block($2,$3);}
var_declarations :{$$ = new Var_declarations();}
									| var_declarations var_declaration SEMICOL { $$->push($2);}
var_declaration :  TYPE ID {$$ = new Var_declaration($1);$$->push($2);}
									| var_declaration COMMA ID { $$->push($3);}

statements : {$$ = new Statements();}| statements statement {$$->push($2);}
statement : location assign_op expr SEMICOL {$$ = new Assignment($1,$2,$3);}
						| method_call SEMICOL {$$ = $1;}
						| IF OTB expr CTB block ELSE block {$$ = new Ifelsestatement($3,$5,$7);}
						| IF OTB expr CTB block {$$ = new Ifelsestatement($3,$5,NULL);}
						| FOR ID EQ expr COMMA expr block {$$ = new Forstatement($2,$4,$6,$7);}
						| RETURN SEMICOL {$$ = new Returnstatement(NULL);}
						| RETURN expr SEMICOL {$$ = new Returnstatement($2);}
						| BREAK SEMICOL {$$ = new Breakstatement();}
						| CONTINUE SEMICOL {$$ = new Continuestatement();}
						| block {$$ = $1;}

assign_op : EQ {$$ = new Assign_op($1);}
						| PLUSEQ {$$ = new Assign_op($1);}
						| MINUSEQ {$$ = new Assign_op($1);}
method_call : ID OTB CTB {$$ = new Expressionscall($1,NULL);}
						 | ID OTB expressions CTB {$$ = new Expressionscall($1,$3);}
						 | CALLOUT OTB STRING CTB {$$ = new Calloutcall($3,NULL);}
						 | CALLOUT OTB STRING COMMA callout_args CTB {$$ = new Calloutcall($3,$5);}

callout_args : callout_arg {$$ = new Calloutargs();$$->push($1);}
							| callout_args COMMA callout_arg {$$->push($3);}
location : ID {$$ = new Location($1);}
  				| ID OSB expr CSB {$$ = new Location($1,$3);}

expressions : expr {$$ = new Expressions();$$->push($1);}
             | expressions COMMA expr {$$->push($3);}
expr : location {$$ = $1;}
			| method_call {$$ = $1;}
			| literal {$$ = $1;}
			| expr ADD expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr SUB expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr MUL expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr DIV expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr MOD expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr LT expr  {$$ = new BinaryExpression($1,$2,$3);}
			| expr GT expr  {$$ = new BinaryExpression($1,$2,$3);}
			| expr LE expr  {$$ = new BinaryExpression($1,$2,$3);}
			| expr GE expr  {$$ = new BinaryExpression($1,$2,$3);}
			| expr DOUBEQ expr {$$ = new BinaryExpression($1,$2,$3);}
			| expr NOTEQ expr  {$$ = new BinaryExpression($1,$2,$3);}
			| expr AND expr    {$$ = new BinaryExpression($1,$2,$3);}
			| expr OR expr     {$$ = new BinaryExpression($1,$2,$3);}
			| SUB expr        {$$ = new UnaryExpression($1,$2);}
			| NOT expr				{$$ = new UnaryExpression($1,$2);}
			| OTB expr CTB    {$$ = $2;}

callout_arg : expr {$$ = new Calloutarg($1);}
						| STRING {$$ = new Calloutarg($1);}

literal : INTEGER { $$ = new Literal(0,$1);}
					| CHAR  { $$ = new Literal(1,$1);}
					| BOOL  { $$ = new Literal(2,$1);}

%%
#include "lex.yy.c"
int main(int argc, char **argv)
{
	yyparse();
	if(errors==0)
	printf("Parsing Over\n");
 if(start)
 {
	 start->accept(vis);
	 cout<<"Semantic Checking done\n";
 }
}

void yyerror(const char *s)
{
	fprintf(stderr, "error: %s\n", s);
}
