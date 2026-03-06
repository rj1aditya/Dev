#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Step 1: Create the socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost

    // Step 3: Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection to server failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server. Type messages (type 'exit' to quit):" << std::endl;

    while (true)
    {
        std::cout << "You: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (strcmp(buffer, "exit") == 0)
        {
            break; // Exit loop if user types "exit"
        }

        // Step 4: Send message to server
        send(client_fd, buffer, strlen(buffer), 0);

        // Step 5: Receive response from server
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer));
        std::cout << "Server: " << buffer << std::endl;
    }

    // Step 6: Close the socket
    close(client_fd);
    return 0;
}