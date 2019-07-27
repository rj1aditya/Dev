#include"MyStack.h"
#include<string>
#include<fstream>

int main()
{
	stackType<string> stu(100);
	
	double gpa;
	double highestgpa;
	string name;
	
	ifstream in( "HighestGPA.txt" );
	
	in >> gpa >> name;
	
	highestgpa = gpa;
	
	while( in )
	{
		if( gpa > highestgpa )
		{
			stu.initializeStack();
			stu.push(name);
			highestgpa = gpa;
		}
		else if( gpa == highestgpa )
		{
			if( !stu.isFullStack() )
				stu.push(name);
		}
		
		in >> gpa >> name;
	}
	
	cout<<"HighestGPA is: "<< highestgpa <<" holding by following student: "<<endl;
	while( !stu.isEmptyStack() )
	{
		cout<<stu.top()<<endl;
		stu.pop();
	}
}
		
		