#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

// =====================================================
// Forward declarations for State Pattern
// =====================================================
class ATM;
class ATMState;

// =====================================================
// Hardware Components (Mocks)
// =====================================================

class CardReader
{
public:
    string readCard()
    {
        cout << "[CardReader] Card inserted.\n";
        return "CARD123"; // mocked card number
    }
};

class Keypad
{
public:
    int getPIN()
    {
        cout << "[Keypad] Enter PIN: ";
        int pin;
        cin >> pin;
        return pin;
    }

    int getWithdrawalAmount()
    {
        cout << "[Keypad] Enter withdrawal amount: ";
        int amt;
        cin >> amt;
        return amt;
    }
};

class Screen
{
public:
    void showMessage(const string &msg)
    {
        cout << "[Screen] " << msg << endl;
    }
};

class CashDispenser
{
    int totalCash;

public:
    CashDispenser(int amount) : totalCash(amount) {}

    bool hasSufficientCash(int amount)
    {
        return totalCash >= amount;
    }

    void dispense(int amount)
    {
        cout << "[CashDispenser] Dispensing cash: " << amount << endl;
        totalCash -= amount;
    }
};

class ReceiptPrinter
{
public:
    void printReceipt(const string &details)
    {
        cout << "\n===== RECEIPT =====\n";
        cout << details << endl;
        cout << "===================\n";
    }
};

// =====================================================
// Bank Backend Simulation
// =====================================================

class BankAccount
{
    string accountNumber;
    int pin;
    int balance;

public:
    BankAccount(string acc, int p, int bal)
        : accountNumber(acc), pin(p), balance(bal) {}

    bool verifyPIN(int enteredPIN)
    {
        return enteredPIN == pin;
    }

    int getBalance()
    {
        return balance;
    }

    bool withdraw(int amount)
    {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }

    string getAccountNumber()
    {
        return accountNumber;
    }
};

class BankDatabase
{
    unordered_map<string, shared_ptr<BankAccount>> accounts;

public:
    BankDatabase()
    {
        // Dummy account
        accounts["CARD123"] = make_shared<BankAccount>("ACC001", 1234, 5000);
    }

    shared_ptr<BankAccount> getAccount(string cardNumber)
    {
        return accounts.count(cardNumber) ? accounts[cardNumber] : nullptr;
    }
};

// Forward declaration of ATM
class ATM;

// =====================================================
// ATM State Pattern Base Class
// =====================================================

class ATMState
{
public:
    virtual ~ATMState() = default;
    virtual void insertCard(ATM &atm) {}
    virtual void enterPIN(ATM &atm) {}
    virtual void showMenu(ATM &atm) {}
    virtual void withdrawCash(ATM &atm) {}
    virtual void checkBalance(ATM &atm) {}
    virtual void printReceipt(ATM &atm) {}
    virtual void returnCard(ATM &atm) {}
};

// =====================================================
// Concrete States (Implementations)
// =====================================================

class IdleState : public ATMState
{
public:
    void insertCard(ATM &atm) override;
};

class PinState : public ATMState
{
public:
    void enterPIN(ATM &atm) override;
};

class MenuState : public ATMState
{
public:
    void showMenu(ATM &atm) override;
};

class WithdrawState : public ATMState
{
public:
    void withdrawCash(ATM &atm) override;
};

class CheckBalanceState : public ATMState
{
public:
    void checkBalance(ATM &atm) override;
};

class ReceiptState : public ATMState
{
public:
    void printReceipt(ATM &atm) override;
};

class ReturnCardState : public ATMState
{
public:
    void returnCard(ATM &atm) override;
};

// =====================================================
// ATM Machine
// =====================================================

class ATM
{
    shared_ptr<ATMState> currentState;

public:
    CardReader cardReader;
    Keypad keypad;
    Screen screen;
    CashDispenser dispenser;
    ReceiptPrinter printer;
    BankDatabase bankDB;

    shared_ptr<BankAccount> currentAccount;
    int lastWithdrawAmount = 0;

    ATM() : dispenser(2000) {} // ATM has ₹2000

    void setState(shared_ptr<ATMState> state)
    {
        currentState = state;
    }

    void start();

