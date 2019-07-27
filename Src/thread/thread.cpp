#include<iostream>
#include<thread>
using namespace std;

class T
{
	public:
	T()
	{
		cout<<"Constr called"<<endl;
	}
	// it is must if you want to call class function as a call back using thread.
	void operator()(int i)
	{
		cout<<"operator here>>>>>>>>>>>>>>>>>"<<10<<"<<<<<<<<<<<<<<<<<<"<<endl;
		fuc();
	}
	void fuc()
	{
		int i = 0;
		while(i < 1000000 )
		{
			i++;
			cout<<i<<". congress voting counter"<<endl;
		}
	}

	
};

void func()
{
	int i=0;
	while( i < 1000000 ){
	i++;
	cout<<i<<". bjp voitng counter"<<endl;}
}

int main()
{
	T obj;
	thread td((T()),10);
	cout<<"thread id is: "<< td.get_id();
	func();
	td.join();
}
