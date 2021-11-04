#include<iostream>
using namespace std;
class A
{
	public:
		A()
		{
			cout<<"Construcn"<<endl;
		}
};

int main()
{
	int x =10;

	if( x >= 10 )
		goto jump1;
	A obj1;
jump1:
	switch(x)
	{
		case 10:
			A obj2;
			break;
		case 11:
			A obj3;
			break;
	}
	return 0;
}
