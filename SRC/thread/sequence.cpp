#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int counter = 1;
int turn = 0; // start with thread 0
mutex mtx;
condition_variable cv;

void func(int limit, int myTurn, int totalThreads)
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [myTurn, limit]()
                { return turn == myTurn || counter > limit; });

        if (counter > limit)
            break;

        cout << "Thread " << myTurn << " (id="
             << this_thread::get_id() << ") -> "
             << counter++ << endl;

        turn = (turn + 1) % totalThreads;
        cv.notify_one(); // wake only the next waiting thread
    }
}

int main()
{
    const int limit = 100;
    const int totalThreads = 3;

    thread td1(func, limit, 0, totalThreads);
    thread td2(func, limit, 1, totalThreads);
    thread td3(func, limit, 2, totalThreads);

    td1.join();
    td2.join();
    td3.join();

    return 0;
}