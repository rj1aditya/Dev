#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>

#define PORT 8080 // Port number
#define BACKLOG 5 // Maximum pending connections

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    // Step 1: Create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Set socket options (Reuse address and port)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Step 3: Bind the socket to an IP and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Step 4: Listen for incoming connections
    if (listen(server_fd, BACKLOG) == -1)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    while (true)
    {
        // Step 5: Accept a new client connection
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_socket == -1)
        {
            perror("Accept failed");
            continue;
        }

        std::cout << "New client connected: " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;

        // Step 6: Create a new process using fork() to handle multiple clients
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            close(new_socket);
            continue;
        }

        if (pid == 0)
        {                     // Child process
            close(server_fd); // Child does not need the listening socket

            while (true)
            {                                      // Handle multiple messages from the same client
                memset(buffer, 0, sizeof(buffer)); // Clear the buffer
                int bytes_read = read(new_socket, buffer, sizeof(buffer));

                if (bytes_read <= 0)
                {
                    std::cout << "Client disconnected. Child process exiting." << std::endl;
                    break;
                }

                std::cout << "Client: " << buffer << std::endl;

                const char *response = "Hello from server!";
                send(new_socket, response, strlen(response), 0);
            }

            close(new_socket); // Close client socket in child process
            exit(0);           // Terminate child process
        }
        else
        {
            close(new_socket); // Parent process does not need this socket
        }
    }

    close(server_fd);
    return 0;
}