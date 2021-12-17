#include<iostream>
using namespace std;

class A
{
    public:
    static int objCount;
    A()
    {
        
        objCount++;
        cout<<objCount<<": A constr\n";
    }
    A(const A &obj)
    {
        
        objCount++;
        cout<<objCount<<": A Copy constr\n";
    }
    ~A()
    {
        objCount--;
        cout<<objCount<<": A Destr\n";
    }
};
int A::objCount=0;

A fun(A obj)
{
    return obj;
}

int main()
{
    A obj;
    A obj1 = fun(obj);
    return 0;
}