#include<iostream>
#include<vector>
#include<mutex>
#include<string>
#include<thread>
using namespace std;

class Singleton
{
    string value;
    Singleton(string str)
    {
        value = str;
    }

    static mutex m;
    static Singleton *singleton;
    public:

    static Singleton* getInstance(string);

    void getValue()
    {
        cout << value << endl;
    }
};

mutex Singleton::m;
Singleton *Singleton::singleton = nullptr;

Singleton* Singleton::getInstance(string v)
{
    m.lock();
    if(singleton == nullptr)
        singleton = new Singleton(v);
    m.unlock();
    return singleton;
}


void fun1()
{
    Singleton *inst = Singleton::getInstance("fin1");
    inst->getValue();
}

void fun2()
{
    Singleton *inst = Singleton::getInstance("fin2");
    inst->getValue();
}

int main()
{
    thread td1(fun1);
    thread td2(fun2);

    td1.join();
    td2.join();

    return 0;
}