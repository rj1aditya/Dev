#include"MyStack.h"

void testCopyConstructor(stackType<int> otherStack);

int main()
{
	stackType<int> a(100);
	stackType<int> b(150);
	stackType<int> c(200);
	
	a.initializeStack();
	a.push(12);
	a.push(13);
	a.push(14);
	
	b = a;
	
	cout << "The elements of b: ";
	
	while (!b.isEmptyStack()) //print copyStack
	{
		cout << b.top() << " ";
		b.pop();
	}
	cout << endl;
	
	b = a;

	testCopyConstructor(a); //test the copy constructor
	if (!a.isEmptyStack())
		cout << "The original stack is not empty." << endl << "The top element of the original stack: ";
		cout << a.top() << endl;
	
}

void testCopyConstructor(stackType<int> otherStack)
{
	if (!otherStack.isEmptyStack())
		cout << "otherStack is not empty." << endl;
		cout << "The top element of otherStack: " << otherStack.top() << endl;
}