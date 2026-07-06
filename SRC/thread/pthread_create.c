#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
typedef struct student
{
    char name[20];
    int rollNo;
}student;

void* fun(void *str)
{
    for(;;){
            pid_t tid = syscall(SYS_gettid);
            printf("thread id[%d]\n", tid);
    }
    struct student *s1 = (struct student*)malloc(sizeof(struct student));
    memcpy(s1->name, "aditya", sizeof(s1->name));
    s1->rollNo = 1243616;
    printf("new thread created start excecuting\n");
    pthread_exit((void*)s1);
}

int main()
{
    pthread_t td1;
    printf("Main thread created start excecuting\n");
    pthread_create(&td1, NULL, &fun, NULL);
    int iThreadRet;
    struct student *strThreadReturnVal;
    pthread_join(td1, (void*)&strThreadReturnVal);
    //pthread_join(td1, (void*)&strThreadReturnVal);
    printf("Main exiting from the process\n");
    printf("Return Value from main:\n");
    printf("RollNo:[%d]\n", strThreadReturnVal->rollNo);
    printf("Name:[%s]\n", strThreadReturnVal->name);
    return 0;
}