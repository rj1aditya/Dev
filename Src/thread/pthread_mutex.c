#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* thread_fun1(void *arg)
{
    sleep(3);
    pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&m1);
    for(;;)
        printf("thread_fun1 lock taken\n");
    pthread_mutex_unlock(&m1);
    pthread_exit(NULL);
}

void* thread_fun2(void *arg)
{
    for(;;)
        printf("thread_fun2\n");
}

int main()
{
    pthread_t td1, td2;

    pthread_create(&td1, NULL, &thread_fun1, NULL);
    pthread_create(&td2, NULL, &thread_fun2, NULL);

    for(;;)
        printf("main func\n"); 

    pthread_join(td1, NULL);
    pthread_join(td2, NULL);
    return 0;
}