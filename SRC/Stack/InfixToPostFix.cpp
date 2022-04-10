#include"LinkedStacktype.h"

int prec( char c )
{
	switch( c )
	{
		case '^':
		return 3;
		case '+':
		case '-':
		return 1;
		case '*':
		case '/':
		return 2;
		default:
		return -1;
	}
}

void infixToPostfix( string exp )
{
	LinkedStackType<char> st;
	st.push('N');
	int len = exp.length();
	string pos;
	
	for( int i = 0; i < len; i++ )
	{
		if( (exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z') )
			pos+=exp[i];
		else if( exp[i] == '(' )
			st.push( exp[i] );
		else if( exp[i] == ')' )
		{
			while( st.top() != 'N' && st.top() != '(' )
			{
				pos+=st.top();
				st.pop();
			}
			if( st.top() == '(' )
				st.pop();
		}
		else
		{
			while( st.top() != 'N' && prec( exp[i] ) <= prec(st.top()) )
			{
				pos+=st.top();
				st.pop();
			}
			st.push(exp[i]);
		}
		
	}
	while( st.top() != 'N' )
	{
		pos+=st.top();
		st.pop();
	}
	cout<<pos<<endl;
}

int main() 
{ 
    string exp = "a+b*(c^d-e)^(f+g*h)-i"; 
    infixToPostfix(exp); 
    return 0; 
} 