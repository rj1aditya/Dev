#include <iostream>
#include <string>
#include<type_traits>
using namespace  std;

template<typename T>
auto length(T const& value) {
    if (is_integral<T>::value) {
        return value;
    }
    else {
        return value.length();
    }
}
int main() {
    // Create shared_ptr managing an array of 5 ints
    int n{10};
    string str ="aditya";
    cout <<length(n)<<endl<<length(str)<<endl;
    // When arr goes out of scope, delete[] is called automatically
    return 0;
}