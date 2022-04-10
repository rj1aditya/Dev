#include<iostream>
using namespace std;

class A // just an example
{
    int x;
public:
    A(){ x = 4; }
    int getX() { return x; }
};

class B
{
    static A obj1;  // <- Problem happens here
public:
   // static void start();
	static void start()
	{
		int x = obj1.getX();
	}
};

A B::obj1;

int main()
{
    B::start();
}

