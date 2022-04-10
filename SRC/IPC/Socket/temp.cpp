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
    struct sockaddr_un sockName;
    int iRet = -1;
    unlink(SOCKET_NAME);
    int master_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if (master_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Master socket created\n");
    sockName.sun_family = AF_UNIX;
    strncpy(sockName.sun_path, SOCKET_NAME, sizeof(sockName.sun_path) -1 );

    iRet = bind(master_fd, (const struct sockaddr*)&sockName, sizeof(struct sockaddr_un));
    if (iRet == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    printf("bind() call succeed\n");

    iRet = listen(master_fd, 20);
    if (iRet == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int data_socket;
    int result;
    char buffer[BUFFER_SIZE];
    int data;
    while(1)
    {
        printf("Waiting on accept() sys call\n");
        data_socket = accept(master_fd, NULL, NULL);
        if (data_socket == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Connection accepted from client\n");
        result = 0;
        memset(buffer, '\0', BUFFER_SIZE);
        while(1)
        {
            iRet = read(data_socket, buffer, BUFFER_SIZE);
            if (iRet == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            memcpy(&data, buffer, sizeof(int));
            if( data == 0 )
                break;
            
            result += data;
        }
        /* Send result. */
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "Result = %d", result);

        printf("sending final result back to client\n");
        iRet = write(data_socket, buffer, BUFFER_SIZE);
        if (iRet == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        /* Close socket. */
        close(data_socket);
    }
    /*close the master socket*/
    close(master_fd);
    printf("connection closed..\n");

    /* Server should release resources before getting terminated.
     * Unlink the socket. */

    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);

    return 0;
}

