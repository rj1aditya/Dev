#include <iostream>
#include <future>
#include <thread>

int main() {
    std::promise<int> p;
    std::shared_future<int> sf = p.get_future().share();

    // Multiple threads can use the same shared_future
    auto worker = [](std::shared_future<int> f) {
        std::cout << "Result: " << f.get() << "\n";
    };

    std::thread t1(worker, sf);
    std::thread t2(worker, sf);

    p.set_value(42); // sets the value once

    t1.join();
    t2.join();
}