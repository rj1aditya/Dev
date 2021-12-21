#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        
        //for storing the matrix row, and col index value 
        queue<pair<int,int>> Q;
        
        //Quing the vertixes which are 0, and non zeros are updating to -1.
        for(int i = 0; i < mat.size(); i++)
        {
            for(int j = 0; j < mat[0].size(); j++)
            {
                if(mat[i][j] == 0)
                    Q.push({i,j});
                else
                    mat[i][j] = -1;
            }
        }
        
        //to know the level
        int length = 0;
        
        //to visit the index in all 4 direction
        int dir[4][2] = {{-1,0}, {0,-1},{1,0}, {0,1}};
        while(!Q.empty())
        {
            length++;
            int size = Q.size();
            
            while( size-- > 0)
            {
                auto it = Q.front();
                Q.pop();

                for( auto d: dir )
                {
                    int r = it.first;
                    int c = it.second;
                    r += d[0];
                    c += d[1];
                    
                    if( r < 0 || c < 0 || r == mat.size() || c == mat[0].size() || mat[r][c] != -1)
                        continue;
                    
                    mat[r][c] = length;
                    Q.push({r,c});
                }
            }
        }
        
        return mat;
        
        
    }
};


int main()
{
    Solution s;
    vector<vector<int>> v{{0,0,0},{0,1,0},{1,1,1}};
    s.updateMatrix(v);
}