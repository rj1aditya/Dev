#include<chrono>
#include<mutex>
#include<iostream>
#include<map>
#include<string>
#include<thread>
using namespace std;

class UserBucker
{
    std::chrono::steady_clock::time_point lastRefillTime;
    mutex mtx;
    int tokenLimit;
    int currentToken;
    int capacity;
    public:

    UserBucker(int tl, int cap)
    {
        tokenLimit = tl;
        capacity = cap;
        lastRefillTime = std::chrono::steady_clock::now();
        currentToken = cap;
    }

    void refill()
    {
        std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currTime-lastRefillTime).count();
        double tokens = (duration/1000)* tokenLimit;
        currentToken = min(capacity, int(currentToken+tokens));
        lastRefillTime = currTime;
    }

    bool allowRequest()
    {
        lock_guard<mutex> lg(mtx);
        refill();
        if(currentToken > 0)
        {
            currentToken--;
            return true;
        }
        return false;
    }
};


class RateLimiter
{
    map<int, UserBucker*> m;
    int cap;
    int tokenLimit;
    mutex mtx;
    public:

    RateLimiter(int c, int TL)
    {
        tokenLimit = TL;
        cap = c;
    }

    bool allowRequest(int userid)
    {
        lock_guard<mutex> lg(mtx);
        if(m.find(userid) == m.end())
        {
            m[userid] = new UserBucker(tokenLimit, cap);
        }
        return m[userid]->allowRequest();
    }
};

int main()
{
    RateLimiter rl(10, 10);
    for(int i = 0; i < 100; i++)
    {
        cout << rl.allowRequest(100) << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    return 0;
}