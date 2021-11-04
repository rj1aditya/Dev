#include"reqh.h"


int x = 10;

class A
{
    static int  x;
    static int  y;
    public:
    A()
    {
        cout<<x<<endl<<y;
    }
};

int A::x = 1;
int A::y = ::x+1;

int main()
{
    A obj;
}