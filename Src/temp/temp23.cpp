#include"reqh.h"
class Base
{
protected:
    int m_value{};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    virtual const char* getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }

    virtual const char* getName() const { return "Derived"; }
};

int main()
{
    Derived d1{5};
    Derived d2{6};

    Base &b{d2};

    cout<<b.getName();

    b = d1;


    int x = 15;

    int y = 25;

    int &re = x;

    cout<<re;

    re = y;
    cout<<re;

    int &c;
    return 0;
}