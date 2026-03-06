#include<iostream>
#include<string>

using namespace std;

template<typename T>

class stack
{
	class Node
	{
		public:
		T *data;
		T *next;
		// Node()
		// {
			// cout<<"Coming hre"<<endl;
		// }
		Node(T *ptr, T *dat ): data(dat),next(ptr)
		{
			cout<<"Coming here"<<endl;
		}
		
		Node( const T &cobj )
		{
			cout<<"Coming Soon, Copy constr"<<endl;
		}
		
		T* operator=(const T &aobj )
		{
			cout<<"Coming Soon, Assign operator"<<endl;
		}
		void check()
		{
			cout<<"Coming in check"<<endl;
		}
	};
	
	Node *head;
	public:
	stack()
	{
		head = NULL;
	}
	stack(const stack &cobj);
	T* operator=(const stack &aobj);
	void push( T *ptr );
	void pop();
	void seek();
};

template<typename T>
void stack<T>::push( T *ptr )
{
	Node *temp = new Node;
	temp->data = ptr;
	head = temp;
	temp->check();
}

int main()
{
	stack<int> s;
	cout<<"#################Program execution has kick off#################"<<endl;
	cout<<endl;
	cout<<"Size of stack object is: "<<sizeof(s)<<endl;
	s.push( new int(10) );
}