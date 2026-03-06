#include<bits/stdc++.h>
using namespace std;

vector<string> ans;

void makeSubsequenceOfString(string s, string output)
{
	if(s.length() == 0)
	{
		ans.push_back(output);
		return;
	}

	makeSubsequenceOfString(s.substr(1), output+s[0]);
	makeSubsequenceOfString(s.substr(1), output);
}

int main()
{
	string s= "abcd";
	string output;
	makeSubsequenceOfString(s, output);
	for(auto s: ans)
		cout<<s<<endl;
}
