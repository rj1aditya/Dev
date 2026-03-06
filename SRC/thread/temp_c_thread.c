#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
struct xyz
{
    int a;
    double b;
};

void* func(void* ptr)
{
    struct xyz *tmp = (struct xyz*)(ptr);

    printf("Struct value In thread\n");
    for(int i = 0; i < 5; i++)
    {
        // printf("a=%d b=%f\n", obj[i].a, obj[i].b);
        printf("a=%d b=%f\n", tmp->a, tmp->b);
        tmp++;
    }
    pthread_exit((void*)500);
    return NULL;
}


int main()
{
    struct xyz *obj = (struct xyz*)malloc(5*sizeof(struct xyz));
    struct xyz *tmp = obj;

    for(int i = 0; i < 5; i++)
    {
        // obj[i].a = i*2;
        // obj[i].b = i*10.1;
        tmp->a = i*2;
        tmp->b = i*10.1;
        tmp++;
    }

    printf("Struct value before thread\n");
    tmp = obj;
    for(int i = 0; i < 5; i++)
    {
        // printf("a=%d b=%f\n", obj[i].a, obj[i].b);
        printf("a=%d b=%f\n", tmp->a, tmp->b);
        tmp++;
    }

    pthread_t td1;
    tmp = obj;
    pthread_create(&td1, NULL, func, tmp);

    int x = 10;
    pthread_join(td1, (void*)&x);

    printf("Thread returned value=%d", x);
}