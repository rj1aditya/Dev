#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Product
{
    string name;
    double price;

public:
    Product(const string &n, double p) : name(n), price(p) {}
    double getPrice() const { return price; }
    void display() const
    {
        cout << "Product: " << name << ", Price: " << price << endl;
    }
};

class ProductCombo
{
    vector<Product> products;
    string name;

public:
    ProductCombo(const string &n) : name(n) {}

    void addProduct(const Product &product)
    {
        products.push_back(product);
    }

    double getPrice() const
    {
        double total = 0.0;
        for (auto &p : products)
        {
            total += p.getPrice();
        }
        return total;
    }

    void display() const
    {
        cout << "Combo: " << name << endl;
        for (const auto &p : products)
        {
            p.display();
        }
        cout << "Total Combo Price: " << getPrice() << endl;
    }
};

int main()
{
    Product p1("Laptop", 1000.0);
    Product p2("Mouse", 50.0);
    Product p3("Keyboard", 80.0);
    Product p4("Monitor", 300.0);
    Product p5("USB Drive", 20.0);
    Product p6("Headphones", 150.0);
    Product p7("Webcam", 70.0);
    Product p8("Speakers", 120.0);

    ProductCombo combo1("Office Setup");
    combo1.addProduct(p1);
    combo1.addProduct(p2);
    combo1.addProduct(p3);
    combo1.addProduct(p4);

    vector<void *> cart;
    vector<string> cartType;

    cart.push_back(&combo1);
    cartType.push_back("combo");
    cart.push_back(&p5);
    cartType.push_back("product");
    cart.push_back(&p6);
    cartType.push_back("product");
    cart.push_back(&p7);
    cartType.push_back("product");
    cart.push_back(&p8);
    cartType.push_back("product");

    double grandTotal = 0.0;
    for (int i = 0; i < cartType.size(); i++)
    {
        if (cartType[i] == "combo")
        {
            grandTotal += static_cast<ProductCombo *>(cart[i])->getPrice();
            static_cast<ProductCombo *>(cart[i])->display();
        }
        else
        {
            grandTotal += static_cast<Product *>(cart[i])->getPrice();
            static_cast<Product *>(cart[i])->display();
        }
    }
    cout << "Grand Total of Cart: " << grandTotal << endl;
}
