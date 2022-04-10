// C++ program to print all 
// permutations with duplicates allowed 
#include <bits/stdc++.h> 
using namespace std; 


// Function to print permutations of string 
// This function takes three parameters: 
// 1. String 
// 2. Starting index of the string 
// 3. Ending index of the string. 
class Solution
{
    vector<string> v;
    
    void permute(string s, int l, int r)
    {
        if(l == r)
            v.push_back(s);
        
        for(int i = l; i <= r; i++)
        {
            swap(s[l], s[i]);
            permute(s, l+1, r);
            swap(s[l], s[i]);
        }
    }
    
	public:
		vector<string> find_permutation(string S)
		{
		    // Code here there
		    permute(S, 0, S.length()-1);
		    return v;
		}
};

// Driver Code 
int main() 
{ 
    Solution s;
    string str = "ABC"; 
    int n = str.size(); 
    vector<string> v = s.find_permutation(str);
    for(auto a: v)
        cout<<a<<" "; 
    return 0; 
} 

// This is code is contributed by rathbhupendra 
