#include<iostream>
#include<chrono>
#include<thread>
#include<mutex>
#include<map>
using namespace std;

class RateLimiter {
private:
   UserBucket* globalBucket;
   unordered_map<int, UserBucket*> userBuckets;
   mutex m;


public:
   RateLimiter(int globalCap, double globalRate,
               int userCap, double userRate)
   {
       globalBucket = new UserBucket(globalCap, globalRate);
       // userBuckets created lazily
   }


   bool allowRequest(int userId) {
       // Step 1: check global limit
       if (!globalBucket->allowRequest())
           return false;


       lock_guard<mutex> lock(m);


       // Step 2: ensure user bucket exists
       if (userBuckets.find(userId) == userBuckets.end()) {
           userBuckets[userId] = new UserBucket(10, 10.0);
       }


       // Step 3: check per-user limit
       return userBuckets[userId]->allowRequest();
   }
};
