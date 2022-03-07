#include <bits/stdc++.h>
using namespace std;

class Solution
{
    string t1;
    string t2;
    vector<vector<int>> v;
    int dp(int i, int j)
    {
        if (t1[i] == '\0' || t2[j] == '\0')
            return 0;

        if (v[i][j] != -1)
            return v[i][j];

        if (t1[i] == t2[j])
            v[i][j] = 1 + dp(i + 1, j + 1);
        else
            v[i][j] = max(dp(i + 1, j), dp(i, j + 1));

        return v[i][j];
    }

public:
    int longestCommonSubsequence(string text1, string text2)
    {
        t1 = text1;
        t2 = text2;
        int n = t1.length();
        int m = t2.length();

        v.resize(n + 1);

        for (int i = 0; i <= n; i++)
            v[i].resize(m + 1, 0);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                v[i][j] = -1;

        return dp(0, 0);
    }
};

class Solution2
{
    string text1;
    string text2;
public:
    int lcs(int n, int m)
    {
        vector<vector<int>> t(n+1, vector<int>(m+1, 0));

        for (int i = 1; i < n + 1; i++)
        {
            for (int j = 1; j < m + 1; j++)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    t[i][j] = 1 + t[i - 1][j - 1];
                }
                else
                {
                    t[i][j] = max(t[i - 1][j], t[i][j - 1]);
                }
            }
        }
        return t[n][m];
    }

    int longestCommonSubsequence(string text1, string text2)
    {
        this->text1 = text1;
        this->text2 = text2;
    
        int n = text1.length();
        int m = text2.length();

        return lcs(n, m);
    }
};

int main()
{
    Solution s;
    cout << s.longestCommonSubsequence("abcde", "ace");
}