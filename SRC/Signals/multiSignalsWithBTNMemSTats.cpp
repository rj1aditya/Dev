#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/resource.h>

#if defined(__linux__)
#include <malloc.h> // Linux (mallinfo/mallinfo2)
#elif defined(__APPLE__)
#include <sys/sysctl.h> // macOS (memory stats)
#endif

void printMemoryStats()
{
    std::cout << "\n🔹 Capturing Memory Statistics...\n";

#if defined(__linux__)
    // Read from /proc/self/status
    std::ifstream memFile("/proc/self/status");
    std::string line;
    while (std::getline(memFile, line))
    {
        if (line.find("VmSize:") != std::string::npos ||
            line.find("VmRSS:") != std::string::npos ||
            line.find("VmPeak:") != std::string::npos)
        {
            std::cout << line << std::endl;
        }
    }

    // Use mallinfo2() for newer glibc versions (2.33+)
    struct mallinfo2 mem_info = mallinfo2();
    std::cout << "Heap Memory Allocated: " << mem_info.uordblks / 1024 << " KB\n";
    std::cout << "Heap Memory Free: " << mem_info.fordblks / 1024 << " KB\n";

#elif defined(__APPLE__)
    // macOS: Get total memory
    int64_t memSize;
    size_t size = sizeof(memSize);
    sysctlbyname("hw.memsize", &memSize, &size, NULL, 0);
    std::cout << "Total Physical Memory: " << memSize / (1024 * 1024) << " MB\n";
#endif

    // Get max resident set size
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    std::cout << "🔹 Max Resident Set Size: " << usage.ru_maxrss << " KB\n";
}

void signalHandler(int signum)
{
    std::cout << "\n🚨 Received signal: " << signum << " - Capturing system state...\n";
    printMemoryStats();
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    for (int i = 0; i < 10000000; i++)
    {
        int *ptr = new int[1000000];
        // delete[] ptr;
    }
    std::cout << "Press 1 for SIGABRT, 2 for SIGSEGV: ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        abort();
    }
    else if (choice == 2)
    {
        int *ptr = nullptr;
        *ptr = 42;
    }

    return 0;
}