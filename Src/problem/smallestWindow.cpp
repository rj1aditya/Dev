#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    // Function to find the smallest window in the string s consisting
    // of all the characters of string p.
    string smallestWindow(string s, string p)
    {
        // Your code here

        unordered_map<char, int> m;

        for (int i = 0; i < p.length(); i++)
            m[p[i]]++;

        int max_len = p.length();

        unordered_map<char, int> match;

        int start = 0;
        int end = 0;
        int j = 0;
        int maxi = INT_MAX;
        string ans;
        int i = 0;
        while (i < s.length())
        {
            m[s[i]]--;

            if (m[s[i]] == 0)
                max_len--;

            if (max_len == 0)
            {
                while (max_len == 0)
                {
                    if (i - j + 1 < maxi)
                    {
                        maxi = i - j + 1;
                        start = j;
                        end = i;
                    }

                    m[s[j]]++;
                    if (m[s[j]] == 1)
                        max_len++;

                    j++;
                }
            }
            i++;
        }

        if (maxi == INT_MAX)
            return "-1";

        ans = s.substr(start, end);
        return ans;
    }
    bool canPair(vector<int> arr, int k)
    {
        int n = arr.size();
        // An odd length array cannot be divided into pairs
        if (n & 1)
            return false;

        // Create a frequency array to count occurrences
        // of all remainders when divided by k.
        unordered_map<int, int> freq;

        // Count occurrences of all remainders
        for (int i = 0; i < n; i++)
            freq[arr[i] % k]++;

        // Traverse input array and use freq[] to decide
        // if given array can be divided in pairs
        for (int i = 0; i < n; i++)
        {
            // Remainder of current element
            int rem = arr[i] % k;

            // If remainder is 0, then there must be even
            // number of elements with 0 remainder
            if (rem == 0)
            {
                if (freq[rem] & 1)
                    return false;
            }

            // Else number of occurrences of remainder
            // must be equal to number of occurrences of
            // k - remainder
            else if (freq[rem] != freq[k - rem])
                return false;
        }
        return true;
    }
};