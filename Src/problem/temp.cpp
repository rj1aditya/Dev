#include<bits/stdc++.h>
using namespace std;

int main()
{
	string s = "   hello   World   !!   ";

	stringstream ss(s);

	string word;
	while(ss>>word)
		cout<<word;

	return 0;
}
