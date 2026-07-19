#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <algorithm>
using namespace std;

class userBucket {
    int capacity;
    double tokensPerSecond;
    double currentTokens;
    std::chrono::steady_clock::time_point lastRefillTime;
    mutex mtx;

public:
    userBucket(int c, double tokensPerSecond)
        : capacity(c),
          tokensPerSecond(tokensPerSecond),
          currentTokens(c),
          lastRefillTime(std::chrono::steady_clock::now()) {}

    void refill() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRefillTime).count();
        double tokensToAdd = (duration / 1000.0) * tokensPerSecond;
        currentTokens = std::min((double)capacity, currentTokens + tokensToAdd);
        lastRefillTime = now;
    }

    bool allowRequest() {
        lock_guard<mutex> lock(mtx);
        refill();
        if (currentTokens >= 1.0) {
            currentTokens -= 1.0;
            return true;
        }
        return false;
    }
};

enum class Apps {
    GET,
    POST,
    PUT,
    DELETE
};

class rateLimiter {
    map<int, map<Apps,userBucket*>> userBuckets;
    mutex mtx;
    int cap;
    double tokensPerSecond;

public:
    rateLimiter(int c, double tokensPerSecond)
        : cap(c), tokensPerSecond(tokensPerSecond) {}


    bool allowRequest(int userId, Apps app) {
        lock_guard<mutex> lock(mtx);
        if (userBuckets[userId].find(app) == userBuckets[userId].end()) {
           if (app == Apps::GET) {
                userBuckets[userId][app] = new userBucket(100, 100);   // 100 req/sec
            } else if (app == Apps::POST) {
                userBuckets[userId][app] = new userBucket(20, 20);     // 20 req/sec
            } else if (app == Apps::DELETE) {
                userBuckets[userId][app] = new userBucket(5, 5);       // 5 req/sec
            } else {
                // Default bucket if unknown API type
                userBuckets[userId][app] = new userBucket(10, 10);
            }
        }
        return userBuckets[userId][app]->allowRequest();
    }
};

int main() {
    rateLimiter rl(5, 1); // capacity = 5, refill rate = 1 token/sec
    for (int i = 0; i < 10; i++) {
        cout << rl.allowRequest(1, Apps::GET) << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}