#include <bits/stdc++.h>
using namespace std;

struct node
{
    int val;
    node *left;
    node *right;
    node(int v) : val(v)
    {
        left = nullptr;
        right = nullptr;
    }
};

using Node = node;
class Solution
{
    int cap;
    node *head;
    node *tail;
    unordered_map<int, node *> m;
    int pageFault;
    int currC;
    void insert_node(node *ptr)
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

    void delete_node(node *ptr)
    {
        if (ptr->left == nullptr)
            head = head->right;
        else
        {
            ptr->left->right = ptr->right;
        }

        if (ptr->right == nullptr)
            tail = tail->left;
        else
        {
            ptr->right->left = ptr->left;
        }

        ptr->left = ptr->right = nullptr;
    }

public:
    Solution()
    {
        head = tail = nullptr;
        pageFault = 0;
        currC = 0;
    }

    void pushback(int key)
    {
        /*
        if(currC == cap)
        {
            if(m.find(ele) != m.end())
            {
                node* temp = m[ele];
                delete_node(temp);
                insert_node(temp);
            }
            else
            {
                m.erase(head->val);
                delete_node(head);
                pageFault++;
                node* temp = new node(ele);
                insert_node(temp);
                m[ele] = temp;
            }
        }
        else
        {
            if(m.find(ele) != m.end())
            {
                node* temp = m[ele];
                delete_node(temp);
                insert_node(temp);
            }
            else{
                currC++;
                pageFault++;
                node* temp = new node(ele);
                insert_node(temp);
                m[ele] = temp;
            }
        }
        */
        if (m.find(key) == m.end())
        {
            pageFault++;
            Node *newN = new Node(key);

            if (currC == cap)
            {
                m.erase(head->val);
                delete_node(head);
                insert_node(newN);
            }
            else
            {
                currC++;
                insert_node(newN);
            }
            m[key] = newN;
        }
        else
        {
            Node *temp = m[key];
            delete_node(temp);
            insert_node(temp);
        }
    }

    int pageFaults(int N, int C, vector<int> pages)
    {
        // code here
        cap = C;
        // pageFault = C;

        for (int i = 0; i < N; i++)
        {
            pushback(pages[i]);
        }

        return pageFault;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int N = atoi(argv[1]);
    vector<int> v;

    int i = 0;
    for (i = 0; i < N; i++)
    {
        v.push_back(atoi(argv[i + 2]));
    }

    int C = atoi(argv[i + 2]);

    cout << C << endl;
    cout << N << endl;
    cout << v[N - 1];
    cout << s.pageFaults(i, C, v);
}