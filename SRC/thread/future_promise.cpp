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



//get_future() returns a future object associated with the promise. The future object can be used to retrieve the value set by the promise once it is available. In this example, we use std::shared_future to allow multiple threads to access the same future object. Each thread calls get() on the shared_future to retrieve the value set by the promise, 
//which is 42 in this case.

//get() is a member function of the future class that retrieves the value set by the promise. If the value is not yet available, get() will block until it is. In this example, both threads will block until the promise sets the value to 42, 
//at which point they will both print the result.

//set_value() is a member function of the promise class that sets the value to be retrieved by the associated future. In this example, we call set_value(42) to set the value of the promise to 42, which will unblock any threads waiting 
//on the future to retrieve this value.