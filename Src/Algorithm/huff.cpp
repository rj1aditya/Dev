#include<bits/stdc++.h>
using namespace std;

struct Node
{
    char data;
    unsigned int freq;

    struct Node* left;
    struct Node* right;

    Node(int data, int freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
};

struct compare
{
    bool operator()(Node *left, Node *right)
    {
        return left->freq > right->freq;
    }
};

void printHeap(Node *top, string s)
{
    if(!top)
        return;
    
    if(top->data != '$' )
        cout<<top->data<<": "<<s<<endl;

    printHeap(top->left, s+"0");
    printHeap(top->right, s+"1");
}

void HuffmanCodes(char *arr, int *freq, int size)
{
    priority_queue<Node*, vector<Node*>, compare> q;

    Node *left, *right, *top;

    for(int i=0; i<size; i++)
        q.push(new Node(arr[i], freq[i]));
    
    while(q.size() != 1)
    {
        left = q.top();
        q.pop();
        right = q.top();
        q.pop();

        top = new Node('$', left->freq+right->freq);
        
        top->left = left;
        top->right = right;

        q.push(top);
    }

    printHeap(q.top(), "");
}

int main()
{

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 5, 9, 12, 13, 16, 45 };

	int size = sizeof(arr) / sizeof(arr[0]);

	HuffmanCodes(arr, freq, size);

	return 0;
}