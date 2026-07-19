#include <iostream>
#include <string>
#include <memory>
using namespace std;

class ATMStateContext; // forward declation

class ATMState
{
public:
    ATMState() = default;
    virtual ~ATMState() = default;
    virtual void next(ATMStateContext *context) = 0;
    virtual string getStateName() const = 0;
};

class IdealState;
class HasATMCardState;
class ProcessingState;
class TransactionState;

// Forward declarations for all state subclasses

class IdealState : public ATMState
{
public:
    IdealState() = default;

    virtual ~IdealState() override = default;

    void next(ATMStateContext *context) override;
    string getStateName() const override
    {
        return "IdealState";
    }
};

class HasATMCardState : public ATMState
{
public:
    HasATMCardState() = default;

    virtual ~HasATMCardState() override = default;

    void next(ATMStateContext *context) override;
    string getStateName() const override
    {
        return "HasATMCardState";
    }
};

class ProcessingState : public ATMState
{
public:
    ProcessingState() = default;

    virtual ~ProcessingState() override = default;

    void next(ATMStateContext *context) override;
    string getStateName() const override
    {
        return "ProcessingState";
    }
};

class TransactionState : public ATMState
{
public:
    TransactionState() = default;

    virtual ~TransactionState() override = default;

    void next(ATMStateContext *context) override;
    string getStateName() const override
    {
        return "TransactionState";
    }
};

class ATMStateContext
{
public:
    unique_ptr<ATMState> currentATMState;
    ATMStateContext()
    {
        currentATMState = make_unique<IdealState>();
    }

    void setState(unique_ptr<ATMState> newState)
    {
        currentATMState = std::move(newState); // Use std::move for unique_ptr
    }

    void next()
    {
        currentATMState->next(this);
    }

    string getStateName() const
    {
        return currentATMState->getStateName();
    }

    ~ATMStateContext()
    {
    }
};

void IdealState::next(ATMStateContext *context)
{
    context->setState(make_unique<HasATMCardState>());
}

// HasATMCardState
void HasATMCardState::next(ATMStateContext *context)
{
    context->setState(make_unique<ProcessingState>());
}

void ProcessingState::next(ATMStateContext *context)
{
    context->setState(make_unique<TransactionState>());
}

void TransactionState::next(ATMStateContext *context)
{
    context->setState(make_unique<IdealState>());
}

int main()
{
    ATMStateContext atmContext;
    cout << atmContext.getStateName() << endl;
    atmContext.next();
    cout << atmContext.getStateName() << endl;
    atmContext.next();
    cout << atmContext.getStateName() << endl;
    atmContext.next();
    cout << atmContext.getStateName() << endl;
    atmContext.next();
    cout << atmContext.getStateName() << endl;
}