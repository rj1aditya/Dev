#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {

        string nStr = to_string(n);
        int nLen = nStr.length();
        int nDigitLen = digits[0].size();
        
        int total = 0;
        
        for( int i = 1; i < nLen; i++ )
            total += pow(nDigitLen, i);
        
        for( int i = 0; i < nLen; i++ )
        {
            int N1 = nStr[i] - '0';
            bool hasSameNo = false;
            for(int j = 0; j < digits[0].size(); j++ )
            {
                int N2 = digits[0][j] - '0';
                if( N2 < N1 )
                {
                    total += pow(nDigitLen,  nLen - i -1);
                }
                else if( N2 == N1 )
                {
                    hasSameNo = true;
                    if( i == nLen -1)
                        total++;
                }
            }
            if(!hasSameNo){
                return total;
            }
        }
        
        return total;
        
    }
};

int main()
{
    Solution s;
    vector<string> v{"1357"};
    cout<<s.atMostNGivenDigitSet(v, 153);

}