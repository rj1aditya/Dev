#include<bits/stdc++.h>
using namespace std;

class Solution {
    //Hashmap
    unordered_map<int,int> hash_cost;
    
    int DFS(vector<int>& cost, int i)
    {
        //Base condition
        if( i < 2 )
        {
            return hash_cost[i];
        }
            
        
        if( hash_cost.find(i) == hash_cost.end() )
            hash_cost[i] = cost[i] +  min( DFS( cost, i-1), DFS( cost, i-2) );

        return hash_cost[i];
    }

public:
    int minCostClimbingStairs(vector<int>& cost) {
        // The array's length should be 1 longer than the length of cost
        // This is because we can treat the "top floor" as a step to reach
        vector<int> v(cost.size()+1);
        
        // Start iteration from step 2, since the minimum cost of reaching
        // step 0 and step 1 is 0
        for (int i = 2; i < v.length; i++) {
            int takeOneStep = v[i - 1] + cost[i - 1];
            int takeTwoSteps = v[i - 2] + cost[i - 2];
            v[i] = Math.min(takeOneStep, takeTwoSteps);
        }
        
        // The final element in minimumCost refers to the top floor
        return v[v.size - 1];
    }
};
int main()
{
    Solution s;
    vector<int> v{1,100};
    cout<<s.minCostClimbingStairs(v);
}