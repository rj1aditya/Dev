#include<bits/stdc++.h>
using namespace std;

class Solution {
    //hashmap
    unordered_map<int,int> m;
    //i is state
    int DFS(vector<int>& nums, int i)
    {
        if( i == 0 )
            return nums[0];
        if( i == 1 )
            return max( nums[0], nums[1] );

        
        if( !m[i] )
        {
            m[i] = max( DFS(nums, i-1), DFS(nums, i-2) + nums[i]);
        }
        
        return m[i];
        
    }
public:
    
    int rob(vector<int>& nums) {
        
        //Top Down approach
        //n is the state of the DP
        int n = nums.size() - 1;
        return DFS(nums, n);
        
        /*bottom up solution
        if(nums.size()==1)return nums[0];
        int dp1=nums[0];
        int dp2=max(nums[0],nums[1]);
        int dp3=dp2;
        //here dp[1] = nums[1] will fail [2,1]
        //dp[1]=nums[1];
        for(int i=2;i<nums.size();i++){
            dp3=max(dp2,dp1+nums[i]);
            dp1 = dp2;
            dp2 = dp3;
        }
        //4,8,5,50,500,1000
        return dp3;*/
    }
};

int main()
{
    vector<int> v{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    Solution s;
    cout<<s.rob(v);
}