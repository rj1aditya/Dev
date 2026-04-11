#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    Node* next;
    Node* prev;
    int value;
    int key;
    chrono::steady_clock::time_point timestamp;
    
    Node(int k, int val, int ttl = 0)
    {
        key = k;
        value = val;
        timestamp = chrono::steady_clock::now() + chrono::seconds(ttl);
        next = prev = nullptr;
    }
};

class dll
{
    public:
    Node* head;
    Node* tail;
    dll()
    {
        head = tail = nullptr;
    }


    void insert_node(Node* ptr)
    {
        if(head == nullptr)
        {
            head = tail = ptr;
        }
        else
        {
            ptr->prev = tail;
            tail->next = ptr;
            tail = ptr;
        }
    }

    void delete_node(Node* ptr)
    {
        if(ptr->prev == nullptr)
        {
            head = head->next;
        }
        else
        {
            ptr->prev->next = ptr->next;
        }

        if(ptr->next == nullptr)
        {
            tail = tail->prev;
        }
        else
        {
            ptr->next->prev = ptr->prev;
        }

        ptr->next = ptr->prev = nullptr;
    }
};

class LRUCache {
    dll list;
    int cap;
    unordered_map<int, Node*> m;
    mutex mtx;
    thread td;
    atomic<bool> stop_thread = false;
    condition_variable cv;

    void background_nodes_cleaner()
    {
        while(stop_thread.load() == false)
        {
            
        }
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
        td = thread(&LRUCache::background_nodes_cleaner, this);
    }
    
    int get(int key) {
        lock_guard<mutex> lock(mtx);
        auto it = m.find(key);
        if(it == m.end())
            return -1;
        
        list.delete_node(it->second);
        list.insert_node(it->second);
        return it->second->value;
    }
    
    void put(int key, int value) {
        lock_guard<mutex> lock(mtx);
        auto it = m.find(key);
        if(it == m.end())
        {
            Node* newnode = new Node(key, value);
            if(m.size() == cap)
            {
                Node* lru = list.head;
                m.erase(lru->key);
                list.delete_node(lru);
            }

            m[key] = newnode;
            list.insert_node(newnode);
        }
        else
        {
            list.delete_node(it->second);
            list.insert_node(it->second);
            it->second->value = value;
        }
    }

    ~LRUCache()
    {
        stop_thread = true;
        td.join();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */