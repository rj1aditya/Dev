#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<chrono>
// #include<lock_guard>


using namespace std;

class Singleton{
    private:
        static Singleton* _instance;
        static mutex mtx;
        Singleton(){}
    public:

    static Singleton* getInstance();

    void showMessage(){
        cout << "Singleton Instance Address: " << this << endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::_instance = nullptr;
mutex Singleton::mtx;
Singleton* Singleton::getInstance(){
    lock_guard<mutex> lock(mtx);
    // mtx.lock();
    if(_instance == nullptr){
        _instance = new Singleton();
    }
    // mtx.unlock();
    return _instance;
}

void foobar(){
    this_thread::sleep_for(chrono::milliseconds(100));
    Singleton* instance = Singleton::getInstance();
    instance->showMessage();
}

void foogar(){
    this_thread::sleep_for(chrono::milliseconds(100));
    Singleton* instance = Singleton::getInstance();
    instance->showMessage();
}

int main(){
    
    thread td1(foobar);
    thread td2(foogar); 
    td1.join();
    td2.join();
    return 0;
}

/*
problem in this code:
1. deadlock if program is interrupted between lock and unlock
2. copy constructor and assignment operator are not deleted, so multiple instances can be created by copying

*/