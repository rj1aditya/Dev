#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m,0));
        int count = 0;
        
        //adding 1st row
        for(int i = 0; i < m; i++)
        {
            dp[0][i] = matrix[0][i];
            count += dp[0][i];
        }
            
        //adding 1st col
        for(int i = 1; i < n; i++)
        {
            dp[i][0] = matrix[i][0];
            count += dp[i][0];
        }
        
        for(int i = 1; i < n; i++)
        {
            for( int j = 1; j< m; j++)
            {
                if(matrix[i][j] == 1)
                {
                    dp[i][j] = 1 + min( dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]) );
                    count += dp[i][j];
                }
            }
        }
        return count;
    
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v{
  {0,1,1,1},
  {1,1,1,1},
  {0,1,1,1}
};
    cout<<s.countSquares(v);
}