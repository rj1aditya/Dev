#include<iostream>
using namespace std;

class Base
{
	public:
	static Base* create(int i);

	virtual ~Base()
	{
		cout<<"base class destructor"<<endl;
	}

	Base()
	{
		cout<<"Base class constructor"<<endl;
	}
	
	virtual void Display() = 0;
};

class D1: public Base
{
	public:
	D1()
	{
		cout<<"D1 class constructor"<<endl;
	}
	~D1()
	{
		cout<<"D1 class destructor called"<<endl;
	}
	void Display()
	{
		cout<<"D1 class"<<endl;
	}
};

class D2: public Base
{
	public:
	D2()
	{
		cout<<"D2 class constructor"<<endl;
	}
	~D2()
	{
		cout<<"D2 class destructor called"<<endl;
	}
	void Display()
	{
		cout<<"D2 class"<<endl;
	}
};

class D3: public Base
{
	public:
	D3()
	{
		cout<<"D3 class constructor"<<endl;
	}
	~D3()
	{
		cout<<"D3 class destructor called"<<endl;
	}
	void Display()
	{
		cout<<"D3 class"<<endl;
	}
};

Base* Base::create(int i)
{
		switch(i)
		{
			case 1:
			return new D1;
			case 2:
			return new D2;
			case 3:
			return new D3;
		}
}

class User
{
	Base *pbase;
	
	public:
	User():pbase(0)
	{
		int choice;
		cout << "Enter ID (1, 2 or 3): "; 
        cin >> choice;
		
		pbase = Base::create(choice);
	}
	~User()
	{
		delete pbase;
		pbase = 0;
	}
	
	void Action()
	{
		pbase->Display();
	}
};


int main()
{
	User *ptr = new User;
	ptr->Action();
	delete ptr;
}










