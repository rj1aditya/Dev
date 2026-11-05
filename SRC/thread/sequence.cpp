#include<thread>
#include<iostream>
#include<queue>
#include<condition_variable>
#include<mutex>
#include<vector>
#include<functional>
#include <algorithm>
using namespace std;

class ThreadPool
{
    mutex m;
    vector<thread> td;
    int threadCount;
    queue<function<void()>> q;
    bool stop;
    condition_variable cv;

    public:
    ThreadPool(int c):threadCount(c), stop(false)
    {
        for(int i = 0; i < threadCount; i++)
        {
            td.emplace_back(thread(&ThreadPool::threadWorker, this));
        }
    }

    void threadWorker()
    {
        while(true)
        {
            function<void()> fn;
            unique_lock<mutex> ul(m);
            cv.wait(ul, bind(&ThreadPool::check, this));
            if(stop == true && q.empty())
            {
                return;
            }

            fn = std::move(q.front());
            q.pop();
            ul.unlock();
            fn();
        }
    }

    void addNewTask(function<void()> f)
    {
        m.lock();
        q.push(std::move(f));
        m.unlock();

        cv.notify_one();
    }

    bool check()
    {
        return stop || !q.empty();
    }

    ~ThreadPool()
    {
        m.lock();
        stop = true;
        m.unlock();
        cv.notify_all();
        for(auto &t: td)
            t.join();
    }
};


int main()
{
    ThreadPool obj(3);
    for(int i = 0; i < 100; i++)
    {
        obj.addNewTask([i](){
            cout << "Working thread id = "<<this_thread::get_id()<<" Task Counter = " << i <<endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        });
    }

    return 0;

}