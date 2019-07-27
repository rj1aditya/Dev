#include<iostream>

int main()
{
	int arr[5] = {1,2,3,4,5};

	std::cout<<sizeof(arr)/sizeof(arr[0]);

	int a{5},b{6};

	a ^= b;
	b ^= a;
	a ^= b;
	std::cout<<std::endl;
	std::cout<< a << " "<<b;
}
