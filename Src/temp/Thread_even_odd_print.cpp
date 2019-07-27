#include<iostream>
#include<thread>
#include<condition_variable>
#include<functional>

using namespace std;


condition_variable c_e;
condition_variable c_o;

mutex me;
mutex mo;

bool even = 0;
bool odd = 1;

bool check_even()
{
	return even;
}

bool check_odd()
{
	return odd;
}

void print_odd()
{
	static int i = 1;
	//cout<<"odd thread created"<<endl;
	while( i < 100 )
	{
		unique_lock< mutex > ulock( me );
		c_o.wait( ulock, bind( check_odd ));
		ulock.unlock();
		cout<<"thread 1:"  <<i <<" ";
		i++;
		i++;
		odd = 0;
		even = 1;
		c_e.notify_all();
		cout<<endl;
	}
}

void print_even()
{
	static int i = 2;
	//cout<<"even thread created"<<endl;
	
	while( i <= 100 )
	{
		unique_lock< mutex > ulock( mo );
		c_e.wait( ulock, bind( check_even ));
		ulock.unlock();
		cout<< "thread 2: "<< i <<" ";
		i++;
		i++;
		even = 0;
		odd = 1;
		c_o.notify_all();
	}
}

int main()
{
	thread t1( print_even );
	thread t2( print_odd );
	
	//cout<<"Thread created"<<endl;
	
	t1.join();
	t2.join();
}