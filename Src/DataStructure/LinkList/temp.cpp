
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if( n == 1 )
            return {0};
        
        vector<unordered_set<int>> adj(n);

        //Making adjacency list using vector<unordered_set<int>> adj[n];
        // here in first iteration of vector<vector<int>>& edges gives edges i.e. a[0] = 3, a[1] = 0
        for( auto &a: edges )
        {
            adj[a[0]].insert(a[1]); 
            adj[a[1]].insert(a[0]);
        }

        queue<int> Q;
        //traversing the adjacency list like 0th set, 1st set, 2nd set, 3rd set and so on
        for( int i = 0; i < adj.size(); i++ )
        {
            // Queue will hold only those adjacency node which have only 1 element in the set
            if(adj[i].size() == 1)
                Q.push(i);
        }

        //Why n > 2? coz n is showing nodes, and let say if n = 2 so there is only 1 edge posible n-1 edges
        while( n > 2)
        {
            int len = Q.size();
            n = n -len;

            for( int i = 0; i < len; i++ )
            {
                int node = Q.front();
                Q.pop();

                //to trave set element of adjacency list i.e. adj[0] -> 1 
                for( auto &a: adj[node] )
                {
                    // it will remove the adj[1] -> 0 set element
                    adj[a].erase(node);
                    if(adj[a].size() == 1)
                        Q.push(a);
                }

            }
        }
        vector<int> result;
        while(!Q.empty()){
            result.push_back(Q.front());
            Q.pop();
        }
        return result;
    }
};

int main()
{

    Solution s;
    vector<vector<int>> v{5, vector<int>{2, -1}};
    v[0][0] = 3;
    v[0][1] = 0;
    v[1][0] = 3;
    v[1][1] = 1;
    v[2][0] = 3;
    v[2][1] = 2;
    v[3][0] = 3;
    v[3][1] = 4;
    v[4][0] = 5;
    v[4][1] = 4;

    vector<int> res = s.findMinHeightTrees(6, v);
    for(int i = 0; i < res.size(); i++)
    {
        cout<<res[i]<<" ";
    }

}