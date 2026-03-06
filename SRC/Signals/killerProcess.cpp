#include <iostream>
#include <signal.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage:\nexename <pid>\n";
        return 1;
    }

    int pid = atoi(argv[1]);
    if (pid < 0)
    {
        cout << "Invalid pid\n";
        return 1;
    }

    cout << "Killing process with PID:" << pid << endl;
    kill(pid, SIGABRT);
    return 0;
}