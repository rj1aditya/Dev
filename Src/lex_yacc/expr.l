
%{
#include<stdio.h>
#include"expr.tab.h"
%}

%%

[ \t\n] {}
AND {return AND;}
OR  {return OR;}
NOT {return NOT;}

0 {yylval=0; return BOOLEAN;}
1 {yylval=1; return BOOLEAN;}

[;()] {return *yytext;}
. { fprintf(stderr, "Unknow character %s\n", yytext); }

%%
