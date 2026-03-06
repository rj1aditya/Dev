#include <iostream>

class Cents
{
private:
	int m_cents {};

public:
	Cents(int cents) 
    { 
        m_cents = cents; 
        std::cout<<"construcotr\n";
    }

	// add Cents + Cents using a friend function
	friend Cents operator+(const Cents &c1, const Cents &c2);

	int getCents() const { return m_cents; }

    Cents(const Cents& refe){
        std::cout<<"This is copy constructor\n";
    }
};

// note: this function is not a member function!
Cents operator+(const Cents &c1, const Cents &c2)
{
	// use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
	return Cents(c1.m_cents + c2.m_cents);
}

int main()
{
	Cents cents1{ 6 };
	Cents cents2{ 8 };
	Cents centsSum(cents1 + cents2); //Doubt What constructor or copy constructor will call here. // in execution non of them got called.
	std::cout << "I have " << centsSum.getCents() << " cents.\n";

	return 0;
}