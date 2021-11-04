#include<iostream>
#include<sstream>
using namespace std;
int main()
{
	string s = "Aditya Jain Age 25";
	stringstream ss(s);
	string splitS;
	while( getline(ss, splitS, ' '))
		       cout<<splitS<<endl;

	return 0;
}	
