#include"reqh.h"

class Base
{
    
    protected:
    int i;
    void setData()
    {
        i = 50;
    }
};

class Drive: public Base
{
    public:
    void setData()
    {
        i = 100;
    }
    void showData()
    {
        cout<<i;
    }
};

int main()
{    
    Drive obj;
    obj.setData();
    obj.showData();
}