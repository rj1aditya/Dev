#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<int>>& matrix) {
        
        vector<vector<int>> m(matrix.size()+1, vector<int>(matrix[0].size()+1, 0));
        
        int maxCount = 0;
        
        for( int i = 1; i <= matrix.size(); i++ )
        {
            for(int j = 1; j <= matrix[0].size(); j++)
            {
                if(matrix[i-1][j-1] == 1)
                    m[i][j] = 1 + min(m[i-1][j-1],min(m[i][j-1], m[i-1][j]));
                
                if(maxCount < m[i][j])
                    maxCount = m[i][j];
            }
        }
        return maxCount*maxCount;
        
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v{{1,0,1,0,0},{1,0,1,1,1},{1,1,1,1,1},{1,0,0,1,0}};
    cout<<s.maximalSquare(v);
}