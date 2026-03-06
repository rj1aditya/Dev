#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

static void sigAbrtSigHandler(int sig)
{
    cout << "Caught SIGABRT signal: " << sig << endl;
    exit(1);
}

int main()
{
    signal(SIGABRT, sigAbrtSigHandler);
    cout << "PID: " << getpid() << endl;
    int x = 0;
    cin >> x;
    return 0;
};