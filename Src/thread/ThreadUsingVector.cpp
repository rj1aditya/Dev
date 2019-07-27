#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<algorithm>
using namespace std;

class Worker
{
	static int no;
	public:
	Worker()
	{
		no++;
		cout<<"Worker count is: "<<no<<endl;
	}
	void operator()(int x)
	{cout<<">>>>>>>>>>>>>>"<<x<<"<<<<<<<<<<<<<<<<"<<endl;}
};

int Worker::no = 0;

int main()
{
	vector<thread> vtd;
	
	for( int i =0; i < 5; i++ )
	{
		vtd.push_back( thread((Worker()),10) );
	}
	
	for_each( vtd.begin(), vtd.end(), std::mem_fn(&thread::join) );
}
		