#include<iostream>
#include<cstdlib>
using namespace std;

int main( int argc, char *argv[] )
{
	int sum = 0;
	int a;
	for( int i = 1; i < argc; i++ )
	{
		a = atoi(argv[i]);
		sum += a;
	}
	cout<<sum<<endl;
}	
