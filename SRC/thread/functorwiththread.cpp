#include <iostream>
#include <thread>
using namespace std;

// 1️⃣ Functor (callback)
class Callback {
public:
    void operator()(int value) {
        cout << "Callback called with value: " << value << endl;
    }
};


int main() {
    Callback cb;              // functor object
    thread t(cb, 10);     // pass callback to thread
    t.join();
    return 0;
}