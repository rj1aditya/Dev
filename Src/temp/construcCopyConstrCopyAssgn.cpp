#include<iostream>
using namespace std;

class A
{
	public:
	A()
	{
		cout<<"Contructor Called\n";
	}

	A( A& obj )
	{
		cout<<"Copy Constructor called\n";
	}

	A& operator=( A& obj )
	{
		cout<<"Copy Assignment operator called\n";
		return *this;
	}

};

int main()
{
	A obj;
	A obj1 = obj;

	A obj2;

	obj2 = obj;
	return 0;
}
