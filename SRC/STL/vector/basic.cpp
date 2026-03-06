#include<iostream>
#include<vector>
using namespace std;

int main()
{
    // Creating a vector, 6 ways
    // create a simple empty vector
    vector<int> v1;
    cout<<"Size: "<<v1.size()<<" Capacity: "<<v1.capacity()<<endl; // 0 0
    v1.push_back(10);
    cout<<"Size: "<<v1.size()<<" Capacity: "<<v1.capacity()<<endl; // 1 1
    v1.push_back(10);
    cout<<"Size: "<<v1.size()<<" Capacity: "<<v1.capacity()<<endl; // 2 2
    v1.push_back(10);
    cout<<"Size: "<<v1.size()<<" Capacity: "<<v1.capacity()<<endl; // 3 4
    // Create a vector of size n with all values as 10.
    vector<int> v2(3,10);
    v2 = v1;
    cout<<"Size: "<<v2.size()<<" Capacity: "<<v2.capacity()<<endl; // 3 4
    // create vector and initialize vector similar like array initialization
    vector<int> v3{ 10, 20, 30 };

    // Initializing from an array
    int arr[] = { 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> v4(arr, arr + n);

    // create vector from another same type vector
    vector<int> v5(v1.begin(), v1.end());

    // create vector with fix size now
    vector<int> v6(10);
}