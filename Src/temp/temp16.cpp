#include"reqh.h"

class Staff
{
    int code;
    string name;
    public:
    Staff(){}
    void setterName(string n){name=n;}
    void getterName(){cout<<"Name: "<<name<<endl;}

    void setterId(int id){code=id;}
    void getterId(){cout<<"Id: "<< code<<endl;}

    void getter()
    {
        cout<<"Name: "<<name<<", Code: "<<code<<endl;
    }
};

class Typist: public Staff
{
    int speed;
    public:
    Typist(){}
    void setterSpeed(int s){speed=s;}
    void getter()
    {
        cout<<"speed: "<<speed<<endl;
    }
    void getterSpeed()
    {
        cout<<"speed: "<<speed<<endl;
    }
};

int main()
{
    Typist t;
    t.setterName("Ramesh");
    t.setterId(101);
    t.setterSpeed(79);
    t.getterName();
    t.getterId();
    t.getterSpeed();
    t.Staff::getter();
    t.getter();
    return 0;
}