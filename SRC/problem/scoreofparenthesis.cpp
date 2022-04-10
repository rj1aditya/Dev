#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {

        stack<char> stk;

        //since s is balanced , 0th idx would be '('
        stk.push(s[0]);

        for(int i=1; i < s.length(); i++)
        {
            if(s[i] == '(')
                stk.push(s[i]);
            else
            {
                int temp = 0;
                while(stk.top() != '(' )
                {
                    temp += stk.top();
                    stk.pop();
                }
                stk.pop();
                if(temp > 0)
                    stk.push(2*temp);
                else
                    stk.push(1);
            }
        }

        int sum = 0;
        cout<<stk.size()<<" "<<stk.top();
        while(!stk.empty())
        {
            sum += stk.top();
            stk.pop();
        }

        return sum;
    }
};

int main()
{
	string s = "((((((())))()())))";
	Solution obj;

	cout<<obj.scoreOfParentheses(s);
}
