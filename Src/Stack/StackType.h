/*#include<iostream>
#include<assert.h>
#include"/home/aditya/Dev/App/Src/Stack/StackADT.h"
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
*/

