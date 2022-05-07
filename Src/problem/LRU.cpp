#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int val;
    int key;
    Node(int k, int v) : val(v), key(k)
    {
        left = right = NULL;
    }
};

class LRUCache
{

    int size;
    int cap;
    Node *head;
    Node *tail;
    unordered_map<int, Node *> m;

public:
    LRUCache(int capacity)
    {
        cap = capacity;
        size = 0;
        head = tail = nullptr;
    }
    void insert_node(Node *ptr)
    {
        if (head == nullptr)
            head = tail = ptr;
        else
        {
            tail->right = ptr;
            ptr->left = tail;
            tail = ptr;
        }
    }

    void delete_node(Node *ptr)
    {
        if (ptr->left == NULL)
            head = head->right;
        else
            ptr->left->right = ptr->right;

        if (ptr->right == NULL)
            tail = tail->left;
        else
            ptr->right->left = ptr->left;

        ptr->right = ptr->left = nullptr;
    }

    int get(int key)
    {
        if (m.find(key) == m.end())
            return -1;

        Node *ans = m[key];

        delete_node(ans);
        insert_node(ans);

        return ans->val;
    }

    void put(int key, int value)
    {
        if (m.find(key) == m.end())
        {
            Node *newN = new Node(key, value);

            if (size == cap)
            {
                m.erase(head->key);
                delete_node(head);
                insert_node(newN);
            }
            else
            {
                size++;
                insert_node(newN);
            }
            m[key] = newN;
        }
        else
        {
            Node *temp = m[key];
            temp->val = value;
            delete_node(temp);
            insert_node(temp);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */