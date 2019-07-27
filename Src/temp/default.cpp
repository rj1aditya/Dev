#include<iostream>
using namespace std;


class A
{
	int i;
	public:
	A()
	{
		cout<<"Base class constru"<<endl;
		fun();
	}

	virtual void fun()
	{
		cout<<"base class func"<<endl;
	}
	virtual ~A()
	{
		cout<<"from drive class destruc"<<endl;
		fun();
	}

};

class B: public A
{
	public:
	B()
	{
		cout<<"drived class constr"<<endl;
		fun();
	}

	void fun()
	{
		cout<<"drived class func"<<endl;
	}
	~B()
	{
		cout<<"From drived class destr"<<endl;
		fun();
	}
};

int main()
{
	A *bobj = new B;
	delete bobj;
}
