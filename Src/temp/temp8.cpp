#include<iostream>
using namespace std;

class A
{
	int i;
	public:
	A(int ii):i(ii)
	{
		cout<<"Contructor Called\n";
	}

	A( const A& obj )
	{
		cout<<"Copy Constructor called\n";
	}

	A& operator=( const A& obj )
	{
		cout<<"Copy Assignment operator called\n";
		return *this;
	}

	void modify()
	{
		i++;		
	}

};

A F5()
{
	return A(10);
}

const A F6()
{
	return A(20);
}

void F7( A &a )
{
	a.modify();
}

int main()
{
	F5() = A(1);

	//F5().modify();
	return 0;
}
