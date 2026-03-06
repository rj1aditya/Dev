#include<iostream>
#include<memory>
using namespace std;

class paymentGateway {
public:
    paymentGateway() = default;

    virtual void pay(int orderid, double amount) = 0;
    virtual ~paymentGateway() {
    }
};

class paymetUGateway: public paymentGateway {
    public:
    paymetUGateway() = default;

    void pay(int orderid, double amount) override {
        cout <<"Payment done for order id:"<<orderid<<" amount paid:"<<amount<<endl;
    }
};

class RazorPay {
public:
    RazorPay() = default;
    void RazorPayment(string invoiceId, double amount) {
        cout <<"Payment done through RazorPay for orderid:"<<invoiceId<<" amount paid:"<<amount<<endl;
    }
    ~RazorPay() {
        cout<<"RazorPay done"<<endl;
    }
};


class RazorPayAdaptor: public paymentGateway {
    shared_ptr<RazorPay> razorPay;
    public:
    RazorPayAdaptor() {
        razorPay = make_shared<RazorPay>();
    }

    void pay(int orderid, double amount) override {
        razorPay->RazorPayment(to_string(orderid), amount);
    }

    ~RazorPayAdaptor() {
        cout<<"RazorPayAdaptor done"<<endl;
    }
};

class Checkout {
    shared_ptr<paymentGateway> payment;
public:
    Checkout(shared_ptr<paymentGateway> ptr): payment(ptr) {}

    void checkout(int orderid, double amount) {
        payment->pay(orderid, amount);
    }

    ~Checkout() {
        cout<<"Checkout done"<<endl;
    }
};


int main() {
    Checkout chkout(make_shared<RazorPayAdaptor>());
    chkout.checkout(123, 120.3);
}