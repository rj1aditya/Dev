#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdlib>

#define SOCKET_PATH "/tmp/unix_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[256];

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

    // Step 4: Bind the socket to the file path
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 5: Listen for client connections
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on " << SOCKET_PATH << std::endl;

    while (true) {
        // Step 6: Accept a new client connection
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            perror("Accept failed");
            continue;
        }

        std::cout << "New client connected!" << std::endl;

        // Step 7: Fork a new process for the client
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            close(client_fd);
            continue;
        }

        if (pid == 0) {  // Child process
            close(server_fd);  // Child doesn't need the listening socket

            while (true) {
                memset(buffer, 0, sizeof(buffer));  // Clear buffer
                int bytes_read = read(client_fd, buffer, sizeof(buffer));

                if (bytes_read <= 0) {
                    std::cout << "Client disconnected. Child process exiting." << std::endl;
                    break;
                }

                std::cout << "Client: " << buffer << std::endl;

                // Step 8: Send response to client
                const char* response = "Hello from server!";
                send(client_fd, response, strlen(response), 0);
            }

            close(client_fd);  // Close client socket in child
            exit(0);  // Terminate child process
        } else {
            close(client_fd);  // Parent process closes client socket
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
