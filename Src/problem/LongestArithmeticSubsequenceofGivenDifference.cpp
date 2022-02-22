#include<bits/stdc++.h>
using namespace std;


class Solution {
    vector<int> dp;
    int dfs(int indx, vector<int>& arr, int diff)
    {
        int maxLen = 1;
        if( dp[indx] != -1 )
            return dp[indx];
        
        for( int j = indx + 1; j < arr.size(); j++)
        {
            int len = 1;
            if( abs(arr[j] - arr[indx]) == abs(diff) )
            {
                len = 1 + dfs(j, arr, diff);
                maxLen = max(maxLen, len);
            }
        }
        dp[indx] = maxLen;
        return maxLen;
    }
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        sort(arr.begin(), arr.end(), greater<int>());
        
        dp.resize(arr.size(), -1);
        int ans = 0;
        for(int i = 0; i < arr.size(); i++ )
        {
            ans = max(ans, dfs(i, arr, difference));
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> v{3,0,-3,4,-4,7,6};
    cout<<s.longestSubsequence(v,3);
}