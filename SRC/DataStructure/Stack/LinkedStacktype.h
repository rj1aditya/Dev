#ifndef H_LinkedStackType
#define H_LinkedStackType
#include <iostream>
#include<string>
#include <cassert>
#include "StackADT.h"
using namespace std;

template <class type>	
class Data
{
	public:
	type data;
	Data<type> *next;
};

template <class type>
class LinkedStackType:public StackADT<type>
{
	Data<type> *stackTop;
	void copyStack( const LinkedStackType<type>& otherStack);
	
	public:
	
	bool isStackEmpty()const;
	bool isStackFull()const;
	void push( const type &dat );
	void pop();
	type top()const;
	void initializeStack();
	LinkedStackType();
	~LinkedStackType();
	LinkedStackType( const LinkedStackType<type>& otherStack);
	const LinkedStackType<type>& operator=( const LinkedStackType<type>& otherStack );
};

template <class type>
bool LinkedStackType<type>::isStackEmpty() const
{
	return ( stackTop == NULL );
}

template <class type>
bool LinkedStackType<type>::isStackFull() const
{
	return false;
}

//constructor
template <class type>
LinkedStackType<type>::LinkedStackType()
{
	stackTop = NULL;
}

//copy construct
template <class type>
LinkedStackType<type>::LinkedStackType(const LinkedStackType<type>& otherStack)
{
	stackTop = NULL;
	copyStack(otherStack);
}

//destructor
template <class type>
LinkedStackType<type>::~LinkedStackType()
{
	initializeStack();
}

template <class type>
const LinkedStackType<type>& LinkedStackType<type>::operator=(const LinkedStackType<type>& otherStack)
{
	if( this != &otherStack )
		copyStack(otherStack);
	
	return *this;
}

template <class type>
void LinkedStackType<type>::copyStack( const LinkedStackType<type>& otherStack)
{
	Data<type> *cur,*last,*newNode;
	
	if( stackTop != NULL )
		initializeStack();
	if( otherStack.stackTop == NULL )
		stackTop = NULL;
	else
	{
		cur = otherStack.stackTop;
		stackTop = new Data<type>;
		
		stackTop->data = cur->data;
		stackTop->next = NULL;
		
		last = stackTop;
		cur = cur->next;
		while( cur != NULL )
		{
			newNode = new Data<type>;
			newNode->data = cur->data;
			newNode->next = NULL;
			last->next = newNode;
			last = newNode;
			cur = cur->next;
		}
	}
}

template <class type>
void LinkedStackType<type>::push( const type &dat )
{
	Data<type> *newData = new Data<type>;
	
	newData->data = dat;
	newData->next = stackTop;
	stackTop = newData;	
}

template <class type>
type LinkedStackType<type>::top() const
{
	return stackTop->data;
}

template <class type>
void LinkedStackType<type>::pop()
{
	Data<type> *temp = stackTop;
	
	if( stackTop != NULL )
	{
		stackTop = stackTop->next;
		delete temp;
	}
}

template <class type>
void LinkedStackType<type>:: initializeStack()
{
	Data<type> *temp; //pointer to delete the node
	while (stackTop != NULL) //while there are elements inc the stack
	{
		temp = stackTop; //set temp to point to the
	//current node
		stackTop = stackTop->next; //advance stackTop to the
	//next node
		delete temp; //deallocate memory occupied by temp
	}
}
#endif