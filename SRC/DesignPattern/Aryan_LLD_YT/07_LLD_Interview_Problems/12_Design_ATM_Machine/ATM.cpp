#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

// ==================== ENUMS ====================

enum class TransactionType
{
    WITHDRAW_CASH,
    CHECK_BALANCE
};

enum class CashType
{
    BILL_100 = 100,
    BILL_50 = 50,
    BILL_20 = 20,
    BILL_10 = 10,
    BILL_5 = 5,
    BILL_1 = 1
};

static const vector<CashType> kCashTypesDesc = {
    CashType::BILL_100,
    CashType::BILL_50,
    CashType::BILL_20,
    CashType::BILL_10,
    CashType::BILL_5,
    CashType::BILL_1};

string cashTypeToString(CashType t)
{
    switch (t)
    {
    case CashType::BILL_100:
        return "100";
    case CashType::BILL_50:
        return "50";
    case CashType::BILL_20:
        return "20";
    case CashType::BILL_10:
        return "10";
    case CashType::BILL_5:
        return "5";
    case CashType::BILL_1:
        return "1";
    default:
        return "?";
    }
}

// ==================== UTILITY CLASSES ====================

class Account
{
private:
    string accountNumber;
    double balance;

public:
    Account(const string &number, double initialBalance)
        : accountNumber(number), balance(initialBalance) {}

    bool withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    void deposit(double amount) { balance += amount; }

    double getBalance() const { return balance; }
    const string &getAccountNumber() const { return accountNumber; }
};

class Card
{
private:
    string cardNumber;
    int pin;
    string accountNumber;

public:
    Card(const string &card, int pinCode, const string &acct)
        : cardNumber(card), pin(pinCode), accountNumber(acct) {}

    bool validatePin(int enteredPin) const { return pin == enteredPin; }
    const string &getAccountNumber() const { return accountNumber; }
};

class ATMInventory
{
private:
    unordered_map<CashType, int> cashInventory;

public:
    ATMInventory() { initializeInventory(); }

    void initializeInventory()
    {
        cashInventory[CashType::BILL_100] = 10;
        cashInventory[CashType::BILL_50] = 10;
        cashInventory[CashType::BILL_20] = 20;
        cashInventory[CashType::BILL_10] = 30;
        cashInventory[CashType::BILL_5] = 20;
        cashInventory[CashType::BILL_1] = 50;
    }

    int getTotalCash() const
    {
        int total = 0;
        for (auto &entry : cashInventory)
        {
            total += static_cast<int>(entry.first) * entry.second;
        }
        return total;
    }

    bool hasSufficientCash(int amount) const { return getTotalCash() >= amount; }

    map<CashType, int> dispenseCash(int amount)
    {
        if (!hasSufficientCash(amount))
            return {};

        map<CashType, int> dispensed;
        int remaining = amount;

        for (CashType type : kCashTypesDesc)
        {
            int denom = static_cast<int>(type);
            int available = cashInventory.count(type) ? cashInventory.at(type) : 0;
            int take = min(remaining / denom, available);
            if (take > 0)
            {
                dispensed[type] = take;
                remaining -= take * denom;
                cashInventory[type] -= take;
            }
        }

        if (remaining > 0)
        {
            // rollback
            for (auto &entry : dispensed)
            {
                cashInventory[entry.first] += entry.second;
            }
            dispensed.clear();
        }
        return dispensed;
    }

    void addCash(CashType type, int count) { cashInventory[type] += count; }
};

// ==================== STATE PATTERN ====================

class ATMMachineContext; // fwd

class ATMState
{
public:
    virtual ~ATMState() = default;
    virtual string getStateName() const = 0;
    virtual shared_ptr<ATMState> next(ATMMachineContext *context) = 0;
};

// Forward declarations of states
class IdleState;
class HasCardState;
class SelectOperationState;
class TransactionState;

class ATMStateFactory
{
private:
    ATMStateFactory() = default;

public:
    static ATMStateFactory &instance()
    {
        static ATMStateFactory factory;
        return factory;
    }

    shared_ptr<ATMState> createIdleState();
    shared_ptr<ATMState> createHasCardState();
    shared_ptr<ATMState> createSelectOperationState();
    shared_ptr<ATMState> createTransactionState();
};

