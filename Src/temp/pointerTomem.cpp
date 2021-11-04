#include"reqh.h"

class D
{
    public:
    int a;

    void print()
    {
        cout<<a<<endl;
    }
};


int main()
{
    D d;
    D *dp = &d;

    int D::*pointer = &D::a;

    dp->a = 50;
    // dp->*pointer = 48;
    d.print();
    dp->print();
}