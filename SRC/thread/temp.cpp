#include<vector>
#include<algorithm>
#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<map>
#include <chrono>
#include<semaphore>
#include<condition_variable>
#include <functional>
#include<queue>
#include <utility>
using namespace std;

class thread_pool
{
	int threadCnt;
	vector<thread> td_vec;
	bool flag;
	condition_variable cv;
	mutex m;
	queue<function<void()>> q;

	public:
	thread_pool(int thread_cnt)
	{
		threadCnt = thread_cnt;
		flag = false;
		for(int i = 0; i < threadCnt; i++)
		{
			td_vec.emplace_back(thread(&thread_pool::thread_worker, this));
		}
	}

	void thread_worker()
	{
		while(!flag || !q.empty())
		{
			function<void()> fn;
			{
				unique_lock<mutex> ul(m);
				cv.wait(ul, [this](){
					return !q.empty() > 0 || flag;
				});
				if(flag && q.empty())
				{
					cv.notify_all();
					return;
				}

				fn = std::move(q.front());
				q.pop();
			}
			fn();
		}
	}

	void addTask(function<void()> fn)
	{
		lock_guard<mutex> lg(m);
		q.push(fn);
		cv.notify_one();
	}

	~thread_pool()
	{
		{
			lock_guard<mutex> lg(m);
			flag = true;
			cv.notify_all();
		}

		for(auto &th: td_vec)
			th.join();
	}
};

int main()
{
	thread_pool thd_pool(10);

	for(int i = 1; i < 100; i++)
	{
		thd_pool.addTask([i](){
			this_thread::sleep_for(chrono::microseconds(i*1000));
			cout << "ThreadID="<<this_thread::get_id()<<" TaskID="<<i<<endl;
		});
	}
	return 0;
}

