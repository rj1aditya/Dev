#include<iostream>
using namespace std;

class superClass
{
	enum{
		integer,
		character,
		floater
	}vartype;
	
	union{
		int i;
		char c;
		float f;
	};
	public:
	superClass(char cc)
	{
		vartype = character;
		c = cc;
	}

	void print()
	{
		switch(vartype)
		{
			case character:
				cout<<c;
				break;
		}
	}
};

int main()
{
	superClass X('c');
	X.print();
	return 0;
}
