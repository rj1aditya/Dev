#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> v(26, -1);
        
        for(int i = 0; i < s.length(); i++)
            v[s[i]-'a'] = i;
        
        int start = 0;
        int end;
        
        vector<int> res;
        
        // <= taken e.g. "caedbdedda"
        while(start <= end)
        {
            int l = start;
            end = v[s[start]-'a'];
            while(start<end)
            {    
                if(v[s[start]-'a'] > end)
                    end = v[s[start]-'a'];
                start++;   
            }
            res.push_back(end-l+1);
            start++;
        }
        
        return res;
    }
};
int main()
{
    Solution s;
    string str="ababcbacadefegdehijhklij";
    vector<int> v = s.partitionLabels(str);
}