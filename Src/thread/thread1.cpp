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


	void fuc(int i)
	{

		while(i < 20 )
		{
			i++;
			cout<<i<<". congress voting counter"<<endl;
		}
	}

	
};


int main()
{
	T obj;
	thread td(&T::fuc,obj, 10);
	
	td.join();
}