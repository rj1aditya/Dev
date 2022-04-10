#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<algorithm>
#include<mutex>
using namespace std;

class PhoneP
{
	int bal;
	mutex mu;
	public:
	PhoneP( int add_money = 0 ): bal(add_money)
	{
	}
	
	int show_bal()
	{
		return bal;
	}
	
	PhoneP( const PhoneP &obj )
	{
	}
	
	void add_money( int m )
	{
		lock_guard<mutex> lg(mu);
		
		//mu.lock();
		while( m != 0 )
		{
			bal++;
			m--;
		}
		//mu.unlock();
	}
	
};

void testAddMoney()
{
	vector<thread> vtd;
	PhoneP obj;
	for( int i = 0; i < 5; i++ )
	{
		vtd.push_back( std::thread( &PhoneP::add_money, &obj, 10000 ) );
	}
	for_each( vtd.begin(), vtd.end(), std::mem_fn( &thread::join ) );
	int b = obj.show_bal();
	cout<<"cur bal is: "<<b;
}

int main()
{
	testAddMoney();
}
	
	
	