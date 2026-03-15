#include<iostream>
#include<thread>
#include<unordered_map>
#include<chrono>
#include<condition_variable>
using namespace std;

class Node{
    public:
    int data;
    int key;
	chrono::steady_clock::time_point expiryTime;
    Node* right;
    Node* left;
    Node(int k, int d, int ttl): key(k), data(d){
        right = left = nullptr;
		
		expiryTime = chrono::steady_clock::now() + chrono::milliseconds(ttl);
    }
};

class dll{

    public:
    Node* head;
    Node* tail;
    dll()
    {
        head = tail = nullptr;
    }

    void insert_node(Node* temp)
    {

        if(head == nullptr)
        {
            head = tail = temp;
            return;
        }

        tail->right = temp;
        temp->left = tail;
        tail = temp;
    }

    void delete_node(Node* temp)
    {
        if(temp->left == nullptr)
            head = head->right;
        else
            temp->left->right = temp->right;

        if(temp->right == nullptr)
            tail = tail->left;
        else
            temp->right->left = temp->left;

        temp->left = temp->right = nullptr;
    }
};

class LRUCache {
    unordered_map<int, Node*> m;
    dll list;
    int cap;
    mutex mtx;
	bool stop;// = false;
	thread td;
	condition_variable cv;
public:
    LRUCache(int capacity) {
        stop = false;
        cap = capacity;
		td = thread(&LRUCache::nodesCleaner, this, 2000);
    }
    
	void nodesCleaner(int t){
		
		while(true)
		{
			this_thread::sleep_for(chrono::milliseconds(t));
			unique_lock<mutex> ul(mtx);
			cv.wait(ul, [this](){
				return m.size() > 0 || stop == true;
			});
			
			if(stop == true)
			{
				return;
			}
                        
            Node* curr = list.head;
            auto now = chrono::steady_clock::now();

            while(curr)
            {
                Node* next = curr->right;

                if(curr->expiryTime <= now)
                    evict(curr);
                else
                    break;

                curr = next;
            }
		}
	}
	
	void evict(Node* ptr)
	{
		m.erase(ptr->key);
		list.delete_node(ptr);
		delete ptr;
	}
	
    int get(int key) {
        lock_guard<mutex> lock(mtx);
        if(m.find(key) == m.end())
            return -1;
		
		if(m[key]->expiryTime <= chrono::steady_clock::now())
		{
			evict(m[key]);
			return -1;
		}

        list.delete_node(m[key]);
        list.insert_node(m[key]);
        return m[key]->data;
    }
    
    void put(int key, int value, int ttl) {
        lock_guard<mutex> lock(mtx);
        if(m.find(key) == m.end())
        {
            if(m.size() == cap)
            {
                Node* ptr = list.head;
                list.delete_node(ptr);
                m.erase(ptr->key);
                cout << "capped deleting node="<<ptr->data<<endl;
                delete ptr;
            }

            Node* temp = new Node(key, value, ttl);
            list.insert_node(temp);
            m[key] = temp;
        }
        else
        {
            Node* temp = m[key];
            temp->data = value;
			temp->expiryTime = chrono::steady_clock::now() + chrono::milliseconds(ttl);
            list.delete_node(temp);
            list.insert_node(temp);
        }
		cv.notify_one();
    }

    ~LRUCache() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        if(td.joinable())
            td.join();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

 int main()
 {
    return 0;
 }