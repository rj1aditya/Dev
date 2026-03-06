#include <bits/stdc++.h>
using namespace std;

class Solution
{
    using pii = pair<int, int>;
    pii src;
    pii dest;

public:
    // Function to find whether a path exists from the source to destination.
    bool is_Possible(vector<vector<int>> &grid)
    {
        // code here

        // find indexes or src and dest.
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    src.first = i;
                    src.second = j;
                }
                else if (grid[i][j] == 2)
                {
                    dest.first = i;
                    dest.second = j;
                }
            }
        }

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({src.first, src.second});
        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!pq.empty())
        {
            pii node = pq.top();
            pq.pop();

            int r = node.first;
            int c = node.second;

            if (r == dest.first && c == dest.second)
                return true;

            grid[r][c] == 0;

            for (int i = 0; i < 4; i++)
            {
                int rx = r + dir[i][0];
                int cx = r + dir[i][1];

                if (rx < 0 || cx < 0 || rx == grid.size() || cx == grid[0].size() || grid[rx][cx] == 0)
                    continue;

                grid[rx][cx] = 0;
                pq.push({rx, cx});
            }
        }

        return false;
    }
};

int main()
{
    vector<vector<int>> grid = {{1, 2},
                                {3, 2}};

    Solution s;
    cout << s.is_Possible(grid);

    return 0;
}