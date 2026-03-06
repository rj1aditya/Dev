#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        
        vector<vector<int>> map(26);
        
        // making map of indexes let say string is abcdab
        // here v[0] will have indexes = 0, 4
        // v[1] = 1, 5
        // v[2] = 2
        for( int i = 0; i < s.size(); i++ )
            map[s[i] - 'a'].push_back(i);
        
        int ans = 0;
        
        // iterating word by word in words
        // e.g. ace, abc, ..
        // will take first ace
        for( auto &w: words )
        {
            int prev_indx = -1;
            int found = 1;
            // iterating each letter in "ace" will check if all letters is present in 
            // vector in indexes of increasing order
            for( int i = 0; found && i < w.length() ; i++ )
            {
                // if letter is 'a' then map['a'-'a'] i.e. map[0] will return its 1st row
                auto &v = map[w[i] - 'a'];
                auto it = upper_bound(begin(v), end(v), prev_indx);
                if( it == end(v))
                    found = 0;
                else
                    prev_indx = *it;
            }
            ans += found;
        }
        return ans;
        
    }
};
int main()
{
    Solution s1;
    string s = "abcde";
    vector<string> v{"a","bb","acd","ace"};
    cout<<s1.numMatchingSubseq(s, v);

}