#include"reqh.h"

class a
{
    public:
    a(){
        cout<<"Hellow"<<endl;
    }
};

class b: public a
{
    public:
    b(int x){cout<<"Bye";}
};

int main()
{
    b obj(10);
}