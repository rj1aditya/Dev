#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;
class Node
{
public:
	int data;
	int key;
	Node *right;
	Node *left;
	steady_clock::time_point expireAt;

	Node(int k, int d, int ttl_ms) : key(k), data(d)
	{
		right = left = nullptr;
		expireAt = steady_clock::now() + milliseconds(ttl_ms);
	}
};

class dll
{
public:
	Node *head;
	Node *tail;

public:
	dll()
	{
		head = tail = nullptr;
	}

	void insert_node(Node *ptr)
	{
		if (head == nullptr)
		{
			head = tail = ptr;
			return;
		}

		tail->right = ptr;
		ptr->left = tail;
		tail = ptr;
	}

	void delete_node(Node *ptr)
	{
		if (ptr->left == nullptr)
			head = head->right;
		else
			ptr->left->right = ptr->right;

		if (ptr->right == nullptr)
			tail = ptr->left;
		else
			ptr->right->left = ptr->left;

		ptr->left = ptr->right = nullptr;
	}
};

class LRUCache
{
	dll double_link_list;
	unordered_map<int, Node *> m;
	int cap;
	mutex mtx;
	thread cleaner;
	atomic<bool> stopFlag{false};

	void evict(Node *node)
	{
		double_link_list.delete_node(node);
		m.erase(node->key);
		delete node;
	}

public:
	LRUCache(int capacity)
	{
		cap = capacity;
		cleaner = thread(&LRUCache::cleaner_loop, this);
	}

	void cleaner_loop()
	{
		while (!stopFlag)
		{
			this_thread::sleep_for(seconds(10));
			lock_guard<mutex> lock(mtx);

			while (true)
			{
				Node *node = double_link_list.head;
				auto now = steady_clock::now();
				if (node == nullptr || now < node->expireAt)
					break;
				evict(node);
			}
		}
	}

	int get(int key)
	{
		if (m.find(key) == m.end())
			return -1;

		Node *node = m[key];
		if (steady_clock::now() >= node->expireAt)
		{
			evict(node);
			return -1;
		}

		double_link_list.delete_node(node);
		double_link_list.insert_node(node);

		return node->data;
	}

	void put(int key, int value)
	{
		if (m.find(key) == m.end())
		{
			Node *newnode = new Node(key, value, 1000); // TTL of 1000 ms
			if (m.size() == cap)
			{
				Node *lru = double_link_list.head;
				double_link_list.delete_node(lru);
				m.erase(lru->key);
				delete lru;
			}

			m[key] = newnode;
			double_link_list.insert_node(newnode);
		}
		else
		{
			Node *node = m[key];
			node->data = value;
			node->expireAt = steady_clock::now() + milliseconds(1000); // Reset TTL
			double_link_list.delete_node(node);
			double_link_list.insert_node(node);
		}
	}

	~LRUCache()
	{
		stopFlag = true;
		if (cleaner.joinable())
			cleaner.join();

		for (auto &[k, node] : m)
			delete node;
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */