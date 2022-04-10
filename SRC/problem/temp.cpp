#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> mem;
    vector<int> nums;
    
    bool dfs(int sum, int i)
    {
        if(sum == 0)
            return mem[i][sum] = true;
        if(sum < 0 || i >= nums.size())
            return mem[i][sum] = false;
        
        
        if(mem[i][sum] != -1)
            return mem[i][sum];
        
        return mem[i][sum] = dfs(sum-nums[i], i+1) || dfs(sum, i+1);
    }
    
    bool canPartition(vector<int>& nums) {
        
        int sum = 0;
        for(int i =0; i < nums.size(); i++)
        {
            sum += nums[i];
        }
        
        if(sum%2 != 0)
            return false;
        
        int n = nums.size();
        mem.resize(n, vector<int>(sum/2 + 1, -1));
        
        this->nums = nums;
        
        return dfs(sum/2, 0);
    }
};

int main()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(5);
	v.push_back(11);
	v.push_back(5);
	Solution s;
	cout<<s.canPartition(v);
	return 0;
}
