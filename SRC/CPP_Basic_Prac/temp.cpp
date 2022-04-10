#include<iostream>
using namespace std;

class A
{
	static int c;
	public:
		A()
		{
			c++;
			cout<<"Constructor called"<<endl;
		}
		/*A(A &obj )
		{
			c++;
			cout<<"Copy constructor called"<<endl;
		}*/
		void f()
		{
			cout<<"cal"<<endl;
		}
		~A()
		{
			cout<<"Object count is: "<< c;
		}
};

int A::c = 0;
A ff( )
{
	return A();
}
void g(A &obj)
{
}
int main()
{
	A obj;

	A obj1 = g(ff());
	obj1.f();
}
