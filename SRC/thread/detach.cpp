#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

class wrapper
{
    thread &d_thread;

public:
    wrapper(thread &a) : d_thread(a) {}
    ~wrapper()
    {
        if (d_thread.joinable())
        {

            d_thread.detach(); // safer than detach
        }
    }
};

void func()
{
    int i = 0;
    while (i < 5)
    { // run 5 times only for demo
        cout << i++ << " bjp voting counter" << endl;
        sleep(1);
    }
}

int main()
{
    thread td1(func);
    wrapper obj(td1);
    cout << "exiting main..." << endl;
    return 0;
}