class ATMMachineContext
{
private:
    shared_ptr<ATMState> currentState;
    shared_ptr<Card> currentCard;
    shared_ptr<Account> currentAccount;
    ATMInventory atmInventory;
    unordered_map<string, shared_ptr<Account>> accounts;
    TransactionType selectedOperation{};
    bool hasSelectedOperation{false};

public:
    ATMMachineContext()
    {
        currentState = ATMStateFactory::instance().createIdleState();
        cout << "ATM initialized in: " << currentState->getStateName() << endl;
    }

    // state progression
    void advanceState()
    {
        currentState = currentState->next(this);
        cout << "Current state: " << currentState->getStateName() << endl;
    }

    // operations
    void insertCard(const Card &card)
    {
        if (dynamic_pointer_cast<IdleState>(currentState))
        {
            cout << "Card inserted" << endl;
            currentCard = make_shared<Card>(card);
            advanceState();
        }
        else
        {
            cout << "Cannot insert card in " << currentState->getStateName() << endl;
        }
    }

    void enterPin(int pin)
    {
        if (dynamic_pointer_cast<HasCardState>(currentState))
        {
            if (currentCard && currentCard->validatePin(pin))
            {
                cout << "PIN authenticated successfully" << endl;
                currentAccount = accounts[currentCard->getAccountNumber()];
                advanceState();
            }
            else
            {
                cout << "Invalid PIN. Please try again" << endl;
            }
        }
        else
        {
            cout << "Cannot enter PIN in " << currentState->getStateName() << endl;
        }
    }

    void selectOperation(TransactionType type)
    {
        if (dynamic_pointer_cast<SelectOperationState>(currentState))
        {
            cout << "Selected operation: " << (type == TransactionType::WITHDRAW_CASH ? "WITHDRAW_CASH" : "CHECK_BALANCE") << endl;
            selectedOperation = type;
            hasSelectedOperation = true;
            advanceState();
        }
        else
        {
            cout << "Cannot select operation in " << currentState->getStateName() << endl;
        }
    }

    void performTransaction(double amount)
    {
        if (!dynamic_pointer_cast<TransactionState>(currentState))
        {
            cout << "Cannot perform transaction in " << currentState->getStateName() << endl;
            return;
        }

        try
        {
            if (selectedOperation == TransactionType::WITHDRAW_CASH)
            {
                performWithdrawal(amount);
            }
            else
            {
                checkBalance();
            }
            advanceState();
        }
        catch (const exception &ex)
        {
            cout << "Transaction failed: " << ex.what() << endl;
            currentState = ATMStateFactory::instance().createSelectOperationState();
        }
    }

    void returnCard()
    {
        if (dynamic_pointer_cast<HasCardState>(currentState) ||
            dynamic_pointer_cast<SelectOperationState>(currentState) ||
            dynamic_pointer_cast<TransactionState>(currentState))
        {
            cout << "Card returned to customer" << endl;
            resetATM();
        }
        else
        {
            cout << "No card to return in " << currentState->getStateName() << endl;
        }
    }

    void cancelTransaction()
    {
        if (dynamic_pointer_cast<TransactionState>(currentState))
        {
            cout << "Transaction cancelled" << endl;
            returnCard();
        }
        else
        {
            cout << "No transaction to cancel in " << currentState->getStateName() << endl;
        }
    }

    // helpers
    void addAccount(const shared_ptr<Account> &account)
    {
        accounts[account->getAccountNumber()] = account;
    }

    shared_ptr<Account> getAccount(const string &number)
    {
        auto it = accounts.find(number);
        if (it != accounts.end())
            return it->second;
        return nullptr;
    }

    // getters
    shared_ptr<ATMState> getCurrentState() const { return currentState; }
    shared_ptr<Card> getCurrentCard() const { return currentCard; }
    shared_ptr<Account> getCurrentAccount() const { return currentAccount; }
    ATMInventory &getATMInventory() { return atmInventory; }
    bool hasOperationSelected() const { return hasSelectedOperation; }
    TransactionType getSelectedOperation() const { return selectedOperation; }

