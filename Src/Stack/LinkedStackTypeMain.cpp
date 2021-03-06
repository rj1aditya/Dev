#include"LinkedStacktype.h"
void testCopy(LinkedStackType<int> OStack);
int main()
{
	LinkedStackType<int> stack;
	LinkedStackType<int> otherStack;
	LinkedStackType<int> newStack;
//Add elements into stack
	stack.push(34);
	stack.push(43);
	stack.push(27);
//Use the assignment operator to copy the elements
//of stack into newStack
	newStack = stack;
	cout << "After the assignment operator, newStack: "
	<< endl;
//Output the elements of newStack
	while (!newStack.isStackEmpty())
	{
		cout << newStack.top() << endl;
		newStack.pop();	
	}
//Use the assignment operator to copy the elements
//of stack into otherStack
	otherStack = stack;
	cout << "Testing the copy constructor." << endl;
	testCopy(otherStack);
	cout << "After the copy constructor, otherStack: " << endl;
	while (!otherStack.isStackEmpty())
	{
		cout << otherStack.top() << endl;
		otherStack.pop();
	}
	return 0;
}


void testCopy(LinkedStackType<int> OStack)
{
	cout << "Stack in the function testCopy:" << endl;
	while (!OStack.isStackEmpty())
	{
		cout << OStack.top() << endl;
		OStack.pop();
	}
}