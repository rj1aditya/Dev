#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
using namespace std;

#define SOCKET_NAME "/tmp/DemoSocket"
#define BUFFER_SIZE 128


int main()
{
    int data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (data_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un name;
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path)-1);
    
    int ret = connect(data_socket, (const struct sockaddr*)&name, sizeof(struct sockaddr_un ));
    if (ret == -1) {
        fprintf(stderr, "The server is down.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    do
    {
        printf("Enter number to send to server :\n");
        scanf("%d", &i);
        ret = write(data_socket, &i, sizeof(int));
        if (ret == -1) {
            perror("write");
            break;
        }
        printf("No of bytes sent = %d, data sent = %d\n", ret, i); 
    }while(i);

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    ret = read(data_socket, buffer, BUFFER_SIZE);
    if (ret == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    /* Ensure buffer is 0-terminated. */

    buffer[BUFFER_SIZE - 1] = 0;

    printf("Result = %s\n", buffer);

    /* Close socket. */

    close(data_socket);

    exit(EXIT_SUCCESS);
}