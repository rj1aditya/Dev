#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>

using namespace std;

int icount = 1;
condition_variable c;
mutex m;

void printNum(bool sig)
{

	//if (sig)
	//{
		while (icount < 100)
		{
			unique_lock<mutex> ulock(m);
			c.wait(ulock, [sig]()
				   { return icount % 2 == sig; });
			cout << this_thread::get_id() << "Thread id="<<sig<<" counter=" << icount << endl;
			icount++;
			c.notify_one();
		}
	//}
	//else
	// {
	// 	while (icount <= 100)
	// 	{
	// 		unique_lock<mutex> ulock(m);
	// 		c.wait(ulock, []()
	// 			   { return !(icount % 2); });
	// 		cout << this_thread::get_id() << " Even 	Thread	" << icount << endl;
	// 		icount++;
	// 		c.notify_one();
	// 	}
	// }
}

int main()
{
	thread even_thread(printNum, 0);
	thread odd_thread(printNum, 1);

	even_thread.join();
	odd_thread.join();
}