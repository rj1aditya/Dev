#include<iostream>
#include<list>
#include<vector>
using namespace std;

int main()
{
    list<int> listOfInts1;

// It will create a list with 5 elements and each is initialized with a copy of element passed as second argument i.e. 119 in our case.
    list<int> listOfInts2(5, 119);

//In C++11 new overloaded constructor of std::list is introduced that can receive an initializer_list as argument and can initialize list elements with a copy of elements in initializer_list i.e.
    list<int> listOfInts3({2,8,7,5,3,1,4});

// Initializing a std::list with a std::vector or an Array
    vector<int> v = {1,2,3};
    list<int> listOfInts4(v.begin(), v.end());

    for( auto it = listOfInts4.begin(); it != listOfInts4.end(); it++ )
        cout<<*it<< " ";

    return 0;


}