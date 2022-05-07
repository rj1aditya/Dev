#include <bits/stdc++.h>
using namespace std;

class Solution1
{
public:
    int getParent(vector<int> &parents, int idx)
    {

        if (parents[idx] == idx)
        {
            return idx;
        }

        parents[idx] = getParent(parents, parents[parents[idx]]);

        return parents[idx];
    }

    int minCostConnectPoints(vector<vector<int>> &points)
    {

        int n = points.size();
        vector<int> parents(n);
        iota(parents.begin(), parents.end(), 0);
        int ans = 0;
        int edges = 0;
        priority_queue<vector<int>> pq;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != j)
                {
                    pq.push({-1 * (abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])), i, j});
                }
            }
        }

        while (edges != n - 1)
        {

            vector<int> edge = pq.top();

            int p1 = getParent(parents, edge[1]);
            int p2 = getParent(parents, edge[2]);

            if (p1 != p2)
            {

                ans += -1 * edge[0];

                parents[p1] = p2;

                edges++;
            }

            pq.pop();
        }

        return ans;
    }
};

class UnionFind
{
public:
    vector<int> parent, size;
    int edges = 0;
    UnionFind(int n)
    {
        parent = vector<int>(n);
        size = vector<int>(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int Find(int curr)
    {
        if(curr == parent[curr])
            return curr;

        return parent[curr] = Find(parent[curr]);
    }

    bool Union(int i, int j)
    {
        i = Find(i);
        j = Find(j);

        if (i == j)
            return false;

        if (size[i] >= size[j])
        {
            size[i] += size[j];
            parent[j] = i;
        }
        else
        {
            size[j] += size[i];
            parent[i] = j;
        }

        edges++;
        return true;
    }
};

class Solution
{
public:
    struct node
    {
        int x, y, dist;

        bool operator()(node &a, node &b)
        {
            return a.dist > b.dist;
        }
    };

    int minCostConnectPoints(vector<vector<int>> &points)
    {
        priority_queue<node, vector<node>, node> pq;
        int n = points.size();

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                pq.push({i, j, dist});
            }
        }

        int result = 0;
        UnionFind uf(n);

        while (!pq.empty())
        {
            node curr = pq.top();
            pq.pop();

            if (uf.Union(curr.x, curr.y))
                result += curr.dist;

            if (uf.edges == n - 1)
                return result;
        }

        return 0;
    }
};