#include<iostream>
using namespace std;

class A
{
	int i, j;
	public:
	A(int x, int y):i(x),j(y)
	{
	}

	friend int add(A obj);
};

int add(A obj)
{
	return obj.i+obj.j;
}


int main()
{
	A obj(10,20);
	cout<<add(obj);

	return 0;
}
