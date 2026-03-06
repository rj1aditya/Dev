#include<iostream>
#include<string>
using namespace std;

class Base
{
	public:
	int f()
	{
		cout<<"Base::f()"<<endl;
		return 1;
	}
	
	int f( string s)
	{
		cout<<"Base::f(string)"<<endl;
		return 1;
	}
	
	void g()
	{
		cout<<"Base::g()"<<endl;
	}
};

class D1: public Base
{
	public:
	void g()
	{
		cout<<"D1::g()"<<endl;
	}
};

class D2: public Base
{
	public:
	int f()
	{
		cout<<"D2::f()"<<endl;
		return 1;
	}
};


class D3: public Base
{
	public:
	int f(int)
	{
		cout<<"D3::f(int)"<<endl;
		return 1;
	}
};

class D4: public Base
{
	public:
	void f()
	{
		cout<<"D4::f()"<<endl;
		//return 1;
	}
};

int main()
{
	string s("hello");
	D1 d1;
	//d1.f();
	d1.f();
	d1.g();
}