#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,int> freq; 
        unordered_map<int,int> ends; 
        for (int i : nums) {
            freq[i]++; 
        }
        
        for (int i : nums) 
        {
            if (freq[i] == 0) {
                continue; 
            }
            if (ends[i - 1] > 0) {
                freq[i]--;
                ends[i - 1]--;
                ends[i]++; 
            } else if (freq[i + 1] > 0 && freq[i + 2] > 0) {
                freq[i]--;
                freq[i + 1]--;
                freq[i + 2]--;
                ends[i + 2]++; 
            } else {
                return false; 
            }
        }
        
        return true; 
    }
};
int main()
{
    Solution s;

    vector<int> v{1,2,3,3,4,5};
    cout<<s.isPossible(v);

}