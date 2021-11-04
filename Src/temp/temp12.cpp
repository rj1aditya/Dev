#include<iostream>
using namespace std;

class Member
{
    int x,y,z;

    public:

    Member(int i=0): x(i), y(i), z(i) 
    {
        cout<<"Member"<<endl;
    }
};

class WithMember
{
    Member obj1, obj2, obj3;
    int x;

    public:
    WithMember(int ii): x(ii)
    {
        cout<<"With Member"<<endl;
    }
};


int main()
{
    WithMember w(10);
}