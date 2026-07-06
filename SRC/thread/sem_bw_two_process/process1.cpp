#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    sem_t *sem1 = sem_open("/sem1", O_CREAT, 0666, 1);
    sem_t *sem2 = sem_open("/sem2", O_CREAT, 0666, 0);

    for (int i = 1; i <= 5; i++) {
        sem_wait(sem1);

        printf("Process 1 : %d\n", i);
        sleep(1);

        sem_post(sem2);
    }

    sem_close(sem1);
    sem_close(sem2);

    return 0;
}