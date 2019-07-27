#include<iostream>
using namespace std;

void func()
{
	class A
	{
		public:
		A()
		{
			cout<<"A is local call, it is constructor of it"<<endl;
		}
		
		void show()
		{
			cout<<"show time"<<endl;
		}
		
		static void fu()
		{
			cout<<"Static function inside a class"<<endl;
		}
	};
	
	A::fu();
	A a;
	a.show();
}

int main()
{
	func();
}
		
		