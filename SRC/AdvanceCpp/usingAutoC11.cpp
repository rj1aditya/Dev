#include <iostream>
using namespace std;
auto func(int x, int y) -> int
{
    return x + y;
}

int main()
{
    cout << func(10, 20);
    return 0;
}