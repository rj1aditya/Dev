#include<iostream>
#include<string>
#include<vector>
using namespace std;

class cart{
	public:
	virtual void description()= 0;
	virtual int getprice() = 0;
};

class product: public cart
{
    string name;
    double price;
	public:
	product(string n, int p): name(n), price(p)
	{}

	void description()
	{
		cout << name << endl;
	}
	
	int getprice()
	{
		cout << "Price = "<< price << endl;
		return 0;
	}
};

class productcombo: public cart{
	vector<cart*> combo;
	public:
	void description()
	{
		//cout << name << endl;
		for(auto it: combo)
		{
			it->description();
			it->getprice();
		}
	}
	
	int getprice()
	{
		//cout << "Price = "<<price;

		return 0;
	}

	void addprouct(cart* c)
	{
		combo.push_back(c);
	}
};

int main(){
	cart* p1 = new product("macbook", 100000);
	cart* p2 = new product("iphone", 60000);
	cart* p3 = new product("airpods", 10000);
	cart* p4 = new product("mouse", 2000);
	cart* p5 = new product("keyboard", 2000);
	
	productcombo* combo1 = new productcombo();
	combo1->addprouct(p1);
	combo1->addprouct(p2);
	combo1->addprouct(p3);


	vector<cart*> cart;
	cart.push_back(combo1);
	cart.push_back(p4);
	cart.push_back(p5);


	for(auto it: cart)
	{
		it->description();
		it->getprice();
	}


	return 0;
}