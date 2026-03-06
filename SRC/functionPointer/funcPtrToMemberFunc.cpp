#include<stdio.h>

struct X
{
    int val;
    void double_int()
    {
        val = 2*val;
    }
};

typedef void (X::*fptr)();

void transform(X &obj, fptr fu)
{
    (obj.*fu)();
}

int main()
{
    X obj{2};
    //obj.double_int();
    transform(obj, &X::double_int);
    printf("[%d]",obj.val);
}