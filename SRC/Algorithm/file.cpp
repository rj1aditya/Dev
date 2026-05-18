#include<vector>
#include<algorithm>
#include <iostream>
#include<string>
using namespace std;

class Marker
{
    public:
    int price;
    string color;
};


class Invoice
{

    public:
    Marker m1;
    int quantity;
    Invoice(Marker m,int q)
    {
        m1=m;
        quantity=q;
    }
};


class InvoiceDAO
{
    Invoice i1;
    public:
    InvoiceDAO(const Invoice &i):i1(i)
    {
    }

    void saveToDB()
    {
        cout<<"Invoice saved to DB with marker price: "<<i1.m1.price<<" and color: "<<i1.m1.color<<" and quantity: "<<i1.quantity<<endl;
    }
};

int main()
{
    Marker m1{10,"red"};
    Invoice i1(m1,5);
    InvoiceDAO dao(i1);
    dao.saveToDB();
    return 0;   
}