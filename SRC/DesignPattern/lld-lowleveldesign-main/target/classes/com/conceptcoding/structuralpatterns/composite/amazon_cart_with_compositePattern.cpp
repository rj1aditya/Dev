#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class CartItem
{
public:
    virtual double getPrice() const = 0;
    virtual void display() const = 0;
    virtual ~CartItem() = default;
};

class Product : public CartItem
{
    string name;
    double price;

public:
    Product(const string &n, double p) : name(n), price(p) {}
    double getPrice() const override { return price; }
    void display() const override
    {
        cout << "Product: " << name << ", Price: " << price << endl;
    }
};

class ProductCombo : public CartItem
{
    string comboName;
    vector<CartItem *> cart;

public:
    ProductCombo(const string &n) : comboName(n) {}

    void addProduct(Product *p)
    {
        cart.push_back(p);
    }

    string getName() const
    {
        return comboName;
    }

    void display() const override
    {
        for (auto it : cart)
        {
            it->display();
        }
    }

    double getPrice() const override
    {
        double totalPrice = 0.0;

        for (auto it : cart)
        {
            totalPrice += it->getPrice();
        }

        return totalPrice;
    }
};
int main()
{
    Product p1("Laptop", 1000.0);
    Product p2("Mouse", 50.0);
    Product p3("Keyboard", 80.0);

    Product p4("Iphone11", 300.0);
    Product p5("Airpods", 150.0);
    Product p6("Charger", 20.0);

    ProductCombo productCombo("PC");
    productCombo.addProduct(&p1);
    productCombo.addProduct(&p2);
    productCombo.addProduct(&p3);

    vector<CartItem *> cart;

    cart.push_back(&p4);
    cart.push_back(&p5);
    cart.push_back(&p6);
    cart.push_back(&productCombo);

    double total = 0;
    for (auto it : cart)
    {
        it->display();
        total += it->getPrice();
    }
    cout << "Total Cart Price: " << total << endl;
    return 0;
}
