

#include <bits/stdc++.h>
using namespace std;

class minHeap
{

public:
    minHeap *left, *right;
    char data;
    int freq;
    minHeap(char d, int f) : data(d), freq(f)
    {
        left = right = nullptr;
    }
};

struct comparator
{
    bool operator()(minHeap *l1, minHeap *l2)
    {
        return l1->freq > l2->freq;
    }
};

class Solution
{

    void generatesHuffmanCodes(minHeap *ptr, string str)
    {
        if (ptr == nullptr)
            return;

        if (ptr->data != '$')
            hcodes.push_back(str);

        generatesHuffmanCodes(ptr->left, str + "0");
        generatesHuffmanCodes(ptr->right, str + "1");
    }

public:
    vector<string> hcodes;
    vector<string> huffmanCodes(string S, vector<int> f, int N)
    {
        // Code here
        minHeap *left;
        minHeap *right;
        minHeap *top;

        priority_queue<minHeap *, vector<minHeap *>, comparator> pq;
        for (int i = 0; i < N; i++)
        {
            pq.push(new minHeap(S[i], f[i]));
        }

        while (pq.size() != 1)
        {
            left = pq.top();
            pq.pop();

            right = pq.top();
            pq.pop();

            top = new minHeap('$', left->freq + right->freq);
            top->right = right;
            top->left = left;

            pq.push(top);
        }

        generatesHuffmanCodes(pq.top(), "");
        return hcodes;
    }
};
