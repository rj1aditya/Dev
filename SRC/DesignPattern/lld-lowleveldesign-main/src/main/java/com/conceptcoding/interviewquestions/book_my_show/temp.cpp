

#include<string>
#include<vector>
#include<iostream>
using namespace std;


class cart
{
    public:
    virtual void display() = 0;
    virtual double getPrice()= 0;
    virtual string getName() = 0;
};

class Product: public cart
{
	double price;
	string name;
	public:
	Product(int p, string n):price(p), name(n)
	{}
	
	void display()
	{
		cout << "Product name="<<name<< " Product Price="<< price<<endl;
	}
	
	double getPrice()
	{
		return price;
	}
	
	string getName()
	{
		return name;
	}
};

class comboProduct: public cart
{
	vector<cart*> vec;
	string comboName;
	public:
	comboProduct(string n):comboName(n)
	{}
	
	void addProduct(cart* p)
	{
		vec.push_back(p);
	}
	
	
	void display()
	{
        cout << "Combo name="<<comboName<<endl;
		for(int i = 0; i < vec.size(); i++)
			vec[i]->display();
	}
	
	double getTotalPrice()
	{
		double total = 0;
		for(int i = 0; i < vec.size(); i++)
			total += vec[i]->getPrice();
		
		return total;
	}

	double getPrice()
	{
		return 0.0;
	}
	
	string getName()
	{
		return "";
	}
};


int main()
{
	cart *p1 = new Product(100000, "Iphone");
	cart *p2 = new Product(1000, "EarPhone");
	cart *p3 = new Product(500, "MobileCase");
	cart *p4 = new Product(1500, "Battery");
	cart *p5 = new Product(200, "EarPlug");
	cart *p6 = new Product(1200, "EyeGlass");

	cart * cp1 = new comboProduct("mobile Accessiries");
	dynamic_cast<comboProduct*>(cp1)->addProduct(p2);
	dynamic_cast<comboProduct*>(cp1)->addProduct(p3);
	dynamic_cast<comboProduct*>(cp1)->addProduct(p5);
	
	vector<cart*> amazoncart;

	
	amazoncart.push_back(p1);

	amazoncart.push_back(p4);

	amazoncart.push_back(p6);

	amazoncart.push_back(cp1);

	
	
	for(int i  = 0; i < amazoncart.size(); i++)
	{
		amazoncart[i]->display();

	}
	return 0;
}