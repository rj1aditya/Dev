#include <iostream>
#include <string_view>
#include <array>
using namespace std;

bool containsRee(string_view str)
{
    return str.find("ree") != string_view::npos;
}

int main()
{
    auto lm = [](string_view str)
    { return str.find("ree") != string_view::npos; };
    array<string_view, 4> arr = {"one", "two", "three", "four"};

    // auto found(find_if(arr.begin(), arr.end(), containsRee));

    // using lambda function
    auto found(find_if(arr.begin(), arr.end(), lm));
    if (found != arr.end())
    {
        cout << "Found element:" << *found << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
    return 0;
}