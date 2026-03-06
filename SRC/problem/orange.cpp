#include<bits/stdc++.h>
using namespace std;
class Solution
{
    public:
    //Function to find minimum time required to rot all oranges. 
    int orangesRotting(vector<vector<int>>& grid) {
        // Code here
        queue<pair<int,int>> q;
        int R = grid.size();
        int C = grid[0].size();
        
        for(int i = 0; i < grid.size();i++)
        {
            for(int j = 0; j < grid[0].size(); j++)
            {
                if(grid[i][j] == 2)
                    q.push({i,j});
            }
        }
        
        int dir[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};
        int target = 0;
        while( !q.empty() )
        {
            int qSize = q.size();
            int check = 0;
            while(qSize-- > 0)
            {
                auto it = q.front();
                q.pop();
                
                for( auto a: dir)
                {
                    int r = a[0] + it.first;
                    int c = a[1] + it.second;
                    
                    if( r < 0 || c < 0 || r == R || c == C || grid[r][c] == 0 || grid[r][c] == 2 )
                        continue;
                
                    grid[r][c] = 2;
                    q.push({r,c});
                    check = 1;
                }
                
            }
            if(check)
                target++;
        }
        
        return target;
    }
    
};

int main()
{
    Solution s;
    vector<vector<int>> v{{2,1,1},{1,1,0},{0,1,1}};
    cout<<s.orangesRotting(v);
}