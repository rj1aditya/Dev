#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;

class wrapper
{
    thread &d_thread;

    public:
    wrapper(thread &a):d_thread(a)
    {

    }

    ~wrapper()
    {
        if(d_thread.joinable())
        {
            d_thread.detach();
        }
    }
};

void func()
{
	int i=0;
	while(  1 ){
	cout<<i<<"bjp voitng counter"<<endl;
    sleep(5);
    }
}

int main()
{
	thread td1(func);

    wrapper obj(td1);

    cout<<"exiting"<<endl;

    
    return 0;
}