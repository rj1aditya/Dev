#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;

    fin.open("ReadingList.txt");

    char ch;

    fin >> ch;

    while( !fin.eof() )
    {
        cout<<ch;
        fin >> ch;
    }

    fin.close();

    cout<<"\n-----------------fin.get()-----------------\n";
    fin.open("ReadingList.txt");

    ch = fin.get();

    while( !fin.eof() )
    {
        cout<<ch;
        ch = fin.get();
    }

    fin.close();
    cout<<"\n-----------------store in string-----------------\n";
    fin.open("ReadingList.txt");
    string ss;
    fin >> ss;

    while( !fin.eof() )
    {
        cout<<ss;
        fin >> ss;
    }

    fin.close();

    return 0;

}