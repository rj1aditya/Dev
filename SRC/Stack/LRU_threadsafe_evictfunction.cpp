class NodeLazy
{
public:
    int key, val;
    NodeLazy *prev, *next;
    steady_clock::time_point expireAt;

    NodeLazy(int k, int v, int ttl_ms)
        : key(k), val(v), prev(nullptr), next(nullptr)
    {
        expireAt = steady_clock::now() + milliseconds(ttl_ms);
    }
};

class DLL
{
public:
    NodeLazy *head;
    NodeLazy *tail;

    DLL()
    {
        head = tail = nullptr;
    }

    void removeNode(NodeLazy *node)
    {
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        node->prev = node->next = nullptr;
    }

    void insertNode(NodeLazy *node)
    {
        node->prev = node->next = nullptr;

        if (!tail)
        {
            head = tail = node;
            return;
        }

        tail->next = node;
        node->prev = tail;
        tail = node;
    }
};

class LRUCacheLazyTTL
{
    int cap, size;
    DLL dll;
    unordered_map<int, NodeLazy *> mp;

    mutex mtx;
    thread cleaner;
    atomic<bool> stopFlag{false};

public:
    LRUCacheLazyTTL(int capacity)
        : cap(capacity), size(0)
    {
        cleaner = thread(&LRUCacheLazyTTL::cleanerLoop, this);
    }

    ~LRUCacheLazyTTL()
    {
        stopFlag = true;

        if (cleaner.joinable())
            cleaner.join();

        for (auto &[k, node] : mp)
            delete node;
    }

private:

    void evict(NodeLazy *node)
    {
        mp.erase(node->key);
        dll.removeNode(node);
        delete node;
        size--;
    }

    void cleanerLoop()
    {
        while (!stopFlag)
        {
            this_thread::sleep_for(seconds(10));

            lock_guard<mutex> lock(mtx);

            auto now = steady_clock::now();

            while (dll.head)
            {
                if (now >= dll.head->expireAt)
                    evict(dll.head);
                else
                    break;
            }
        }
    }

public:

    int get(int key)
    {
        lock_guard<mutex> lock(mtx);

        if (!mp.count(key))
            return -1;

        NodeLazy *node = mp[key];

        if (steady_clock::now() >= node->expireAt)
        {
            evict(node);
            return -1;
        }

        dll.removeNode(node);
        dll.insertNode(node);

        return node->val;
    }

    void put(int key, int value, int ttl_ms)
    {
        lock_guard<mutex> lock(mtx);

        if (cap == 0)
            return;

        if (mp.count(key))
        {
            NodeLazy *node = mp[key];

            node->val = value;
            node->expireAt = steady_clock::now() + milliseconds(ttl_ms);

            dll.removeNode(node);
            dll.insertNode(node);

            return;
        }

        if (size == cap)
            evict(dll.head);

        NodeLazy *node = new NodeLazy(key, value, ttl_ms);

        dll.insertNode(node);
        mp[key] = node;
        size++;
    }
};