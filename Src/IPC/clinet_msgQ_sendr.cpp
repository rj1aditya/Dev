#include <iostream>
#include <cstring>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/my_msg_queue"  // Message Queue Name

int main() {
    // Step 1: Open message queue for writing
    mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("mq_open (client)");
        return 1;
    }

    std::cout << "Client: Type messages (type 'exit' to quit):\n";

    char buffer[256];

    // Step 2: Send messages
    while (true) {
        std::cout << "You: ";
        std::cin.getline(buffer, sizeof(buffer));

        // Send message to server
        mq_send(mq, buffer, strlen(buffer) + 1, 0);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    // Step 3: Close the message queue
    mq_close(mq);
    return 0;
}
