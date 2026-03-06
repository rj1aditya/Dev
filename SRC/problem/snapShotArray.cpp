#include<bits/stdc++.h>
using namespace std;

class SnapshotArray {
    vector<vector<int>> snaps;
    //vector<int> v;
    map<pair<int,int>, int> m;
    
    int snap1;
public:
    SnapshotArray(int length) {
        //v.resize(length, 0);
        snaps.resize(length, {0});
        snap1 = 0;
    }
    
    void set(int index, int val) {
        //v[index] = val;
        snaps[index].push_back(snap1);
        m[{index, snap1}] = val;
    }
    
    int snap() {
        return snap1++;
    }
    
    int get(int index, int snap_id) {
        int u = upper_bound(snaps[index].begin(), snaps[index].end(), snap_id) - snaps[index].begin();
        --u;
        return m[{index,snaps[index][u]}];
    }
};

int main()
{
    // s;
    SnapshotArray s(10);
    s.set(0,10);
    s.snap();
    s.snap();
    s.snap();
    s.set(0,12);
    s.get(0,2); 
}