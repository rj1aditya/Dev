#include<iostream>
#include<thread>
#include<functional>
#include<algorithm>
#include<mutex>
#include<condition_variable>
using namespace std;
class Application
{
    mutex mtx;
    condition_variable c_var;
    bool m_flag;
    public:
    Application()
    {
        m_flag = false;
    }

    void mainTask()
    {
        cout<<"Handshake\n";
        unique_lock<mutex> mutex1(mtx);
        c_var.wait(mutex1, bind(&Application::isDataLoaded, this));
        // c_var.wait(mlock, std::bind(&A::sig_e, this));
        cout<<"Wait is over going to do main task\n";
    }

    void loadXML()
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout<<"loading Data from xml\n"<<endl;
        lock_guard<mutex> guard(mtx);
        m_flag=true;
        c_var.notify_one();
    }

    bool isDataLoaded()
    {
        return m_flag;
    }
};

int main()
{
    Application obj;
    thread td1(&Application::mainTask, &obj);
    thread td2(&Application::loadXML, &obj);

    td1.join();
    td2.join();

    return 0;
}