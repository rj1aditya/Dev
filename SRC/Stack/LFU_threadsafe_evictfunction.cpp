#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

/* ============================================================
   1️⃣ LRU CACHE WITH TTL (LAZY EXPIRY – NO BACKGROUND THREAD)
   ============================================================ */

class NodeLazy {
public:
    int key, val;
    NodeLazy *prev, *next;
    steady_clock::time_point expireAt;

    NodeLazy(int k, int v, int ttl_ms)
        : key(k), val(v), prev(nullptr), next(nullptr) {
        expireAt = steady_clock::now() + milliseconds(ttl_ms);
    }
};

class LRUCacheLazyTTL {
    int cap, size;
    NodeLazy *head, *tail;
    unordered_map<int, NodeLazy*> mp;
    mutex mtx;

public:
    LRUCacheLazyTTL(int capacity)
        : cap(capacity), size(0), head(nullptr), tail(nullptr) {}

    ~LRUCacheLazyTTL() {
        for (auto &[k, node] : mp)
            delete node;
    }

private:
    void removeNode(NodeLazy* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        node->prev = node->next = nullptr;
    }

    void insertNode(NodeLazy* node) {
        if (!tail) head = tail = node;
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void evict(NodeLazy* node) {
        mp.erase(node->key);
        removeNode(node);
        delete node;
        size--;
    }

public:
    int get(int key) {
        lock_guard<mutex> lock(mtx);

        if (!mp.count(key))
            return -1;

        NodeLazy* node = mp[key];

        if (steady_clock::now() >= node->expireAt) {
            evict(node);
            return -1;
        }

        removeNode(node);
        insertNode(node);
        return node->val;
    }

    void put(int key, int value, int ttl_ms) {
        lock_guard<mutex> lock(mtx);

        if (mp.count(key)) {
            NodeLazy* node = mp[key];
            node->val = value;
            node->expireAt = steady_clock::now() + milliseconds(ttl_ms);
            removeNode(node);
            insertNode(node);
            return;
        }

        if (size == cap)
            evict(head);

        NodeLazy* node = new NodeLazy(key, value, ttl_ms);
        insertNode(node);
        mp[key] = node;
        size++;
    }
};

/* ============================================================
   2️⃣ LRU CACHE WITH TTL + BACKGROUND EXPIRY WORKER THREAD
   ============================================================ */

class Node {
public:
    int key, val;
    Node *prev, *next;
    steady_clock::time_point expireAt;

    Node(int k, int v, int ttl_ms)
        : key(k), val(v), prev(nullptr), next(nullptr) {
        expireAt = steady_clock::now() + milliseconds(ttl_ms);
    }
};

class LRUCacheTTLWorker {
    int cap, size;
    Node *head, *tail;
    unordered_map<int, Node*> mp;

    priority_queue<
        pair<steady_clock::time_point, Node*>,
        vector<pair<steady_clock::time_point, Node*>>,
        greater<>
    > expiryHeap;

    mutex mtx;
    condition_variable cv;
    bool stop;
    thread worker;

public:
    LRUCacheTTLWorker(int capacity)
        : cap(capacity), size(0), head(nullptr), tail(nullptr), stop(false) {
        worker = thread(&LRUCacheTTLWorker::expiryWorker, this);
    }

    ~LRUCacheTTLWorker() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_one();
        worker.join();

        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

private:
    void removeNode(Node* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        node->prev = node->next = nullptr;
    }

    void insertNode(Node* node) {
        if (!tail) head = tail = node;
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void evict(Node* node) {
        mp.erase(node->key);
        removeNode(node);
        delete node;
        size--;
    }

    void expiryWorker() {
        unique_lock<mutex> lock(mtx);
        while (!stop) {
            if (expiryHeap.empty()) {
                cv.wait(lock);
                continue;
            }

            auto [expTime, node] = expiryHeap.top();
            if (steady_clock::now() < expTime) {
                cv.wait_until(lock, expTime);
                continue;
            }

            expiryHeap.pop();
            if (mp.count(node->key) &&
                steady_clock::now() >= node->expireAt) {
                evict(node);
            }
        }
    }

public:
    int get(int key) {
        lock_guard<mutex> lock(mtx);
        if (!mp.count(key))
            return -1;

        Node* node = mp[key];
        if (steady_clock::now() >= node->expireAt) {
            evict(node);
            return -1;
        }

        removeNode(node);
        insertNode(node);
        return node->val;
    }

    void put(int key, int value, int ttl_ms) {
        lock_guard<mutex> lock(mtx);

        if (mp.count(key)) {
            Node* node = mp[key];
            node->val = value;
            node->expireAt = steady_clock::now() + milliseconds(ttl_ms);
            expiryHeap.push({node->expireAt, node});
            removeNode(node);
            insertNode(node);
            cv.notify_one();
            return;
        }

        if (size == cap)
            evict(head);

        Node* node = new Node(key, value, ttl_ms);
        insertNode(node);
        mp[key] = node;
        size++;

        expiryHeap.push({node->expireAt, node});
        cv.notify_one();
    }
};

/* ============================================================
   TEST (Uncomment ONE at a time)
   ============================================================ */

// int main() {
//     cout << "Lazy TTL Cache\n";
//     LRUCacheLazyTTL cache(2);
//     cache.put(1, 10, 2000);
//     this_thread::sleep_for(seconds(3));
//     cout << cache.get(1) << endl; // -1 (expired)
// }

// int main() {
//     cout << "Worker TTL Cache\n";
//     LRUCacheTTLWorker cache(2);
//     cache.put(1, 10, 2000);
//     this_thread::sleep_for(seconds(3));
//     cout << cache.get(1) << endl; // -1 (expired automatically)
// }