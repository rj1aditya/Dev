#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Node
{
    public:
    int key;
    int val;
    Node* left;
    Node* right;
    Node(int k, int v): key(k),val(v)
    {
        left = right = nullptr;
    }
};

class LRUCache {
    Node *tail;
    Node *head;
    unordered_map<int, Node*> map1;
    int cap;
    int size;
    void insert(Node *ptr)
    {
        if(head == nullptr)
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
        if(ptr->left == nullptr)
            head = ptr->right;
        else
        {
            ptr->left->right = ptr->right;
        }

        if(ptr->right == nullptr)
            tail = ptr->left;
        else
        {
            ptr->right->left = ptr->left;
        }

        ptr->left = nullptr;
        ptr->right = nullptr;
    }

    public:
    LRUCache(int s):cap(s)
    {
        head = tail = nullptr;
        size = 0;
    }
    /*Logic for Put function:
    ->if key already present then change the value of the key insert it at last
    ->if key not present
        Case1:if size== capacity then first value removed in LRU Cache
        Case2:if size!=capacity value inserted at last  
    */
    void put(int key, int value) 
    {
        Node *temp = new Node(key, value);

        if(map1.find(key) == map1.end())
        {
            if(cap == size)
            {
                map1.erase(head->key);
                delete_node(head);
                insert(temp);
            }
            else
            {
                size++;
                insert(temp);
            }
            map1[key] = temp;
        }
        else
        {
            Node* oldNode = map1[key];
            oldNode->val = value;
            delete_node(oldNode);
            insert(oldNode);
        }
    }

    /*
    Logic for get function:
    -> if key not found return -1
    ->if found then return val
    */
    int get(int key)
    {
        if(map1.find(key) == map1.end())
            return -1;
        else
        {
            Node *temp = map1[key];
            delete_node(temp);
            insert(temp);
            return temp->val;
        }
    }
};