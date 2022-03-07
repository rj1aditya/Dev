#include<iostream>
#include<memory>
#include<string>
using namespace std;

class X
{
	public:
	int count;
	X()
	{
		count=0;
	}
    void set(int x)
    {
        count = x;
    }

	~X()
	{
		
		cout<<count<<" detructor called"<<endl;
		count--;
	}
};
		
int main()
{
	unique_ptr<X[]> ptr(new X[10]); // A way to declare Array using unique_ptr
    for(int i = 0; i < 10; i++)
        ptr[i].set(i);
    
    for(int i = 0; i < 10; i++)
        cout<<ptr[i].count;
    
    unique_ptr<X> p(new X);
    p->set(101);

    cout<<endl<<"                                       "<<p->count<<endl;
}