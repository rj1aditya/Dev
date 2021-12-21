#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
    Node *root{nullptr};
public:
    void insert(Node** p, int val)
    {
        if( *p == nullptr )
        {
            Node *ptr = new Node(val);
            *p = ptr;
            return;
            
        }
            
        
        if(val < (*p)->val)
            insert(&(*p)->left, val);
        else
            insert(&(*p)->right, val);

    }
    void insert1(int val)
    {
        insert(&root, val);
    }

    void connect1() {
        connect(root);
    }
    Node* connect(Node* root) {
        
        if(root == nullptr)
            return nullptr;
        
        queue<Node*> Q;
        // inserting root into the queue
        Q.push(root);
        
        while(!Q.empty())
        {
            int qSize = Q.size();
            Node* prev = nullptr;

            while(qSize-- > 0)
            {
                //
                Node* head = Q.front();
                head->next = prev;
                prev = head;
                Q.pop();
                
                
                if(head->left)
                    Q.push(head->left);
                if(head->right)
                    Q.push(head->right);
            }
        }
        return root;
        
    }
};


int main()
{
    Solution s;
    
    s.insert1(5);
    s.insert1(3);
    s.insert1(4);
    s.insert1(2);
    s.insert1(8);
    s.insert1(9);
    s.insert1(7);

    s.connect1();
}