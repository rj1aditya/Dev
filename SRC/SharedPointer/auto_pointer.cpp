#include<iostream>
using namespace std;

template <class T>
class auto_ptr
{
	T *ptr;
	public:
	auto_ptr( T *p = 0 ): ptr(p)
	{
		cout<<"auto pointer const called"<<endl;
	}
	
	~auto_ptr()
	{
		cout<<"auto pointer destroy"<<endl;
	}
	
	T* operator->()
	{
		return ptr;
	}
	
	T& operator*()
	{
		return *ptr;
	}
};

class A
{
	public:
	A()
	{
		cout<<"A const"<<endl;
	}
	void f()
	{
		cout<<"F function of A class"<<endl;
	}
};

int main()
{
	auto_ptr<A> ptr( new A() );
	ptr->f();
}