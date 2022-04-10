#include<iostream>
using namespace std;

class stack
{
	public:
	class Data
	{	public:
		int *data;
		int top;
		int capacity;
		Data( int cap): capacity(cap)
		{
			top = -1;
			data = new int[capacity];
		}
	};

	Data *ptr;

	stack( int cap = 10 )
	{
		ptr = new Data(cap);
	}

	void push(int val)
	{
		if( (ptr->top+1) == ptr->capacity )
			cout<<"overflow"<<endl;
		else
		{
			ptr->top++;
			ptr->data[ptr->top] = val;
		}
	}
	
	void pop()
	{
		if( ptr->top == -1 )
			cout<<"underflow"<<endl;
		else
		{
			cout<<ptr->data[ptr->top]<<endl;
			ptr->top--;
		}
	}
};

int main()
{
	stack s;
	s.push(10);
	s.push(100);
	s.push(1000);
	s.push(10);
	s.push(100);
	s.push(1000);
	s.push(10);
	s.push(100);
	s.push(1000);
	s.push(10);
	s.push(100);
	s.push(1000);
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
}
