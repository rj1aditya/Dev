#include<iostream>
#include<thread>
#include<string>
#include<sstream>

using namespace std;


void output( string w )
{

}

int main()
{
	string s = "My company name is Capgemini";
	string s1;
	stringstream ss(s);
	
	thread t[3];
	
	int i = 0;
	while( getline( ss, s1, ' ' ) )
	{
		t[i] = output;
		//cout<<s1<<endl;
	}
	
	
}
	
	