#include<bits/stdc++.h>
using namespace std;
class Solution {
    
    int MaxArea(vector<vector<int>>& grid, int r, int c, int rows, int cols)
    {   
        if(r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0)
            return 0;
        
        grid[r][c] = 0;

        return 1 + MaxArea(grid, r-1, c, rows, cols) + MaxArea(grid, r+1, c, rows, cols) + MaxArea(grid, r, c-1, rows, cols) + MaxArea(grid, r, c+1, rows, cols);
        
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxIsland = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        for(int i = 0; i < grid.size(); i++)
        {
            for(int j = 0; j < grid[0].size(); j++)
            {
                if(grid[i][j] == 1)
                    maxIsland = max(maxIsland, MaxArea(grid, i, j, rows, cols));
            }
        }
        
        return maxIsland;
        
    }
};


int main()
{
    Solution s;
    vector<vector<int>> v{{1,1,0,0,0},{1,1,0,0,0},{0,0,0,1,1},{0,0,0,1,1}};
    cout<<s.maxAreaOfIsland(v);
}