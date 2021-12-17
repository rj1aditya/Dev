#include<bits/stdc++.h>

using namespace std;

int main()
{
    list<pair<int,int>> l;
    unordered_map<int, pair<int,list<pair<int,int>>::iterator>> map;

    l.push_front({1,100});
    map[1] = {100, l.begin()};


    auto p = l.back();
    cout<<p.first<<" "<<p.second;

    auto xx = map[1];
    if(!l.empty())
        cout<<"\nlist is not empty";
    l.erase(xx.second);
    if(l.empty())
        cout<<"\nlist is empty";
    // auto it1 = map.find(p.first);
    // if(!map.empty())
    //     cout<<"\nMap is not empty";
    // map.erase(it1);
    // if(map.empty())
    //     cout<<"\nMap is empty";
}