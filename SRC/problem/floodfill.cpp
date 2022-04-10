#include<bits/stdc++.h>
using namespace std;

class Solution {
    
    void makeColor(vector<vector<int>>& image, int sr, int sc, int newColor, int rows, int cols, int src) {
        
        if(sr < 0 || sr >= rows || sc < 0 || sc >= cols)
            return;
        else if(image[sr][sc] != src)
            return;
        
        image[sr][sc] = newColor;
        
        
        makeColor(image, sr-1, sc, newColor, rows, cols, src);
        makeColor(image, sr+1, sc, newColor, rows, cols, src);
        makeColor(image, sr, sc-1, newColor, rows, cols, src);
        makeColor(image, sr, sc+1, newColor, rows, cols, src);
        
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(newColor == image[sr][sc]);
        int rows = image.size();
        int cols = image[0].size();
        int src = image[sr][sc];
        makeColor(image, sr, sc, newColor, rows, cols, src);
        
        return image;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v{{1,1,1},{1,1,0},{1,0,1}};
    s.floodFill(v, 1,1,2);
}