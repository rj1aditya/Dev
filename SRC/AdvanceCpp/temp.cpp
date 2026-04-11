/*
Following is the class structure of the Node class:

class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        this->data = 0;
        next = NULL;
    }
    Node(int data)
    {
        this->data = data; 
        this->next = NULL;
    }
    Node(int data, Node* next)
    {
        this->data = data;
        this->next = next;
    }
};
*/
struct Compare {
    bool operator()(const pair<int, Node*>& a, const pair<int, Node*>& b) const {
        return a.first > b.first; // min-heap by int
    }
};

Node* mergeKLists(vector<Node*> &listArray){
    // Write your code here.
    priority_queue<pair<int, Node*>, vector<pair<int,Node*>>, Compare> pq;
    Node* dummy = new Node(-1);
    Node* temp = dummy;

    int n = listArray.size();
    for(int i = 0; i < n; i++)
    {
        Node* tmp = listArray[i];
        pq.push({tmp->data, tmp});
    }

    while(!pq.empty())
    {
        Node* tmp = pq.top().second;
        pq.pop();

        temp->next = tmp;
        temp = temp->next;
        if(tmp->next)
            pq.push({tmp->next->data, tmp->next});

    }

    return dummy->next;
}
