#include <iostream>
#include <cstring>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/my_msg_queue"  // Message Queue Name

int main() {
    // Step 1: Define message queue attributes
    struct mq_attr attr;
    attr.mq_flags = 0;          // Blocking mode
    attr.mq_maxmsg = 10;        // Maximum messages in queue
    attr.mq_msgsize = 256;      // Max size per message
    attr.mq_curmsgs = 0;        // Current messages in queue

    // Step 2: Open message queue for reading
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open (server)");
        return 1;
    }

    std::cout << "Server: Waiting for messages...\n";

    char buffer[256];

    // Step 3: Receive message
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = mq_receive(mq, buffer, 256, NULL);
        
        if (bytes_read > 0) {
            std::cout << "Server received: " << buffer << std::endl;

            if (strcmp(buffer, "exit") == 0) {
                std::cout << "Server: Exiting...\n";
                break;
            }
        }
    }

    // Step 4: Close and unlink the message queue
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
