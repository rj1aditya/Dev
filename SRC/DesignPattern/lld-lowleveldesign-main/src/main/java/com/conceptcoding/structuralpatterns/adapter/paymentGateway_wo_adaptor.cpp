#include <bits/stdc++.h>
using namespace std;

// Target Interface:
// Standard interface expected by the CheckoutService
class PaymentGateway
{
public:
    virtual void pay(string orderId, double amount) = 0;
    virtual ~PaymentGateway() {}
};

// Concrete implementation of PaymentGateway for PayU
class PayUGateway : public PaymentGateway
{
public:
    void pay(string orderId, double amount) override
    {
        cout << "Paid Rs. " << amount << " using PayU for order: " << orderId << endl;
    }
};

// Adaptee:
// An existing class with an incompatible interface//this class is not fit well in the payment gateway system
class RazorpayAPI
{
public:
    void makePayment(string invoiceId, double amountInRupees)
    {
        cout << "Paid Rs. " << amountInRupees << " using Razorpay for invoice: " << invoiceId << endl;
    }
};

// Client Class:
// Uses PaymentGateway interface to process payments
class CheckoutService
{
private:
    PaymentGateway *paymentGateway;

public:
    // Constructor injection for dependency inversion
    CheckoutService(PaymentGateway *paymentGateway)
    {
        this->paymentGateway = paymentGateway;
    }

    // Business logic to perform checkout
    void checkout(string orderId, double amount)
    {
        paymentGateway->pay(orderId, amount);
    }
};

int main()
{
    // Using PayU payment gateway to process payment
    CheckoutService checkoutService(new PayUGateway());
    checkoutService.checkout("12", 1780.0);
    return 0;
}
