#include <iostream>
#include <csignal>
#include <execinfo.h> // For backtrace functions
#include <cstdlib>
#include <unistd.h>

void signalHandler(int signum)
{
    std::cout << "\nReceived signal: " << signum << std::endl;

    // Step 1: Capture the backtrace
    void *buffer[10]; // Store up to 10 stack frames
    int size = backtrace(buffer, 10);

    // Step 2: Convert addresses to function names
    char **symbols = backtrace_symbols(buffer, size);
    if (symbols)
    {
        std::cout << "Stack trace (most recent calls first):\n";
        for (int i = 0; i < size; ++i)
        {
            std::cout << symbols[i] << std::endl;
        }
        free(symbols); // Free memory allocated by backtrace_symbols()
    }
    else
    {
        std::cerr << "Failed to retrieve backtrace symbols\n";
    }

    // Step 3: Exit safely
    exit(EXIT_FAILURE);
}

int main()
{
    // Register signal handler for crashes
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    std::cout << "Press 1 for SIGABRT, 2 for SIGTERM, 3 for SIGSEGV: ";
    int choice;
    std::cin >> choice;

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