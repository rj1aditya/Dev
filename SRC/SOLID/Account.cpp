#include <iostream>
#include <string>
using namespace std;

// Interface class
class ICalculateInterest
{
public:
    virtual double calculateInterest(double userBalance) = 0;
    virtual ~ICalculateInterest() {}
};

class savingAccountInterestCalculator : public ICalculateInterest
{
public:
    double calculateInterest(double userBalance)
    {
        return userBalance * 0.05;
    }
};

// If I wanted to extend the functionality of the salary account, I would create a
// new class that implements the ICalculateInterest interface.
class salaryAccountInterestCalculator : public ICalculateInterest
{
public:
    double calculateInterest(double userBalance)
    {
        return userBalance * 0.035;
    }
};

class currentAccountInterestCalculator : public ICalculateInterest
{
public:
    double calculateInterest(double userBalance)
    {
        return userBalance * 0.04;
    }
};

class Account
{
public:
    string userName;
    string userAddress;
    string userAccountType;
    double userBalance;
    ICalculateInterest *interestCalculator;
    Account(string name, string address, string accountType, double balance, ICalculateInterest *intCalculator)
    {
        userName = name;
        userAddress = address;
        userAccountType = accountType;
        userBalance = balance;
        this->interestCalculator = intCalculator;
    }

    ~Account()
    {
        delete interestCalculator;
    }

    double calculateInterest()
    {
        // Following code code follow SRP principle so commented it
        //  if(userAccountType == "Savings")
        //  {
        //      return userBalance * 0.05;
        //  }
        //  else if(userAccountType == "Current")
        //  {
        //      return userBalance * 0.02;
        //  }
        //  else
        //  {
        //      return 0;
        //  }
        return interestCalculator->calculateInterest(userBalance);
    }
};

int main()
{
    Account *account1 = new Account("John Doe", "123 Main St", "Savings", 1000, new savingAccountInterestCalculator());
    Account *account2 = new Account("Jane Doe", "456 Main St", "Salary", 2000, new salaryAccountInterestCalculator());
    Account *account3 = new Account("John Smith", "789 Main St", "Current", 3000, new currentAccountInterestCalculator());

    cout << "Interest for " << account1->userName << " is " << account1->calculateInterest() << endl;
    cout << "Interest for " << account2->userName << " is " << account2->calculateInterest() << endl;
    cout << "Interest for " << account3->userName << " is " << account3->calculateInterest() << endl;

    delete account1;
    delete account2;
    delete account3;
    return 0;
}