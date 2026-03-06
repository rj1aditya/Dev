#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string removeDuplicates(string s, int k)
    {

        while (1)
        {
            string tmp;
            int i = 0;
            int n = s.length();

            while (i < n)
            {
                int j = i + 1;
                int kk = k;
                if (j < n && s[i] == s[j])
                {
                    // cout << s[i] << " " << s[j] << endl;
                    while (kk)
                    {
                        kk--;
                        if (s[i] != s[j] || kk == 0)
                            break;
                        j++;
                    }
                }

                if (i + 1 == j)
                {
                    tmp = tmp + s[i];
                    i = j;
                }
                else if (kk == 0)
                {
                    i = j;
                }
                else
                {
                    tmp = tmp + s[i];
                    i++;
                }
            }

            if (tmp.size() == s.size())
                break;

            s = tmp;
        }

        return s;
    }
};
class Solution1
{
public:
    string removeDuplicates(string s, int k)
    {
        stack<pair<char, int>> stk;

        for (int i = 0; i < s.length(); i++)
        {
            if (!stk.empty() && stk.top().first == s[i])
            {
                stk.top().second++;
                if (stk.top().second == k)
                    stk.pop();
            }
            else
                stk.push({s[i], 1});
        }

        string ans;
        while (!stk.empty())
        {
            ans = stk.top().first + ans;
            stk.pop();
        }
        return ans;
    }
};
int main()
{
    Solution1 s;
    string str = "pbbcggttciiippooaais";

    cout << s.removeDuplicates(str, 2);
}