#include<iostream>
#include<memory>
using namespace std;

int main()
{
	unique_ptr<int> ptr(new int(7));

	cout<<*ptr;
}
