#include<bits/stdc++.h>
using namespace std;

// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution {
    map<int, Employee*> m;
    int getImp(int id)
    {
        int s = m[id]->importance;
        
        //subordinate will fetch the nodeId or employee id, using that id we will get the address of that employee then its importance
        for(auto subordinate: m[id]->subordinates)
        {
            s += getImp(subordinate);
        }
        
        return s;
    }
public:
    //DFS
    int getImportance(vector<Employee*> employees, int id) {
        for(auto &node: employees)
        {
            //it stores the nodeId as key and its address as value
            m[node->id] = node;
        }
        return getImp(id);
    }
};

int main()
{
    Solution s1;
    Employee s[3] = {{1,5,{2,3}},{2,3,{}},{3,3,{}}};
    vector<Employee*> v;
    v.push_back(&s[0]);
    v.push_back(&s[1]);
    v.push_back(&s[2]);
    cout<<s1.getImportance(v, 1);

}