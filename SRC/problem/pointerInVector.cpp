#include<bits/stdc++.h>
using namespace std;

class A
{
    static int x;
    public:

    A()
    {
        x++;
    }
    
    void show()
    {
        cout<<x<<" ";
    }
    ~A()
    {
        cout<<x<<" ";
        cout<<"Destr"<<" ";
    }

};

int A::x = 0;
 

int main()
{
    vector<A*> v;

    for(int i = 0; i <100; i++)
    {
        A *ptr{new A()};

        v.push_back(ptr);
    }

    for(int i = 0; i < v.size(); i++)
    {
        v[i]->show();
        
    }

    for(int i = 0; i < v.size(); i++)
    {
        delete v[i];
    }

}