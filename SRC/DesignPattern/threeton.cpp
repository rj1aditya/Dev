#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<semaphore.h>
#include<pthread.h>

using namespace  std;

mutex m;



class threeton
{
    static int objC;
    static threeton *objptr[3];
    threeton(const threeton& obj) = delete;
    threeton* operator=(const threeton &obj) = delete;
    threeton()
    {
        objC++;
        cout<<objC<<" object Created\n";
    }

    public:
    static threeton* getInstance(int objType=0)
    {
        if(objType < 1 || objType > 3)
        {
            cout<<"getInstance failed\n";
            return NULL;
        }
        m.lock();
        if(objptr[objType] == NULL)
        {
            objptr[objType] = new threeton();
        }
        m.unlock();
        return objptr[objType];
    }
};

int threeton::objC = 0;
threeton* threeton::objptr[3] = {NULL, NULL, NULL};

int main()
{
    threeton *obj1[6];
    obj1[0] = threeton::getInstance(1);
    obj1[1] = threeton::getInstance(1);
    obj1[2] = threeton::getInstance(1);
    obj1[3] = threeton::getInstance(2);
    obj1[4] = threeton::getInstance(1);
    obj1[5] = threeton::getInstance(3);
}