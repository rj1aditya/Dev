#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<algorithm>
using namespace std;

class ThreadRail
{
	thread &tdRef;
	public:
	ThreadRail( thread &td ):tdRef(td)
	{
	}
	~ThreadRail()
	{
		if( tdRef.joinable() )
			tdRef.detach();
	}
};

void func()
{
	while(1)
		cout<<"round"<<" ";
}

int main()
{
	thread td( func );
	ThreadRail obj( td );
	while(1){}
}