#include<iostream>
using namespace std;

class Final;

class Makefinal
{
	private:
	Makefinal()
	{cout<<"Make final conns"<<endl;}
	~Makefinal()
	{cout<<"Make final destroy"<<endl;}
	friend class Final;
};

class Final: virtual Makefinal
{
	public:
	Final()
	{
		cout<<"Final class Constructor"<<endl;
	}
	
	~Final()
	{
		cout<<"Des of Final"<<endl;
	}
};

class D: public Final
{
	public:
	D()
	{}
};

int main()
{
	Final obj;
}

