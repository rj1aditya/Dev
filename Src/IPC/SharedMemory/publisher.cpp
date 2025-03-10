#include <iostream>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE 256
#define PORT 8080  // Socket communication port

int main() {
    // Step 1: Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }
    ftruncate(shm_fd, SHM_SIZE); // Set size

    // Step 2: Map shared memory
    char* shared_mem = (char*) mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Step 3: Create a socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);

    std::cout << "Publisher: Waiting for subscriber to connect...\n";
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        return 1;
    }
    std::cout << "Subscriber connected!\n";

    // Step 4: Message loop
    while (true) {
        std::cout << "Enter message (type 'exit' to quit): ";
        std::string message;
        std::getline(std::cin, message);

        // Write to shared memory
        strcpy(shared_mem, message.c_str());

        // Notify subscriber via socket
        send(new_socket, "update", 6, 0);

        if (message == "exit") break;
    }

    // Cleanup
    close(new_socket);
    close(server_fd);
    munmap(shared_mem, SHM_SIZE);
    shm_unlink(SHM_NAME);

    return 0;
}