    // reset
    void resetATM()
    {
        currentCard.reset();
        currentAccount.reset();
        hasSelectedOperation = false;
        currentState = ATMStateFactory::instance().createIdleState();
    }

private:
    void performWithdrawal(double amount)
    {
        if (!currentAccount)
            throw runtime_error("No account linked");
        if (!currentAccount->withdraw(amount))
            throw runtime_error("Insufficient funds in account");
        int amtInt = static_cast<int>(amount);
        if (!atmInventory.hasSufficientCash(amtInt))
        {
            currentAccount->deposit(amount);
            throw runtime_error("Insufficient cash in ATM");
        }
        auto dispensed = atmInventory.dispenseCash(amtInt);
        if (dispensed.empty())
        {
            currentAccount->deposit(amount);
            throw runtime_error("Unable to dispense exact amount");
        }
        cout << "Transaction successful. Please collect your cash:" << endl;
        for (auto &entry : dispensed)
        {
            cout << entry.second << " x $" << cashTypeToString(entry.first) << endl;
        }
    }

    void checkBalance()
    {
        if (!currentAccount)
            throw runtime_error("No account linked");
        cout << "Your current balance is: $" << currentAccount->getBalance() << endl;
    }
};

// ==================== STATE IMPLEMENTATIONS ====================

class IdleState : public ATMState
{
public:
    IdleState() { cout << "ATM is in Idle State - Please insert your card" << endl; }
    string getStateName() const override { return "IdleState"; }
    shared_ptr<ATMState> next(ATMMachineContext *context) override;
};

class HasCardState : public ATMState
{
public:
    HasCardState() { cout << "ATM is in Has Card State - Please enter your PIN" << endl; }
    string getStateName() const override { return "HasCardState"; }
    shared_ptr<ATMState> next(ATMMachineContext *context) override;
};

class SelectOperationState : public ATMState
{
public:
    SelectOperationState()
    {
        cout << "ATM is in Select Operation State - Please select an operation" << endl;
        cout << "1. Withdraw Cash" << endl;
        cout << "2. Check Balance" << endl;
    }
    string getStateName() const override { return "SelectOperationState"; }
    shared_ptr<ATMState> next(ATMMachineContext *context) override;
};

class TransactionState : public ATMState
{
public:
    TransactionState() { cout << "ATM is in Transaction State" << endl; }
    string getStateName() const override { return "TransactionState"; }
    shared_ptr<ATMState> next(ATMMachineContext *context) override;
};

// Factory methods
shared_ptr<ATMState> ATMStateFactory::createIdleState() { return make_shared<IdleState>(); }
shared_ptr<ATMState> ATMStateFactory::createHasCardState() { return make_shared<HasCardState>(); }
shared_ptr<ATMState> ATMStateFactory::createSelectOperationState() { return make_shared<SelectOperationState>(); }
shared_ptr<ATMState> ATMStateFactory::createTransactionState() { return make_shared<TransactionState>(); }

// State transitions
shared_ptr<ATMState> IdleState::next(ATMMachineContext *context)
{
    if (context->getCurrentCard())
    {
        return ATMStateFactory::instance().createHasCardState();
    }
    return ATMStateFactory::instance().createIdleState();
}

shared_ptr<ATMState> HasCardState::next(ATMMachineContext *context)
{
    if (!context->getCurrentCard())
        return ATMStateFactory::instance().createIdleState();
    if (context->getCurrentAccount())
        return ATMStateFactory::instance().createSelectOperationState();
    return ATMStateFactory::instance().createHasCardState();
}

shared_ptr<ATMState> SelectOperationState::next(ATMMachineContext *context)
{
    if (!context->getCurrentCard())
        return ATMStateFactory::instance().createIdleState();
    if (context->hasOperationSelected())
        return ATMStateFactory::instance().createTransactionState();
    return ATMStateFactory::instance().createSelectOperationState();
}

shared_ptr<ATMState> TransactionState::next(ATMMachineContext *context)
{
    if (!context->getCurrentCard())
        return ATMStateFactory::instance().createIdleState();
    return ATMStateFactory::instance().createSelectOperationState();
}

// ==================== MAIN (DEMO) ====================
int main()
{
    ATMMachineContext atm;
    atm.addAccount(make_shared<Account>("123456", 1000.0));
    atm.addAccount(make_shared<Account>("654321", 500.0));

    try
    {
        cout << "=== Starting ATM Demo ===" << endl;
        atm.insertCard(Card("123456", 1234, "654321"));
        atm.enterPin(1234);
        atm.selectOperation(TransactionType::WITHDRAW_CASH);
        atm.performTransaction(100.0);
        atm.selectOperation(TransactionType::CHECK_BALANCE);
        atm.performTransaction(0.0);
        atm.returnCard();
        cout << "=== ATM Demo Completed ===" << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
