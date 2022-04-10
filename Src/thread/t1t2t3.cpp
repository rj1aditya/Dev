#include<iostream>
#include<thread>
#include<semaphore.h>
#include<string>


// print t1 -> then t2 then t3
// using semaphore is done
using namespace std;

sem_t t1;
sem_t t2;


void func1(string msg)
{
    cout<<msg<<endl;
    sem_post(&t1);
}
void func2(string msg)
{
    sem_wait(&t1);
    cout<<msg<<endl;
    sem_post(&t2);
}
void func3(string msg)
{
    sem_wait(&t2);
    cout<<msg<<endl;
}
int main()
{

    sem_init(&t1, 0, 0);
    sem_init(&t2, 0, 0);
    thread td3(func3, "thread 3");
    thread td2(func2, "thread 2");
    thread td1(func1, "thread 1");



    td1.join();
    td2.join();
    td3.join();
}