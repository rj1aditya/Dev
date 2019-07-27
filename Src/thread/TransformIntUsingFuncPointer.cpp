#include<iostream>
#include<thread>
using namespace std;

int square(int a)
{
	return a*a;
}

int double_int(int a)
{
	return 2*a;
}

void transform( int *arr, int (*tx)(int) )
{
	for( int i = 0 ; i < 5; i++ )
	{
		arr[i] = tx( arr[i] );
	}
}

int main()
{
	int arr[5] = {1,2,3,4,5};
	
	transform( arr, double_int );
	
	cout<<"After double no are: "<<endl;
	for( int i = 0; i < 5; i++ )
	{
		cout<<arr[i]<<" ";
	}
	
	transform( arr, square );
	
	cout<<"After square no are: "<<endl;
	for( int i = 0; i < 5; i++ )
	{
		cout<<arr[i]<<" ";
	}
	
}
	