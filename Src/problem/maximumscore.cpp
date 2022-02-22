#include<bits/stdc++.h>
using namespace std;
class Solution {
    vector<vector<int>> v;
    vector<int> nums;
    vector<int> multipliers;
    //This is DP Problem solved using 2d array
    int DFS(int i, int left) // State Condition
    {
        if( i == multipliers.size() ) //Base Condition
            return 0;
        
        int right = nums.size() - 1 - (i - left);
        int mult = multipliers[i];
        
        if( v[i][left] == INT_MIN )
        {
            v[i][left] = max(mult*nums[right] + DFS(i+1, left), mult*nums[left] + DFS(i+1, left+1) );// Recurrence relation
        }
        for(int i = 0; i < v.size(); i++)
        {
            for( int j = i; j < v[0].size(); j++)
            {
                cout<<"v["<<i<<"]["<<j<<"]"<<v[i][j]<<endl;
            }
        }
        return v[i][left];
    }
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int m = multipliers.size();
        int n = nums.size();
        this->nums = nums;
        this->multipliers = multipliers;
        
        v.resize(m, vector<int>(m,INT_MIN));
        return DFS(0,0);
    }
};

int main()
{
    Solution s;
    vector<int> nums{1,2,3};
    vector<int> multi{3,2,1};

    cout<<s.maximumScore(nums,multi);

}