#include <bits/stdc++.h> 
vector<vector<int>> wallsAndGates(vector<vector<int>> &a, int n, int m) {
    // Write your code here.

    queue<pair<int,int>> q;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(a[i][j] == 0)
                q.push({i, j});
        }
    }

    int dir[] = {-1, 0, 1, 0};
    int dic[] = {0, 1, 0, -1};

    while(!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int newr = r + dir[i];
            int newc = c + dic[i];

            if(newr >= 0 && newc >= 0 && newr < n && newc < m && a[newr][newc] != -1 && a[newr][newc] != 0)
            {
                if(1+a[r][c] < a[newr][newc])
                {
                    a[newr][newc] = 1+a[r][c];
                    q.push({newr, newc});
                }
            }
        }
    }
    return a;

}