#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/unix_socket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[256];

    // Step 1: Create a UNIX domain socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Step 3: Connect to the server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server! Type a message: " << std::endl;

    while (true) {
        std::cout << "You: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Step 4: Send data to server
        send(client_fd, buffer, strlen(buffer), 0);

        // Step 5: Receive response from server
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer));
        std::cout << "Server: " << buffer << std::endl;
    }

    close(client_fd);
    return 0;
}
