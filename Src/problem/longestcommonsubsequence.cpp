#include<bits/stdc++.h>
using namespace std;

class Solution {
    string t1;
    string t2;
    vector<vector<int>> v;
    int dp(int i, int j)
    {
        if( v[i][j] != -1 )
            return v[i][j];
        
        
        int option1 = dp(i+1, j);
        int firstOccurance;
        
        int option2;
        if( (firstOccurance = t2.find(t1[i], j)) != string::npos )
            option2 = 1 + dp(i+1, firstOccurance + 1);

        
        return v[i][j] = max(option1, option2);
    }
        
public:
    int longestCommonSubsequence(string text1, string text2) {
        t1 = text1;
        t2 = text2;
        int n = t1.length();
        int m = t2.length();
        
        v.resize(n+1);
        
        for(int i = 0; i <= n; i++)
            v[i].resize(m+1, 0);
        
        for( int i = 0; i < n; i++ )
            for( int j = 0; j < m; j++ )
                v[i][j] = -1;
        
        return dp(0, 0);
    }
};

int main()
{
    Solution s;
    cout<<s.longestCommonSubsequence("abcde", "ace");
}