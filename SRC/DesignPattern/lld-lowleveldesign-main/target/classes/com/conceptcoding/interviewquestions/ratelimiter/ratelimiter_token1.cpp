#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>

using namespace std;

class userBucket
{
    int capcacity;
    double tokenslimit;
    int currenttokens;
    std::chrono::steady_clock::time_point lastrefilltime;
    mutex mtx;

public:
    userBucket(int capcacity, double tokenslimit)
    {
        this->capcacity = capcacity;
        this->tokenslimit = tokenslimit;
        this->currenttokens = capcacity;
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
        if (currenttokens > 0)
        {
            currenttokens--;
            return true;
        }
        return false;
    }
};

class RateLimiter
{
    map<int, userBucket> userBuckets;
    mutex mtx;
    int cap;
    double tokenslimit;

public:
    RateLimiter(int capcacity, double tokenslimit)
    {
        this->cap = capcacity;
        this->tokenslimit = tokenslimit;
    }

    bool allowRequest(int userId)
    {
        lock_guard<mutex> lock(mtx);
        if (userBuckets.find(userId) == userBuckets.end())
        {
            userBuckets[userId] = userBucket(cap, tokenslimit);
        }
        return userBuckets[userId].allowRequest();
    }
};

int main()
{
}