#include"reqh.h"

class Base
{
    public:

    void f()
    {
        cout<<"Base class F()"<<endl;
    }

    void f(const string s)
    {
        cout<<"Base class f string fun "<<s<<endl;
    }
};


class D1: public Base
{
    public:
    void f()
    {
        cout<<"D1 class f()\n";
    }
};

class D2: public Base
{
    public:
    int f()
    {
        cout<<"D2 class f()\n";
        return 0;
    }

    int f(int x)
    {
        cout<<"D2 class f int x fun"<<endl;
        return 0;
    }
};

int main()
{
    D1 obj;
    obj.f();
    obj.Base::f();
    string s = "hello";
    obj.Base::f(s);


    D2 obj1;
    obj1.f();
    obj1.f(10);
    obj1.Base::f();
    obj1.Base::f("ehlo");
}