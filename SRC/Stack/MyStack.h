#ifndef H_StackType
#define H_StackType
#include <iostream>
#include <cassert>
#include "StackADT.h"
using namespace std;

template <class type>
class stackType: public stackADT<type>
{
	private:
		int maxStackSize;
		int stackTop;
		type *list;
		
		//Function to make a copy of otherStack.
		void copyStack( const stackType<type> &otherStack );
	public:
		void initializeStack();
		bool isEmptyStack() const;
		bool isFullStack() const;
		void push( const type &newItem );
		type top() const;
		void pop();
		
		//Assignment operator overloading
		const stackType<type>& operator=(const stackType<type>&);
		
		stackType(int stackSize = 100 );
		
		//Copy constructor
		stackType(const stackType<type> &otherStack);
		
		~stackType();
};

template <class type>
stackType<type>::stackType( int stackSize )
{
	if (stackSize <= 0)
	{
		cout << "Size of the array to hold the stack must "<< "be positive." << endl;
		cout << "Creating an array of size 100." << endl;
		maxStackSize = 100;
	}
	else
		maxStackSize = stackSize; //set the stack size to
								  //the value specified by the parameter stackSize
		stackTop = 0;
		list = new type[maxStackSize];
}

template <class type>
stackType<type>::~stackType()
{
	delete []list;
}

template <class type>
void stackType<type>::initializeStack()
{
	stackTop = 0;
}//

template <class type>
bool stackType<type>::isEmptyStack() const
{
	return( stackTop == 0 );
}

template <class type>
bool stackType<type>::isFullStack() const
{
		return( stackTop == maxStackSize );
}

template <class type>	
void stackType<type>::push( const type &newItem )
{
	if (!isFullStack())
	{
		list[stackTop] = newItem; //add newItem at the top
		stackTop++; //increment stackTop
	}
	else
		cout << "Cannot add to a full stack." << endl;
}

template <class type>
type stackType<type>::top() const
{
	assert( (stackTop != 0) ); //if stack is empty terminate the program
	
	return list[ stackTop - 1 ];
}

template <class type>
void stackType<type>::pop()
{
	if (!isEmptyStack())
		stackTop--; //decrement stackTop
	else
		cout << "Cannot remove from an empty stack." << endl;
}

template <class type>
stackType<type>::stackType( const stackType<type>& otherStack)
{
	cout<<endl<<"COPYCONSTRUCTORCALL"<<endl;
	list = NULL;
	copyStack( otherStack );	
}

template <class type>
const stackType<type>& stackType<type>::operator=(const stackType<type>& otherStack)
{
	if (this != &otherStack) // avoid self copy
		copyStack( otherStack );
	return *this;
}

template <class type>
void stackType<type>::copyStack( const stackType<type> &otherStack )
{
	delete []list;
	
	maxStackSize = otherStack.maxStackSize;
	stackTop = otherStack.stackTop;
	list = new type[maxStackSize];
	
	for (int j = 0; j < stackTop; j++)
		list[j] = otherStack.list[j];
}

#endif