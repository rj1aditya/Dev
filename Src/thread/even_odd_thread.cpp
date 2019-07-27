#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>

using namespace std;

int count = 1;
condition_variable c;
mutex m;

void printNum( bool sig )
{
	if( sig )
	{
		while( count < 100 )
		{
			unique_lock<mutex> ulock(m);
			c.wait( ulock, [](){return count%2;});
			cout<<this_thread::get_id()<<" "<<count<<endl;
			count++;
			ulock.unlock();
			c.notify_all();
		}
	}
	else
	{
		while( count <= 100 )
		{
			unique_lock<mutex> ulock(m);
			c.wait( ulock, [](){return !(count%2);});
			cout<<this_thread::get_id()<<" "<<count<<endl;
			count++;
			ulock.unlock();
			c.notify_all();
		}
	}
}

int main()
{
	thread even_thread( printNum, 0 );
	thread odd_thread( printNum, 1 );
	
	even_thread.join();
	odd_thread.join();
}