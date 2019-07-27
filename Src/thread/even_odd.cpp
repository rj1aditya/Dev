#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

using namespace std;

condition_variable c;
mutex m;
int count = 1;

void printOdd()
{
	for( ; count < 100; )
	{
		unique_lock<mutex> ul(m);
		c.wait( ul, [](){ return count%2==1; } );
		cout<<"From odd: "<<count<<endl;
		count++;
		ul.unlock();
		c.notify_all();
	}
}

void printEven()
{
	for( ; count < 100; )
	{
		unique_lock<mutex> ul(m);
		c.wait( ul, [](){ return count%2==0; } );
		cout<<"From even: "<<count<<endl;
		count++;
		ul.unlock();
		c.notify_all();
	}
}

int main()
{
	thread t1( printOdd );
	thread t2( printEven );
	t1.join();
	t2.join();
}