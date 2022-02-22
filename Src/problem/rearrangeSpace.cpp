#include<bits/stdc++.h>
using namespace std;

class Solution {
    string spaceNWordCount(const string &text)
    {
        vector<string> words;
        
        stringstream sso(text);
        
        string res;
        int spaceC = count(text.begin(), text.end(), ' ');
        
        while( sso>> res)
        {
            words.push_back(res);
        }
        
        int n = words.size();
        
        int quotient = n==1? 0: spaceC/(n-1);
        int remainder = n==1? spaceC: spaceC%(n-1);
        
        res = "";
        for( auto &w: words)
        {
            if( !res.empty() )
                res = res + string(quotient, ' ');
            res = res + w;
        }
        
        res = res + string(remainder, ' ');
        return res;
    }
public:
    string reorderSpaces(string text) {
        
        return spaceNWordCount(text);
        
    }
};


int main()
{
    cout<<reorderSpaces("  this   is  a sentence ")<<"yes";
}