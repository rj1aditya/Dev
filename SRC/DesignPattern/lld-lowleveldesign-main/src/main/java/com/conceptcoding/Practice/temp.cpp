#include<iostream>
#include<thread>
#include<mutex>
#include <cassert>
using namespace std;


class singleton
{
    private:
    static mutex mtx;
    static singleton* instance[2];
    char var;
    singleton(char x):var(x)
    {

    }

    public:
    static singleton* getinstance(char c, int id);

    void accessDB()
    {
        cout <<"DB Access\n"<<" var="<<var;
    }

    ~singleton()
    {

    }
    static void cleanup()
    {
        delete instance[0];
        delete instance[1];
    }
};

mutex singleton::mtx;
singleton* singleton::instance[2] = {nullptr, nullptr};

singleton* singleton::getinstance(char c, int id)
{
    assert(id >= 0 && id <= 1);
    lock_guard<mutex> lock(mtx);

    if(instance[id] == nullptr)
        instance[id] = new singleton(c);

    return instance[id];
}

void func(char x, int ti, int id)
{
    
    this_thread::sleep_for(chrono::milliseconds(ti));
    singleton* obj = singleton::getinstance(x, id);
    obj->accessDB();
}

int main()
{


    thread td1(func, 'A', 100, 1);
    thread td2(func, 'B', 100, 0);
    thread td3(func, 'C', 100, 0);
    //thread td4(func, 'D', 100, 9);
    td1.join();
    td2.join();
    td3.join();


    singleton::cleanup();
    return 0;
}