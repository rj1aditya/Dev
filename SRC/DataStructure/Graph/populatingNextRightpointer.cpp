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
public:
    void insert(Node *root, int val)
    {
        Node *ptr = new Node(val);
        if( root == nullptr )
            root = ptr;
        
        if(val < root->val)
            insert(root->left);
        else(val < root->val)
            insert(root->left);
    }
    Node* connect(Node* root) {
        
        if(root == nullptr)
            return nullptr;
        
        queue<Node*> Q;
        
        Q.push(root);
        
        while(!Q.empty())
        {
            int qSize = Q.size();
            Node* prev = nullptr;
            while(qSize-- > 0)
            {
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
    Node *root = nullptr;
    s.insert(root, 5);
    s.insert(root, 3);
    s.insert(root, 4);
    s.insert(root, 2);
    s.insert(root, 8);
    s.insert(root, 9);
    s.insert(root, 7);

    s.connect(v);
}