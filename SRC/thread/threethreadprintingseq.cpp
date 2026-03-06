#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

using namespace std;

condition_variable c;
mutex m;
int count = 1;
int flag = 0;

bool thread1()
{
    return flag == 0;
}
bool thread2()
{
    return flag == 1;
}
bool thread3()
{
    return flag == 2;
}


void print1()
{
    while(count < 10 )
    {
        unique_lock<mutex> ul(m);
        c.wait(ul, thread1);
        cout<<count<<endl;
        count++;
        flag = 1;
        c.notify_all();
    }
}


void print2()
{
    while(count < 10 )
    {
        unique_lock<mutex> ul(m);
        c.wait(ul, thread2);
        cout<<count<<endl;
        count++;
        flag = 2;
        c.notify_all();
    }
}


void print3()
{
    while(count < 10 )
    {
        unique_lock<mutex> ul(m);
        c.wait(ul, thread3);
        cout<<count<<endl;
        count++;
        flag = 0;
        c.notify_all();
    }
}


int main()
{
	thread t1( print1 );
	thread t2( print2 );
    thread t3( print3 );
	t1.join();
	t2.join();
    t3.join();
}