#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<algorithm>
#include<mutex>
#include<condition_variable>
using namespace std;
class A
{
	mutex mu;
	condition_variable c;
	bool sig;
	public:
	A()
	{
		sig = false;
		//cout<<"Constru"<<endl;
	}
	
	void load_xml()
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout<<"Loading XML...."<<endl;
		lock_guard<mutex> lg(mu);
		sig = true;
		c.notify_one();
	}
	
	void load_main()
	{
		std::unique_lock<std::mutex> mlock(mu);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout<<"Handshake with network 1000/1001"<<endl;
		//c.wait( mu, bind(&A::sig_e, this) );
		c.wait(mlock, std::bind(&A::sig_e, this));
		cout<<"Now further procedure.."<<endl;
	}
	
	bool sig_e()
	{
		return sig;
	}
};

int main()
{
	A obj;
	thread td1(&A::load_xml,&obj);
	thread td2(&A::load_main,&obj);
	td1.join();
	td2.join();
}