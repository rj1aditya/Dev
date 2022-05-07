#include <bits/stdc++.h>
using namespace std;

    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Code here
        vector<int> ans(V, INT_MAX);
        ans[S] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});
        while (!pq.empty())
        {
            pair<int, int> p = pq.top();
            int node = p.second;
            pq.pop();
            for (int i = 0; i < adj[node].size(); i++)
            {
                int adjacentnode = adj[node][i][0];
                int weight = adj[node][i][1];
                if (ans[adjacentnode] > weight + ans[node])
                {
                    ans[adjacentnode] = weight + ans[node];
                    pq.push({ans[adjacentnode], adjacentnode});
                }
            }
        }
        return ans;
    }