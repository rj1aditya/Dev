
//Important this program not works in macos, linux is fine for this code

#include <iostream>
#include <thread>
#include <semaphore.h>
#include <string>

#include <mutex>
#include <condition_variable>
// print t1 -> then t2 then t3
// using semaphore is done
using namespace std;

sem_t t3;
sem_t t1;
sem_t t2;

void func1(string msg)
{
    int k = 10;
    while (k--)
    {
        sem_wait(&t1);
        cout << msg << endl;
        sem_post(&t2);
    }
}
void func2(string msg)
{
    int k = 10;
    while (k--)
    {
        sem_wait(&t2);
        cout << msg << endl;
        sem_post(&t3);
    }
}

void func3(string msg)
{
    int k = 10;
    while (k--)
    {
        sem_wait(&t3);
        cout << msg << endl;
        sem_post(&t1);
    }
}

int main()
{
    //thread id, shared between same process threads, intial values of thread
    sem_init(&t1, 0, 1);
    sem_init(&t2, 0, 0);
    sem_init(&t3, 0, 0);
    thread td3(func3, "thread 3");
    thread td2(func2, "thread 2");
    thread td1(func1, "thread 1");

    td1.join();
    td2.join();
    td3.join();

    sem_destroy(&t1);
    sem_destroy(&t2);
    sem_destroy(&t3);
}