class Solution
{
public:
    string decodeString(string s)
    {
        stack<char> stk;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != ']')
            {
                stk.push(s[i]);
            }
            else
            {
                string tempS = "";
                while (stk.top() != ']')
                {
                    tempS += stk.top();
                    stk.pop();
                }
                stk.pop();
                while( isDigit(s.top() )
                {
                    
                }
            }
        }
    }
};