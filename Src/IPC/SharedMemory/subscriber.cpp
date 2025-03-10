#include <iostream>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 256
#define PORT 8080  // Port to receive socket notifications

int main() {
    // Step 1: Open shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // Step 2: Map shared memory
    char* shared_mem = (char*) mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Step 3: Create socket and connect to publisher
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    std::cout << "Subscriber: Connected to publisher, waiting for updates...\n";

    // Step 4: Wait for socket notifications
    char notify_buffer[10];
    while (true) {
        recv(sock, notify_buffer, sizeof(notify_buffer), 0);
        std::cout << "New message from publisher: " << shared_mem << std::endl;

        if (strcmp(shared_mem, "exit") == 0) break;
    }

    // Cleanup
    close(sock);
    munmap(shared_mem, SHM_SIZE);
    close(shm_fd);

    return 0;
}
