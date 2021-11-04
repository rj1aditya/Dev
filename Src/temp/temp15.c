#include<stdio.h>

void fun( int *x )
{
    *x = 100;
}

void func( char *x )
{
    x[1] = 'a';
}

int main()
{
    int x = 10;
    char c[2] = {'x'};
    fun(&x);
    func(c);
    printf("%d", x);
    printf("\n%c", c[1]);
}