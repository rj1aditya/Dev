
%{
#include<stdio.h>
int yylex();
void yyerror(const char *s);
%}

%token BOOLEAN
%token OR
%token AND
%token NOT

%left OR
%left AND

%%

prog:
    prog stmt
|
;

stmt:
    expr ';' {fprintf(stderr, "Expr value is %d\n", $1);}
;

expr:
    BOOLEAN {$$ = $1;}
| expr AND expr { $$ = $1 && $3; }
| expr OR expr  { $$ = $1 || $3; }
| NOT expr 	{ $$ = ($2 == 0); }
| '(' expr ')'  { $$ = $2; }
;

%%


void yyerror ( const char *s )
{
printf("%s\n", s);
}

