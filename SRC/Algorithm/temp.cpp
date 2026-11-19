#include <stdio.h>
#include<string>
#include<vector>
#include <sstream>
#include<iostream>
using namespace std;

int main()
{
    string data = "1 3 2 2 5 0 6 0 3 0 4 0";
    vector<string> tokens;
        stringstream ss(data);
        string token;

        while (ss >> token)
            tokens.push_back(token);
    
    for(auto t: tokens)
        cout << t << endl;
    return 0;
}