#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {

        // length of max number in a binary representation
        int L = 31;

        int maxXor = 0;
        int currXor;

        set<int> prefixes;

        for(int i = 4; i > -1; i--)
        {
            // go to the next bit by the left shift
            maxXor <<= 1;
            // set 1 in the smallest bit
            currXor = maxXor | 1;
            prefixes.clear();
            // compute all possible prefixes 
            // of length (L - i) in binary representation
            for(int num: nums) 
                prefixes.insert(num >> i);
            // Update maxXor, if two of these prefixes could result in currXor.
            // Check if p1^p2 == currXor, i.e. p1 == currXor^p2.
            for(int p: prefixes) {
                if (prefixes.find(currXor^p) != prefixes.end()) {
                    maxXor = currXor;
                    break;
                }
            }
        }
        return maxXor;
    }
};

int main()
{
    Solution s;
    vector<int> v{3,10,5,25,2,8};
    cout<<s.findMaximumXOR(v);
}