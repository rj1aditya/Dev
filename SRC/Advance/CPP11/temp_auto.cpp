#include <iostream>
#include <typeinfo>
using namespace std;

auto add(int a, int b) -> decltype(a + b)
{
    return a + b;
}

int main()
{
    auto x = add(10, 20.5);
    cout << x;
}