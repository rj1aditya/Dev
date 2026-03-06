#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;

class NodeLazy
{
public:
    int key, val;
    NodeLazy *prev, *next;
    steady_clock::time_point expireAt;

    NodeLazy(int k, int v, int ttl_ms)
        : key(k), val(v), prev(nullptr), next(nullptr)
    {
        expireAt = steady_clock::now() + milliseconds(ttl_ms);
    }
};

class LRUCacheLazyTTL
{
    int cap, size;
    NodeLazy *head, *tail;
    unordered_map<int, NodeLazy *> mp;
    mutex mtx;

    // Background cleaner
    thread cleaner;
    atomic<bool> stopFlag{false};

public:
    LRUCacheLazyTTL(int capacity)
        : cap(capacity), size(0), head(nullptr), tail(nullptr)
    {
        // Start background cleaner thread
        cleaner = thread(&LRUCacheLazyTTL::cleanerLoop, this);
    }

    ~LRUCacheLazyTTL()
    {
        stopFlag = true;
        if (cleaner.joinable())
            cleaner.join();

        for (auto &[k, node] : mp)
            delete node;
    }

private:
    void removeNode(NodeLazy *node)
    {
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        node->prev = node->next = nullptr;
    }

    void insertNode(NodeLazy *node)
    {
        if (!tail)
            head = tail = node;
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void evict(NodeLazy *node)
    {
        mp.erase(node->key);
        removeNode(node);
        delete node;
        size--;
    }

    // 🔁 Background cleaner loop
    void cleanerLoop()
    {
        while (!stopFlag)
        {
            this_thread::sleep_for(seconds(10));

            lock_guard<mutex> lock(mtx);

            auto now = steady_clock::now();

            // Since head is LRU (oldest), check from head forward
            while (head)
            {
                if (now >= head->expireAt)
                {
                    NodeLazy *expired = head;
                    evict(expired);
                }
                else
                {
                    // As soon as we find a non-expired node, stop
                    break;
                }
            }
        }
    }

public:
    int get(int key)
    {
        lock_guard<mutex> lock(mtx);

        if (!mp.count(key))
            return -1;

        NodeLazy *node = mp[key];

        if (steady_clock::now() >= node->expireAt)
        {
            evict(node);
            return -1;
        }

        removeNode(node);
        insertNode(node);
        return node->val;
    }

    void put(int key, int value, int ttl_ms)
    {
        lock_guard<mutex> lock(mtx);

        if (cap == 0)
            return;

        if (mp.count(key))
        {
            NodeLazy *node = mp[key];
            node->val = value;
            node->expireAt = steady_clock::now() + milliseconds(ttl_ms);
            removeNode(node);
            insertNode(node);
            return;
        }

        if (size == cap)
            evict(head);

        NodeLazy *node = new NodeLazy(key, value, ttl_ms);
        insertNode(node);
        mp[key] = node;
        size++;
    }
};