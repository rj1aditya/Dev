#include"reqh.h"

class A
{
    public:

    int Fun()
    {
        cout<<"Int fun"<<endl;
        return 0;
    }

    char Fun()
    {
        cout<<"Char fun"<<endl;
        return 'z';
    }
};

int main()
{
    A obj;
}