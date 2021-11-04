#include"reqh.h"

class WCC
{
    public:
    WCC()
    {
        cout<<"Constr of WCC class\n";
    }

    WCC(const WCC &obj)
    {
        cout<<"Copy Constr of WCC class";
    }
};

class WOCC
{
    string id;
    public:
    WOCC(string s=""):id(s)
    {
        cout<<"Constr of WOCC class\n";
    }
};

class Composite
{
    WCC obj1;
    WOCC obj2;
    public:
    Composite(): obj2("composite()")
    {
        cout<<"Constr of Composite class\n";
    }
};

int main()
{
    Composite obj;
}