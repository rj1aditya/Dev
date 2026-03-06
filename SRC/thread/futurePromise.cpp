#include <iostream>
#include <thread>
#include <future>
using namespace std;

void producer(promise<int> &prom)
{
    cout << "Producer: calculating value..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // simulate work
    prom.set_value(42);                         // set the result
    cout << "Producer: value set!" << endl;
}

void consumer(future<int> &fut)
{
    cout << "Consumer: waiting for value..." << endl;
    int value = fut.get(); // blocks until value is ready
    cout << "Consumer: got value = " << value << endl;
}

int main()
{
    promise<int> prom;                   // create promise
    future<int> fut = prom.get_future(); // link future to promise

    thread t1(producer, ref(prom));
    thread t2(consumer, ref(fut));

    t1.join();
    t2.join();

    return 0;
}