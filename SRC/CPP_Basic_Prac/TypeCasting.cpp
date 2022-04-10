#include<iostream>
using namespace std;

class A
{
	public:
	int i;
	float f;
	char c;
};

class B
{
	public:
	int ii;
	float ff;
	char cc;
	A obj;
	char c[1000];
	char c_c[4000];
	void display(){
		cout<<obj.i<<" "<<obj.f<<" "<<obj.c<<" "<<endl;
	}
};

int main()
{
	B b,c,d;
	A *a;

	b.ii = 1;
	b.ff = 11.11;
        b.cc = 'c';

	a = (A*)(&b + sizeof(B) - sizeof(A));
	a->i = 10;
	a->f = 12.12;
	a->c = 'a';

	cout<<endl;
	cout<<" "<<a->i<<" "<<a->f<<" "<<a->c<<endl;
	b.display();
}	
