#include<iostream>
#include<chrono>
#include<thread>
#include<mutex>
#include<map>
using namespace std;

class userBucket
{
    int capcacity;
    double tokenslimit;
    int currenttokens;
    std::chrono::steady_clock::time_point lastrefilltime;
    mutex mtx;

    public:
    userBucket(int c, double tokenslimit)
    {
        this->capcacity = c;
        this->tokenslimit = tokenslimit;
        this->currenttokens = c;
        this->lastrefilltime = std::chrono::steady_clock::now();
    }

    void refill()
    {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastrefilltime).count();
        double tokensToAdd = (duration / 1000.0) * tokenslimit;
        currenttokens = min(capcacity, currenttokens + static_cast<int>(tokensToAdd));
        lastrefilltime = now;
    }

    bool allowRequest()
    {
        lock_guard<mutex> lock(mtx);
        refill();
        if(currenttokens > 0)
        {
            currenttokens--;
            return true;
        }
        return false;
    }
};

class rateLimiter
{
    //userId to userBucket mapping
    map<int, userBucket*> userBuckets;
    mutex mtx;
    int cap;
    double tokenslimit;
    public:
    rateLimiter(int c, double tokenslimit)
    {
        this->cap = c;
        this->tokenslimit = tokenslimit;
    }

    bool allowRequest(int userId)
    {
        lock_guard<mutex> lock(mtx);
        if(userBuckets.find(userId) == userBuckets.end())
        {
            userBuckets[userId] = new userBucket(cap, tokenslimit);
        }
        return userBuckets[userId]->allowRequest();
     }
};

int main()
{
    rateLimiter rl(5, 1);
    for(int i = 0; i < 10; i++)
    {
        cout << rl.allowRequest(1) << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}