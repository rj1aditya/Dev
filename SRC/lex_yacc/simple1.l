

%%

[01]	{ printf("Bool value %d", atoi(yytext)); }
[0-9]+	{ printf("Number is %d, number of digits are %d\n", atoi(yytext), yyleng); }

%%
