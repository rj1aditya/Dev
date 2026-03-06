#include<bits/stdc++.h>
using namespace std;

// class Solution {
// public:
//     int wordsTyping(vector<string>& sentence, int rows, int cols) {
        
//         int repSentance = 1;
        
//         int circle = 0;
//         int n = sentence.size();
//         int WordCount = 0;
//         cout<<"Sentence len: "<<n<<endl;
//         for(int i = 0; i < rows; i++)
//         {
//             int possibleLen = 0;
            
//             while(1)
//             {
                
//                 if( possibleLen + sentence[circle%n].length() <= cols )
//                 {
//                     possibleLen = possibleLen + sentence[circle%n].length()+1;
//                     circle++; 
//                     WordCount++;
                    
//                     cout<<"Row: "<< i<<"-Word count: "<<WordCount<<endl;
//                 }
//                 else
//                 {
//                     break;
//                 }
                
//             }
//         }
//         cout<<WordCount;
        
//         return WordCount/sentence.size();
//     }
// };

class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int answer  = 0;
        string s;
        for(auto x : sentence){ 
            s+=x;
            s+=" ";
        }
        int n = s.length();

        for(int i=0;i<rows;i++){
            answer+=cols;
            int ind = (answer)%n;
            while(ind>=0 && s[ind]!=' ')
            {
                answer--;
                ind--;
            }
            answer++;
        }
    
        return answer/n;
    }
};

int main()
{
    Solution s;
    // vector<int> v{1,2,3,0,2};
    vector<string> v;
    v.push_back("a");
    v.push_back("bcd");
    v.push_back("e");
    cout<<s.wordsTyping(v, 4,6);

}