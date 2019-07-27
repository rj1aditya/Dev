#include<iostream>
#include<memory>
#include<string>
using namespace std;

class X
{
	public:
	X()
	{
		count++;
	}
	static int count;

	~X()
	{
		
		cout<<count<<" detructor called"<<endl;
		count--;
	}
};

int X::count = 0;
		
int main()
{
	unique_ptr<X[]> ptr(new X[10]);
	X x;
	X();
}