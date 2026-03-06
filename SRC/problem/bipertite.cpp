#include <bits/stdc++.h>
using namespace std;

// BFS
class Solution1
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, 0);
        queue<int> q;

        for (int i = 0; i < n; i++)
        {
            if (colors[i])
                continue;

            colors[i] = 1;
            q.push(i);

            while (!q.empty())
            {
                int temp = q.front();

                for (auto neighbor : graph[temp])
                {

                    // Color neighbor with opposite color
                    if (!colors[neighbor])
                    {
                        colors[neighbor] = -colors[temp];
                        q.push(neighbor);
                    }

                    // If the neighbor has the same color - can't bipartite.
                    else if (colors[neighbor] == colors[temp])
                        return false;
                }
                q.pop();
            }
        }
        return true;
    }
};

// DFS

class Solution
{
public:
    vector<int> vis, col;
    bool dfs(int v, int c, vector<vector<int>> &graph)
    {
        vis[v] = 1;
        col[v] = c;
        for (int child : graph[v])
        {
            if (vis[child] == 0)
            {
                // here c^1 is for flipping 1 by 0 or 0 by 1, that is flip the current color
                if (dfs(child, c ^ 1, graph) == false)
                    return false;
            }
            else
            {
                if (col[v] == col[child])
                    return false;
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vis.resize(n);
        col.resize(n);

        for (int i = 0; i < n; ++i)
        {
            if (vis[i] == 0 && dfs(i, 0, graph) == false)
            {
                return false;
            }
        }

        return true;
    }
};