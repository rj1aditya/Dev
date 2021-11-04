#include<iostream>
using namespace std;

class X
{
    public:
    inline void fun();
};

inline void X::fun()
{
    cout<<"Inline function";
}

int main()
{
    X obj;
    obj.fun();
}