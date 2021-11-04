#include<iostream>
using namespace std;

void fun()
{
	cout<<"fun"<<endl;
}

int main()
{
	fun();
	int i = 100;
	void *vp = &i;

	int *x=(int*)vp;
}
