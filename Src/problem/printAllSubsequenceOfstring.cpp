#include<bits/stdc++.h>
using namespace std;

vector<string> v;

void allSeq(string s, string output)
{
    if(s.empty())
    {
        //cout<<output<<endl;
        v.push_back(output);
        return;
    }

    //include 1st letter
    allSeq(s.substr(1), output + s[0]);

    //Not include 1st letter
    allSeq(s.substr(1), output);
}


int main()
{
    string s{"abc"};

    string output = "";
    
    allSeq(s, output);
    for( auto a: v)
        cout<<a<<endl;
    return 0;
}