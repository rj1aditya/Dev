#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <algorithm>


class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;


    std::mutex mtx;
    std::condition_variable cv;
    bool stop;


    // --- Callback used as worker body (member function) ---
    void workerThread() {
        while (true) {
            std::function<void()> task;


            {
                std::unique_lock<std::mutex> lock(mtx);


                // wait until there is a task or stop is true
                cv.wait(lock, std::bind(&ThreadPool::waitPredicate, this));


                if (stop && tasks.empty())
                    return;


                task = std::move(tasks.front());
                tasks.pop();
            }


            // Execute task outside the lock
            task();
        }
    }


    // --- Callback used as predicate for condition_variable ---
    bool waitPredicate() {
        return stop || !tasks.empty();
    }


public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; i++) {
            // Start threads with member callback instead of lambda
            workers.emplace_back(&ThreadPool::workerThread, this);
        }
    }


    void submit(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }


    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        //std::for_each(workers.begin(), workers.end(), std::mem_fn(&std::thread::join));
        for (auto &t : workers)
            t.join();
    }
};

int main()
{
    ThreadPool td_pool(4);
   
    for(int i = 0; i < 10; i++)
    {
        td_pool.submit([i](){
        std::cout <<"Task"<<i<< " Running on thread: "<< std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10*i));
        });
    }
    return 0;
}
