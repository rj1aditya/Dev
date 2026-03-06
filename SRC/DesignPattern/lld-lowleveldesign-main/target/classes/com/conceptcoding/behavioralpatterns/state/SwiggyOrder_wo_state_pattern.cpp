#include <bits/stdc++.h>
using namespace std;

class Order {
private:
    string state;

public:
    // Constructor initializes the state to ORDER_PLACED
    Order() {
        this->state = "ORDER_PLACED";
    }

    // Method to cancel the order
    // only allows cancellation if in ORDER_PLACED or PREPARING states
    void cancelOrder() {
        if (state == "ORDER_PLACED" || state == "PREPARING") {
            state = "CANCELLED";
            cout << "Order has been cancelled." << endl;
        } else {
            cout << "Cannot cancel the order now." << endl;
        }
    }

    // Method to move the order to the next state based on its current state
    void nextState() {
        if (state == "ORDER_PLACED") {
            state = "PREPARING";
        } else if (state == "PREPARING") {
            state = "OUT_FOR_DELIVERY";
        } else if (state == "OUT_FOR_DELIVERY") {
            state = "DELIVERED";
        } else {
            cout << "No next state from: " << state << endl;
            return;
        }
        cout << "Order moved to: " << state << endl;
    }

    // Getter for the state
    string getState() {
        return state;
    }
};

int main() {
    Order order;

    // Display initial state
    cout << "Initial State: " << order.getState() << endl;

    // Moving through states
    order.nextState(); // ORDER_PLACED -> PREPARING
    order.nextState(); // PREPARING -> OUT_FOR_DELIVERY
    order.nextState(); // OUT_FOR_DELIVERY -> DELIVERED

    // Attempting to cancel an order after it is out for delivery
    order.cancelOrder(); // Should not allow cancellation

    // Display final state
    cout << "Final State: " << order.getState() << endl;

    return 0;
}
















