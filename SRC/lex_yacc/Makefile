bin-expr: expr.c expr.tab.c
	gcc expr.c expr.tab.c -ll

expr.c: expr.l expr.tab.h
	flex -t expr.l > expr.c

expr.tab.h expr.tab.c: expr.y
	bison -d expr.y
