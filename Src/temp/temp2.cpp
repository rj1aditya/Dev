#include<iostream>
#include<string>
#include<fstream>

using namespace std;


int main()
{
	string s;
	ifstream in("temp1.cpp");

	while( getline( in, s ) )
		cout<<s<<endl;
}
