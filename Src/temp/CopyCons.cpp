#include"reqh.h"

class howmany
{
    static int objCount;
    public:
    howmany()
    {
        objCount++;
    }
    howmany(const howmany &obj)
    {
        objCount++;
        cout<<"Copy constructor called: "<<objCount<<endl;
    }
    static void print(const string& msg)
    {
        cout<<msg<<": "<<endl;
        cout<<"Object count="<<objCount<<endl;
    }
    ~howmany()
    {
        objCount--;
        print("~howmany()");
    }
};

int howmany::objCount=0;

howmany f(howmany x)
{
    x.print("x argument inside f()");
    return x;
}

int main()
{
    howmany h; //1
    howmany::print("after construcotr of h");
    howmany h2=f(h); // 0
    howmany::print("after call to f()");
}

/*

*/