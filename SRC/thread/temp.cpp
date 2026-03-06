#include <thread>
#include <iostream>
#include<future>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<functional>
#include<vector>
using namespace  std;

class ThreadPool {
    queue<function<void()>> q;
    vector<thread> vthread;
    mutex mtx;
    condition_variable cv;
    bool stop = false;

    public:
    ThreadPool(int size) {
        stop = false;
        for (int i = 0; i < size; i++) {
            vthread.emplace_back(&ThreadPool::threadFunction, this);
        }

    }

    void threadFunction() {
        while (true) {
            function<void()> func;
            {
                unique_lock<mutex> lk(mtx);
                cv.wait(lk, [this]() {
                    return !q.empty() || stop;
                });

                if (stop && q.empty()) {
                    return;
                }

                func = std::move(q.front());
                q.pop();
            }
            func();
        }
    }

    void addNewTask(function<void()> task) {
        {
            lock_guard<mutex> lg(mtx);
            q.push(std::move(task));
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            lock_guard<mutex> lg(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto &t : vthread) {
            t.join();
        }
    }
};


int main() {

    ThreadPool obj(5);

    for (int i = 0; i < 5; i++) {
        obj.addNewTask([i](){
        std::cout <<"Task"<<i<< " Running on thread: "<< std::this_thread::get_id() << std::endl;
        });
    }
    return 0;
}