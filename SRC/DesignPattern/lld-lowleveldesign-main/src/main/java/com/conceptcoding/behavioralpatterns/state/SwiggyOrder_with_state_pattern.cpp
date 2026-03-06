#include <iostream>
#include <string>
using namespace std;

class OrderContext; // forward declaration

// ====================== STATE INTERFACE ======================
class OrderState
{
public:
    virtual void next(OrderContext *context) = 0;
    virtual void cancel(OrderContext *context) = 0;
    virtual string getStateName() = 0;
    virtual ~OrderState() {}
};

// Forward declarations for all states
class OrderPlacedState;
class PreparingState;
class OutForDeliveryState;
class DeliveredState;
class CancelledState;

// ====================== ORDER CONTEXT ======================
class OrderContext
{
private:
    OrderState *currentState;

public:
    OrderContext()
    {
        currentState = nullptr;
    }

    void setState(OrderState *state)
    {
        currentState = state;
    }

    void next()
    {
        currentState->next(this);
    }

    void cancel()
    {
        currentState->cancel(this);
    }

    string getCurrentState()
    {
        return currentState->getStateName();
    }
};

// ====================== ALL STATES - DECLARATIONS ======================

// ---------- ORDER PLACED ----------
class OrderPlacedState : public OrderState
{
public:
    void next(OrderContext *context) override;
    void cancel(OrderContext *context) override;
    string getStateName() override { return "ORDER_PLACED"; }
};

// ---------- PREPARING ----------
class PreparingState : public OrderState
{
public:
    void next(OrderContext *context) override;
    void cancel(OrderContext *context) override;
    string getStateName() override { return "PREPARING"; }
};

// ---------- OUT FOR DELIVERY ----------
class OutForDeliveryState : public OrderState
{
public:
    void next(OrderContext *context) override;
    void cancel(OrderContext *context) override;
    string getStateName() override { return "OUT_FOR_DELIVERY"; }
};

// ---------- DELIVERED ----------
class DeliveredState : public OrderState
{
public:
    void next(OrderContext *context) override;
    void cancel(OrderContext *context) override;
    string getStateName() override { return "DELIVERED"; }
};

// ---------- CANCELLED ----------
class CancelledState : public OrderState
{
public:
    void next(OrderContext *context) override;
    void cancel(OrderContext *context) override;
    string getStateName() override { return "CANCELLED"; }
};

// ====================== ALL STATES - IMPLEMENTATIONS ======================

void OrderPlacedState::next(OrderContext *context)
{
    context->setState(new PreparingState());
    cout << "Order is now being prepared.\n";
}

void OrderPlacedState::cancel(OrderContext *context)
{
    context->setState(new CancelledState());
    cout << "Order has been cancelled.\n";
}

void PreparingState::next(OrderContext *context)
{
    context->setState(new OutForDeliveryState());
    cout << "Order is out for delivery.\n";
}

void PreparingState::cancel(OrderContext *context)
{
    context->setState(new CancelledState());
    cout << "Order has been cancelled.\n";
}

void OutForDeliveryState::next(OrderContext *context)
{
    context->setState(new DeliveredState());
    cout << "Order has been delivered.\n";
}

void OutForDeliveryState::cancel(OrderContext *context)
{
    cout << "Cannot cancel. Order is out for delivery.\n";
}

void DeliveredState::next(OrderContext *context)
{
    cout << "Order is already delivered.\n";
}

void DeliveredState::cancel(OrderContext *context)
{
    cout << "Cannot cancel a delivered order.\n";
}

void CancelledState::next(OrderContext *context)
{
    cout << "Cancelled order cannot move to next state.\n";
}

void CancelledState::cancel(OrderContext *context)
{
    cout << "Order is already cancelled.\n";
}

// ====================== MAIN ======================
int main()
{
    OrderContext order;

    // Initialize first state
    order.setState(new OrderPlacedState());
    cout << "Current State: " << order.getCurrentState() << endl;

    order.next();   // preparing
    order.next();   // out for delivery
    order.cancel(); // fail
    order.next();   // delivered
    order.cancel(); // fail

    cout << "Final State: " << order.getCurrentState() << endl;
    return 0;
}