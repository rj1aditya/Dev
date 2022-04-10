#include <bits/stdc++.h>
using namespace std;

void BSF(int G[8][8], int vtx, int n)
{
    printf("\n%d-> ", vtx);
    queue<int> q;
    q.push(vtx);

    int visited[n] = {0};
    visited[vtx] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 1; i < n; i++)
        {
            if (visited[i] == 0 && G[u][i] == 1)
            {
                printf("%d-> ", i);
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}
vector<int> bfsOfGraph(int V, vector<int> adj[])
{
    // Code here
    vector<bool> visited(V, false);
    vector<int> ans;
    queue<int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty())
    {
        int current = q.front();
        ans.push_back(current);
        for (auto i : adj[current])
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
        q.pop();
    }
    return ans;
}
int main()
{
    int A[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 1, 1, 1, 0, 0, 0},
                   {0, 1, 0, 1, 0, 0, 0, 0},
                   {0, 1, 1, 0, 1, 1, 0, 0},
                   {0, 1, 0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 1, 1, 0, 1, 1},
                   {0, 0, 0, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 1, 0, 0}};

    int n = sizeof(A[0]) / sizeof(A[0][0]);
    // here 1 is vertex 1
    BSF(A, 1, n);
    return 0;
}