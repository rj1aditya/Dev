#include <iostream>
#include <pthread.h>
#include <thread>
#include <functional> // Required for std::mem_fn
using namespace std;

class Wallet
{
    int m_money;
    mutex m_mutex;

public:
    Wallet() : m_money(0) {}
    int getMoney() const { return m_money; }
    void addMoney(int money)
    {
        // m_mutex.lock();
        lock_guard<mutex> lock(m_mutex);
        for (int i = 0; i < money; i++)
        {
            m_money++;
        }
        // m_mutex.unlock();
    }
};

int testMultithreadedWallet()
{
    Wallet walletObject;
    std::vector<std::thread> threads;

    for (int i = 0; i < 5000; i++)
    {
        threads.push_back(thread(&Wallet::addMoney, &walletObject, 1000));
    }

    for_each(threads.begin(), threads.end(), mem_fn(&std::thread::join));

    return walletObject.getMoney();
}

int main()
{
    cout << testMultithreadedWallet() << endl;
    return 0;
}
