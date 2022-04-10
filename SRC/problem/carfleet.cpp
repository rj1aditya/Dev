#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        
        //make a pair of car position and its speed
        vector<pair<int,int>> car_p_s;
        
        stack<double> car_reach_time;
        
        for( int i = 0; i < position.size(); i++ )
        {
            car_p_s.push_back( {position[i], speed[i]} );
        }
        
        // sort the array so that we can easily figure the the time of the last car when it will reach the target
        sort(car_p_s.begin(), car_p_s.end());
        
        //traverse the car_p_s from the last bcoz last car is ahead than others car

        for( int i = car_p_s.size() - 1; i >= 0; i-- )
        {
            auto it = car_p_s[i];
        
            double time = (static_cast<double>(target - it.first)/it.second);
            
            if( car_reach_time.empty() )
            {
                car_reach_time.push(time);
                continue;
            }
            
            if( time > car_reach_time.top() )
            {
                car_reach_time.push(time);
            }
        }
        
        return car_reach_time.size();
        
    }
};


int main()
{
    Solution s1;
    vector<int> pos{10,8,0,5,3};
    vector<int> speed{4,4,4,4,4,4};

    cout<<s1.carFleet(12, pos, speed);

}