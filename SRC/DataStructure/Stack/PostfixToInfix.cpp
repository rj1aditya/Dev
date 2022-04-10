#include"LinkedStacktype.h"

int isOprnd( char c )
{
	return ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) );
}

void PostfixToInfix( string exp )
{
	LinkedStackType<string> st;
	
	for( int i = 0; exp[i] != '\0'; i++ )
	{
		if( isOprnd( exp[i] ) )
		{
			string op(1, exp[i]);
			st.push( op );
		}
		else
		{
			string pos;
			string c1,c2;
			c1 = st.top();
			st.pop();
			c2 = st.top();
			st.pop();
			
			pos = "(" + c2 + exp[i] + c1 + ")";
			
			st.push( pos );
		}
	}
	cout <<st.top();
}

int main() 
{ 
    string exp = "ab*c+";
    PostfixToInfix(exp); 
    return 0; 
} 