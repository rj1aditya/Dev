#include<iostream>
using namespace std;


class Something
{
	public:
	Something()
	{
		cout<<"constr"<<endl;
	}
	
	Something( const Something &obj)
	{
		cout<<"copy constr"<<endl;
	}
};
 
Something foo() 
{
  Something s;
  return s;
}
 
int main()
{
  Something s = foo();
}