#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        
        //key is timeline, value is: task index, timerequired 
        map< int, vector<pair<int,int>> > pc;
        
        for(int task = 0; task < tasks.size(); task++ )
        {
            int key = tasks[task][0];
            int timereq = tasks[task][1];
            
            pc[key].push_back( {task, timereq} );
            
        }
        return {};        
    }
    
};


priority_queue< pair<long int,long int> , vector<pair<long int, long int>>, greater<pair<long int,long int> >
int main()
{
    Solution s;
    vector<vector<int>> v{{1,2},{2,4},{3,2},{4,1},{1,1}};
    vector<int> rs;
    rs = s.getOrder(v);

}