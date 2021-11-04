#include"reqh.h"

class X
{
    int memVar;
    public:
    X(int x = 0): memVar(x)
    {
        cout<<"X Class Constructor\n";
    }
    ~X()
    {
        cout<<"X Class Destrucotr\n";
    }
};

void fun()
{
    static X obj1(10);
    static X obj2;
}


int main()
{
    cout<<"Hello World!!\n";
    fun();
    cout<<"Exiting from main Function\n";
}