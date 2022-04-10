#include<bits/stdc++.h>
using namespace std;


class Solution {
    
    bool isDigit(char c)
    {
        if( c >= '0' && c <= '9' )
            return true;
        
        return false;
    }
    
    string concat(string s, int n)
    {
        string s1 = s;
        
        for(int i = 1; i < n; i++)
        {
            s += s1;
        }
        return s;
    }
        
public:
    string decodeString(string s) {
        
        stack<char> stk;
        
        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] != ']')
            {
                stk.push(s[i]);
            }
            else
            {
                string temp = "";
                while(stk.top() != '[')
                {
                    temp = stk.top() + temp;
                    stk.pop();
                }
                stk.pop();
                
                string num = "";
                while(!stk.empty() && isDigit(stk.top()) )
                {
                    num = stk.top() + num;
                    stk.pop();
                }
                int num1 = stoi(num);
                temp = concat(temp, num1);
                
                for(int x = 0; x < temp.length(); x++)
                {
                    stk.push(temp[x]);
                }
                
            }
        }
        
        string str1 = "";
        while(!stk.empty())
        {
            str1 = stk.top() + str1;
            stk.pop();
        }
        
        //reverse(str1.begin(), str1.end());
        return str1;
        
    }
};

int main()
{
    string s = "3[a]2[bc]"; // aaabcbc
    Solution s1;
    cout<<s1.decodeString(s);
}