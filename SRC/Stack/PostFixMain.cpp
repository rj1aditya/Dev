#include"LinkedStacktype.h"
#include<fstream>

void calculate( LinkedStackType<double>& st, char opera );
void calculate( LinkedStackType<double>& st, char opera )
{
	int  result;
	int count = 1;
	int oprnd1,oprnd2;
	
	
	oprnd1 = (int)st.top();
	st.pop();
	oprnd2 = (int)st.top();
	st.pop();
		
	switch( opera )
	{
		case '+':
		result = oprnd1 + oprnd2;
		st.push( result );
		case '-':
		result = oprnd1 - oprnd2;
		st.push( result );
		case '*':
		result = oprnd1 * oprnd2;
		st.push( result );
		case '/':
		result = oprnd1 / oprnd2;
		st.push( result );
		case '=':
		cout<<"output is: "<<st.top();
		st.pop();
		st.initializeStack();
	}
}

int main()
{
	char expr;
	LinkedStackType<double> st;
	
	ifstream in( "expression.txt" );
	
	in >> expr;
	
	while( in )
	{
		switch( expr )
		{
			case '+':
				calculate( st, '+' );
			case '-':
				calculate( st, '-' );
			case '*':
				calculate( st, '*' );
			case '/':
				calculate( st, '/' );
			default:
				st.push( expr );
		}
		in >> expr;
	}
}