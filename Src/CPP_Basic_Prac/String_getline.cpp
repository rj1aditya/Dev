#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>

using namespace std;

int g;

int main()
{
	char i = 0x4;
	char j =0x5;
	char k = i&j;
	cout<<i<<"&"<<j<<"="<<k;
}