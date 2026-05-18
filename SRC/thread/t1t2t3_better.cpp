#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

mutex m;
condition_variable cv;
int counter = 1;
int turn = 1;
bool stop = false;

void func1()
{
    while(!stop && counter <= 100)
    {
        unique_lock<mutex> ulock(m);
        cv.wait(ulock, []() {
            return turn == 1 || counter > 100;
        });

        if(counter > 100)
        {
            cv.notify_all();
            return;
        }
        cout <<"thread1 Value="<<counter++<<endl;
        turn = 2;
        cv.notify_all();
        ulock.unlock();
    }    
}

void func2()
{
    while(!stop && counter <= 100)
    {
        unique_lock<mutex> ulock(m);
        cv.wait(ulock, []() {
            return turn == 2 || counter > 100;
        });

        if(counter > 100)
        {
            cv.notify_all();
            return;
        }
        cout <<"thread2 Value="<<counter++<<endl;
        turn = 3;
        cv.notify_all();
        ulock.unlock();
    }    
}

void func3()
{
    while(!stop && counter <= 100)
    {
        unique_lock<mutex> ulock(m);
        cv.wait(ulock, []() {
            return turn == 3 || counter > 100;
        });

        if(counter > 100)
        {
            cv.notify_all();
            return;
        }
        cout <<"thread3 Value="<<counter++<<endl;
        turn = 1;
        cv.notify_all();
        ulock.unlock();
    }    
}

int main()
{
    cout <<"Main Thread\n";
    thread td1(func1);
    thread td2(func2);
    thread td3(func3);

    td1.join();
    td2.join();
    td3.join();
}