#include <bits/stdc++.h>

using namespace std;
class Solution
{
    vector<int>
        visited;

    bool DFS(int node, int parent, vector<int> adj[])
    {
        visited[node] = 1;

        for (auto x : adj[node])
        {
            if (visited[x] == -1)
            {
                if (DFS(x, node, adj) == true)
                    return true;
            }
            else if (x != parent)
                return true;
        }

        return false;
    }

public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[])
    {
        // Code here

        visited = vector<int>(V + 1, -1);

        for (int i = 0; i < V; i++)
        {
            if (visited[i] == -1)
            {
                if (DFS(i, -1, adj) == true)
                    return true;
            }
        }

        return false;
    }
};

// { Driver Code Starts.
int main()
{

    int V = 5;
    int E = 5;
    vector<int> adj[V];

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(4);
    adj[4].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);

    Solution obj;
    bool ans = obj.isCycle(V, adj);
    if (ans)
    {
        cout << "Cycle Detected";
    }
    else
        cout << "No Cycle Detected";

    return 0;
}