    // State delegations
    void insertCard() { currentState->insertCard(*this); }
    void enterPIN() { currentState->enterPIN(*this); }
    void showMenu() { currentState->showMenu(*this); }
    void withdrawCash() { currentState->withdrawCash(*this); }
    void checkBalance() { currentState->checkBalance(*this); }
    void printReceipt() { currentState->printReceipt(*this); }
    void returnCard() { currentState->returnCard(*this); }
};

// =====================================================
// Concrete States (Implementation)
// =====================================================

void IdleState::insertCard(ATM &atm)
{
    atm.screen.showMessage("Please insert your card.");
    string cardNumber = atm.cardReader.readCard();

    atm.currentAccount = atm.bankDB.getAccount(cardNumber);
    if (!atm.currentAccount)
    {
        atm.screen.showMessage("Invalid card. Ejecting...");
        return;
    }

    atm.screen.showMessage("Card read successfully.");
    atm.setState(make_shared<PinState>());
}

void PinState::enterPIN(ATM &atm)
{
    int pin = atm.keypad.getPIN();

    if (!atm.currentAccount->verifyPIN(pin))
    {
        atm.screen.showMessage("Incorrect PIN. Card will be returned.");
        atm.setState(make_shared<ReturnCardState>());
        return;
    }

    atm.screen.showMessage("PIN verified successfully.");
    atm.setState(make_shared<MenuState>());
}

void MenuState::showMenu(ATM &atm)
{
    atm.screen.showMessage("1. Withdraw Cash");
    atm.screen.showMessage("2. Check Balance");
    atm.screen.showMessage("3. Exit");

    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        atm.setState(make_shared<WithdrawState>());
        break;
    case 2:
        atm.setState(make_shared<CheckBalanceState>());
        break;
    default:
        atm.screen.showMessage("Exiting...");
        atm.setState(make_shared<ReturnCardState>());
    }
}

void WithdrawState::withdrawCash(ATM &atm)
{
    int amount = atm.keypad.getWithdrawalAmount();

    // ATM insufficient
    if (!atm.dispenser.hasSufficientCash(amount))
    {
        atm.screen.showMessage("ATM has insufficient cash. Cancelling.");
        atm.setState(make_shared<ReturnCardState>());
        return;
    }

    // User insufficient
    if (!atm.currentAccount->withdraw(amount))
    {
        atm.screen.showMessage("Insufficient account balance. Cancelling.");
        atm.setState(make_shared<ReturnCardState>());
        return;
    }

    atm.lastWithdrawAmount = amount;
    atm.dispenser.dispense(amount);
    atm.screen.showMessage("Please collect your cash.");

    atm.setState(make_shared<ReceiptState>());
}

void CheckBalanceState::checkBalance(ATM &atm)
{
    atm.screen.showMessage("Your balance is: " + to_string(atm.currentAccount->getBalance()));
    atm.setState(make_shared<ReturnCardState>());
}

void ReceiptState::printReceipt(ATM &atm)
{
    atm.printer.printReceipt(
        "Account: " + atm.currentAccount->getAccountNumber() +
        "\nWithdrawal Amount: " + to_string(atm.lastWithdrawAmount));
    atm.setState(make_shared<ReturnCardState>());
}

void ReturnCardState::returnCard(ATM &atm)
{
    atm.screen.showMessage("Returning card... Thank you!");
    atm.currentAccount.reset();
    atm.setState(make_shared<IdleState>());
}

// =====================================================
// ATM Start Flow
// =====================================================

void ATM::start()
{
    setState(make_shared<IdleState>());

    while (true)
    {
        insertCard();
        if (!currentAccount)
            continue;

        enterPIN();
        if (!currentAccount)
            continue;

        while (true)
        {
            showMenu();

            if (dynamic_pointer_cast<ReturnCardState>(currentState))
                break;

            if (dynamic_pointer_cast<WithdrawState>(currentState))
            {
                withdrawCash();
            }

            if (dynamic_pointer_cast<CheckBalanceState>(currentState))
            {
                checkBalance();
            }

            if (dynamic_pointer_cast<ReceiptState>(currentState))
            {
                printReceipt();
            }
        }

        returnCard();
    }
}

// =====================================================
// MAIN
// =====================================================

int main()
{
    ATM atm;
    atm.start();
    return 0;
}