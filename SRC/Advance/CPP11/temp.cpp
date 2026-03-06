#include <iostream>
#include <functional>

class Counter {
    int value{};
public:
    // Functor: overload operator()
    void operator()(int step) {
        value += step;
        std::cout << "Counter value = " << value << '\n';
    }
};


int main() {
    Counter c;

    // Wrap the functor in std::function
    std::function<void(int)> f = c;

    // Call it like a normal function
    f(1);   // Counter value = 1
    f(5);   // Counter value = 6
    f(-2);  // Counter value = 4

    return 0;
}
