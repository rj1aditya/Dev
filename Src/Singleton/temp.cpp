// CPP program to illustrate 
// Private Destructor 

#include <bits/stdc++.h> 
using namespace std; 

class Test { 
public: 
	Test() // Constructor 
	{ 
		cout << "Constructor called\n"; 
	} 
	~Test() // Private Destructor 
	{ 
		delete Test;
	} 
}; 

int main() 
{ 
	Test* t = (Test*)malloc(sizeof(Test)); 
	return 0; 
} 
