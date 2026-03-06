#include <iostream>
#include <csignal>
#include <cstdlib> // For abort()

void signalHandler(int signum)
{
    std::cout << "Received signal: " << signum << " - ";

    switch (signum)
    {
    case SIGABRT:
        std::cout << "SIGABRT (Abnormal termination)" << std::endl;
        break;
    case SIGTERM:
        std::cout << "SIGTERM (Termination request)" << std::endl;
        break;
    case SIGSEGV:
        std::cout << "SIGSEGV (Segmentation fault - invalid memory access)" << std::endl;
        std::cout << "Logging error and terminating safely..." << std::endl;
        exit(EXIT_FAILURE);
        break;
    default:
        std::cout << "Unknown signal" << std::endl;
    }
}

int main()
{
    // Step 1: Register signal handler
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGSEGV, signalHandler);

    std::cout << "Press 1 for SIGABRT, 2 for SIGTERM, 3 for SIGSEGV: ";
    int choice;
    std::cin >> choice;

    // Step 2: Generate signals for testing
    if (choice == 1)
    {
        abort(); // Raises SIGABRT
    }
    else if (choice == 2)
    {
        raise(SIGTERM); // Raises SIGTERM
    }
    else if (choice == 3)
    {
        int *ptr = nullptr;
        *ptr = 42; // Causes SIGSEGV (Segmentation fault)
    }

    std::cout << "Program running normally...\n";
    return 0;
}