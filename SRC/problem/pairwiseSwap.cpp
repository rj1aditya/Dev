#include <bits/stdc++.h>
using namespace std;

class Node
{
    int data;
    public:
    Node *next;
    Node(int d):data(d)
    {
        next = nullptr;
    }
};
Node *pairWiseSwap(struct Node *head)
{
    Node *curr = head;
    bool visit = true;
    Node *pre_first = curr;
    while (curr != NULL)
    {
        Node *pre_last = curr;
        Node *t1 = NULL, *t2 = NULL;
        for (int i = 0; i < 2 && curr != NULL; i++)
        {
            t2 = curr->next;
            curr->next = t1;
            t1 = curr;
            curr = t2;
        }
        if (visit)
        {
            head = t1;
            visit = false;
        }
        else
        {
            pre_first->next = t1;
            pre_first = pre_last;
        }
    }
    return head;
}