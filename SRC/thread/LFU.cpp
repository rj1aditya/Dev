#include <iostream>
#include <unordered_map>
#include <set>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace chrono;

/* ===================== Node ===================== */

struct Node {
    int key, value, freq;
    steady_clock::time_point expireAt;
    Node *prev, *next;

    Node(int k, int v, int ttl)
        : key(k), value(v), freq(1),
          expireAt(steady_clock::now() + milliseconds(ttl)),
          prev(nullptr), next(nullptr) {}
};

/* ===================== Doubly Linked List ===================== */

struct FreqList {
    Node *head = nullptr, *tail = nullptr;
    int size = 0;

    void pushBack(Node* node) {
        node->prev = tail;
        node->next = nullptr;
        if (tail) tail->next = node;
        else head = node;
        tail = node;
        size++;
    }

    void remove(Node* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        node->prev = node->next = nullptr;
        size--;
    }
};

/* ===================== LFU Cache ===================== */

class LFUCache {
    unordered_map<int, Node*> keyMap;
    unordered_map<int, FreqList*> freqMap;

    // multiset for expiry (ordered by expire time)
    multiset<pair<steady_clock::time_point, Node*>> expirySet;

    int capacity;
    int size;
    int minFreq;

    mutex mtx;
    condition_variable cv;
    bool stop;
    thread expiryThread;

public:
    LFUCache(int cap) : capacity(cap), size(0), minFreq(0), stop(false) {
        expiryThread = thread(&LFUCache::expiryWorker, this);
    }

    /* ===================== GET ===================== */
    int get(int key) {
        lock_guard<mutex> lock(mtx);

        auto it = keyMap.find(key);
        if (it == keyMap.end()) return -1;

        Node* node = it->second;
        if (steady_clock::now() >= node->expireAt) {
            evictNode(node);
            return -1;
        }

        touch(node);
        return node->value;
    }

    /* ===================== PUT ===================== */
    void put(int key, int value, int ttlMs) {
        if (capacity == 0) return;
        lock_guard<mutex> lock(mtx);

        if (keyMap.count(key)) {
            Node* node = keyMap[key];
            node->value = value;
            node->expireAt = steady_clock::now() + milliseconds(ttlMs);

            // erase old expiry entry and insert new
            expirySet.insert({node->expireAt, node});
            touch(node);
            cv.notify_one();
            return;
        }

        if (size == capacity) {
            evictLFU();
        }

        Node* node = new Node(key, value, ttlMs);
        keyMap[key] = node;
        minFreq = 1;

        if (!freqMap[1]) freqMap[1] = new FreqList();
        freqMap[1]->pushBack(node);

        expirySet.insert({node->expireAt, node});
        size++;
        cv.notify_one();
    }

private:
    /* ===================== Frequency Update ===================== */
    void touch(Node* node) {
        int f = node->freq;
        freqMap[f]->remove(node);

        if (freqMap[f]->size == 0) {
            delete freqMap[f];
            freqMap.erase(f);
            if (minFreq == f) minFreq++;
        }

        node->freq++;
        if (!freqMap[node->freq])
            freqMap[node->freq] = new FreqList();
        freqMap[node->freq]->pushBack(node);
    }

    /* ===================== Eviction ===================== */
    void evictNode(Node* node) {
        freqMap[node->freq]->remove(node);
        if (freqMap[node->freq]->size == 0) {
            delete freqMap[node->freq];
            freqMap.erase(node->freq);
        }
        keyMap.erase(node->key);
        delete node;
        size--;
    }

    void evictLFU() {
        FreqList* list = freqMap[minFreq];
        Node* victim = list->head;
        evictNode(victim);
    }

    /* ===================== Expiry Thread ===================== */
    void expiryWorker() {
        unique_lock<mutex> lock(mtx);

        while (!stop) {
            if (expirySet.empty()) {
                cv.wait(lock, [this]{ return stop || !expirySet.empty(); });
                continue;
            }

            auto it = expirySet.begin();
            auto [time, node] = *it;

            if (cv.wait_until(lock, time, [this, time]{ return stop || steady_clock::now() >= time; })) {
                if (stop) break;

                // stale check
                if (keyMap.count(node->key) && node->expireAt == time) {
                    evictNode(node);
                }
                expirySet.erase(it);
            }
        }
    }

public:
    /* ===================== Destructor ===================== */
    ~LFUCache() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_one();
        expiryThread.join();

        for (auto& [_, list] : freqMap) delete list;
        for (auto& [_, node] : keyMap) delete node;
    }
};