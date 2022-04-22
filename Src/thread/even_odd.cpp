#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;
/*
condition_variable c;
mutex m;
int count = 1;


bool checkeven()
{
    return count%2 == 0;
}
bool checkodd()
{
    return count%2 != 0;
}
void printOdd()
{
    for( ; count < 100; )
    {
        unique_lock<mutex> ul(m);
        // c.wait( ul, [](){ return count%2==1; } );
        c.wait(ul, checkodd);
        cout<<"From odd: "<<count<<endl;
        count++;

        c.notify_all();
    }
}

void printEven()
{
    for( ; count < 100; )
    {
        unique_lock<mutex> ul(m);
        // c.wait( ul, [](){ return count%2==0; } );
        c.wait(ul, checkeven);
        cout<<"From even: "<<count<<endl;
        count++;
        c.notify_all();
    }
}

int main()
{
    thread t1( printOdd );
    thread t2( printEven );
    t1.join();
    t2.join();
}


*/
condition_variable c;
mutex m;
int count = 1;

void printOdd()
{
    while (count < 100)
    {
        unique_lock<mutex> ul(m);
        c.wait(ul, []()
               { return count % 2 != 0; });
        cout << count << endl;
        count++;
        c.notify_all();
        ul.unlock();
    }
}

void printEven()
{
    while (count < 100)
    {
        unique_lock<mutex> ul(m);
        c.wait(ul, []()
               { return count % 2 == 0; });
        cout << count << endl;
        count++;
        c.notify_all();
        ul.unlock();
    }
}

int main()
{
    thread td1(printOdd);
    thread td2(printEven);

    td1.join();
    td2.join();

    return 0;
}

