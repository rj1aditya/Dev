#include<iostream>
using namespace std;

class A
{
	int i;
	public:
	A(int x):i(x){cout<<"cons"<<endl;}
	A( const A &obj ){cout<<"copy"<<endl;}
	void print(){cout<<i<<endl;}
};

class B{
	A a;
	public:
	B( A obj ): a(obj){}
};
int main()
{
	A a(10);
	B b(a);
}
