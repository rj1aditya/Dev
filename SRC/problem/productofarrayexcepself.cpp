#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        
        vector<int> res(nums.size(), 1);
        
        for( int i = 1; i < nums.size(); i++)
        {
            //consider res as a prefix vector
            res[i] = res[i-1]*nums[i-1];
        }
        int a = 1;
        for( int i = nums.size()-2; i >= 0;  i--)
        {
            a = a * nums[i+1];
            res[i] *= a;
        }
        return res;
        //prefix and suffix  vector
        /*space complexity is O(n)
        vector<int> prefix(nums.size(),1);
        vector<int> postfix(nums.size(),1);
        
        for(int i = 1; i < nums.size(); i++)
        {
            prefix[i] = prefix[i-1]*nums[i-1];
        }
        for(int i = nums.size() - 2; i >= 0 ; i--)
        {
            postfix[i] = postfix[i+1]*nums[i+1];
        }
        
        vector<int> res(nums.size());
        for(int i = 0; i < nums.size(); i++)
        {
            res[i] = prefix[i]*postfix[i];
        }
        return res;
        */
        /*Brute force TLE
        vector<int> v(nums.size(), 1);
        for( int i = 0; i < nums.size(); i++)
        {
            for( int j = 0; j < nums.size(); j++ )
            {
                if(i != j)
                {
                    if( nums[j] == 0 )
                        v[i] = 0;
                    else
                    {
                        //if(v[i]%nums[j] != 0)
                            v[i] *=nums[j];
                    }
                }
            }
        }
        return v;
        */
    }
};
int main()
{
    Solution s;
    vector<int> v{1,2,3,4};
    s.productExceptSelf(v);

}