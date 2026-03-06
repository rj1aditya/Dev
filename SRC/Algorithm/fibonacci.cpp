#include<iostream>
using namespace std;


int fib(int x)
{
    if(x ==0)
        return x;
    else if(x==1)
        return x;
    else
        return (fib(x-1)+fib(x-2));
}
void fibonacci(int x)
{
    for(int i = 0; i < x; i++)
        cout<<fib(i)<<" ";
}

int main()
{
    fibonacci(10);
}