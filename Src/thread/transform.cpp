#include<iostream>
#include<thread>
using namespace std;

class A
{
	public:
	int *ptr;
	A(int i)
	{
		ptr = new int[i];
		for( int i = 0; i < 5; i++ )
		{
			ptr[i] = i + 1;
		}
	}
		
	int square(int x)
	{
		return x*x;
	}
	
	int double_int(int x)
	{
		return 2*x;
	}
	
	~A()
	{
		delete []ptr;
	}
	
	void show()
	{
		cout<<"no are: "<<endl;
	for( int i = 0; i < 5; i++ )
	{
		cout<<ptr[i]<<" ";
	}
	}

};

void transform( A &obj, int (A::*tx)(int) )
{
	for( int i = 1; i < 6; i++ )
	{
		obj.ptr[i] = (obj.*tx)(obj.ptr[i]);
	}
	obj.show();
}

int main()
{
	A a(5);
	//thread a(transform,a,double_int);
	transform( a, &A::double_int );
}
	
	