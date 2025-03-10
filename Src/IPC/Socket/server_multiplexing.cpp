#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_PATH "/tmp/unix_socket"
#define MAX_CLIENTS 5

int main() {
    int server_fd, client_fd, max_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    fd_set master_set, read_set;

    // Step 1: Create a UNIX domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Remove old socket file if exists
    unlink(SOCKET_PATH);

    // Step 3: Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Step 4: Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Listen for client connections
    if (listen(server_fd, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on " << SOCKET_PATH << std::endl;

    // Step 6: Initialize the FD set
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    while (true) {
        read_set = master_set;

        // Step 7: Use select() to monitor multiple file descriptors
        if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0) {
            perror("Select error");
            break;
        }

        // Step 8: Check for new client connections
        if (FD_ISSET(server_fd, &read_set)) {
            client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            if (client_fd == -1) {
                perror("Accept failed");
                continue;
            }
            std::cout << "New client connected, FD: " << client_fd << std::endl;
            
            // Add new client to FD set
            FD_SET(client_fd, &master_set);
            if (client_fd > max_fd) max_fd = client_fd;
        }

        // Step 9: Check existing clients for data
        for (int fd = server_fd + 1; fd <= max_fd; fd++) {
            if (FD_ISSET(fd, &read_set)) {
                char buffer[256] = {0};
                int bytes_read = read(fd, buffer, sizeof(buffer));
                
                if (bytes_read <= 0) {
                    std::cout << "Client disconnected, FD: " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                } else {
                    std::cout << "Client " << fd << " says: " << buffer << std::endl;
                    send(fd, "Message received", 16, 0);
                }
            }
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
