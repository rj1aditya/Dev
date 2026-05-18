class Node
{
    public:
    int key;
    int value;
    int freq;
    Node* left;
    Node* right;
    public:
    Node(int k, int v): key(k), value(v)
    {
        left = right = nullptr;
        freq = 1;
    }
};


class dll
{
    public:
    int currentfreq;
    Node *head, *tail;
    int size;

    dll()
    {
        size = 0;
        head = tail = 0;
        currentfreq = 0;
    }

    void insert_node(Node* ptr)
    {
        size++;
        if(head == nullptr)
        {
            head = tail = ptr;
        }
        else
        {
            tail->right = ptr;
            ptr->left = tail;
            tail = ptr;
        }
    }

    void delete_node(Node* ptr)
    {
        size--;

        if(ptr->left == nullptr)
        {
            head = ptr->right;
        }
        else
        {
            ptr->left->right = ptr->right;
        }

        if(ptr->right == nullptr)
        {
            tail = ptr->left;
        }
        else
        {
            ptr->right->left = ptr->left;
        }

        ptr->left = ptr->right = nullptr;
    }
};

class LFUCache {

    unordered_map<int, Node*> m;
    unordered_map<int, dll*> arr;
    int minfreq;
    int cap;

    void update(Node* ptr)
    {
        int freq = ptr->freq;
        //Node* temp = arr[freq];
        arr[freq]->delete_node(ptr);
        if(arr[freq]->size == 0)
        {
            if(minfreq == freq)
                minfreq++;
            arr.erase(freq);
        }
        ptr->freq++;

        if(arr.find(ptr->freq) == arr.end())
        {
            arr[ptr->freq] = new dll();
        }
        arr[ptr->freq]->insert_node(ptr);

    }
public:
    LFUCache(int capacity) {
        minfreq = 0;
        cap = capacity;
    }
    
    int get(int key) {
        if(m.find(key) == m.end())
            return -1;
        
        update(m[key]);
        return m[key]->value;
    }
    
    void put(int key, int value) {
        if(m.find(key) != m.end())
        {
            m[key]->value = value;
            update(m[key]);
        }
        else
        {
            if(m.size() == cap)
            {
                Node *temp = arr[minfreq]->head;
                m.erase(temp->key);
                arr[minfreq]->delete_node(temp);
            }

            Node* newnode = new Node(key, value);
            m[key] = newnode;
            minfreq = 1;
            if(arr.find(minfreq) == arr.end())
            {
                arr[minfreq] = new dll();
            }

            arr[minfreq]->insert_node(newnode);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */