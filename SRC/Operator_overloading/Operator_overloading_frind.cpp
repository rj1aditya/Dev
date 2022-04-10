#include<iostream>
using namespace std;

class Fraction
{
	int num, den;
	
	public:
	
	void round( int x, int y )
	{
		int gcd = Fraction::gcd_f( x, y );
		num/=gcd;
		den/=gcd;
	}
	
	Fraction( int i, int j ): num(i), den(j)
	{
		round(num,den);
	}
	
	static int gcd_f( int a, int b )
	{
		return (b == 0) ? (a > 0 ? a : -a) : gcd_f(b, a % b);
	}
	
	friend Fraction operator*(const Fraction &obj1,const Fraction &obj2)
	{
		return Fraction(obj1.num*obj2.num, obj1.den*obj2.den);
	}
	
	friend Fraction operator*(const Fraction &obj1, int x)
	{
		return Fraction(obj1.num*x, obj1.den);
	}
	
	friend Fraction operator*(int x, const Fraction &obj1)
	{
		return Fraction(obj1.num*x, obj1.den);
	}
	
	void print()
	{
		std::cout << num << "/" << den << "\n";
	}
};
 
int main()
{
    Fraction f1(2, 5);
    f1.print();
 
    Fraction f2(3, 8);
    f2.print();
 
    Fraction f3 = f1 * f2;
    f3.print();
 
    Fraction f4 = f1 * 2;
    f4.print();
 
    Fraction f5 = 2 * f2;
    f5.print();
	
	//Note:
	//1. Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4) to evaluate this compiler creates temp const obj,
	// and if we are receiving this object in operator function as a non constant value then compiler will 
	// throw an error.
	
    Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
    f6.print();
 
    return 0;
}