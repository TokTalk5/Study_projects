#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h> 
typedef struct
{
    int flag;
    char sym;
}targs;

pthread_mutex_t mutex;
    
void * proc1 (void *arg)
{
    printf("\nThread 1 started\n");
    targs *args = (targs*) arg;
    while (args -> flag == 0)
    {
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < 10; i ++)
        {
            putchar(args -> sym);
            fflush(stdout);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("\nThread 1 finished\n");
    pthread_exit((void*)2);
}
void *proc2 (void *arg)
{
    printf("\nThread 2 started\n");
    targs *args = (targs*) arg;
    while (args -> flag == 0)
    {
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < 10; i ++)
        {
            putchar(args -> sym);
            fflush(stdout);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("\nThread 2 finished\n");
    pthread_exit((void*)2);
}
int main()
{
    printf("Program started\n");
    pthread_t id1;
    pthread_t id2;
    int *exitcode1, *exitcode2;
    targs arg1;
    targs arg2;
    arg1.flag = 0;
    arg1.sym = '1';
    arg2.flag = 0;
    arg2.sym = '2';
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&id1,NULL,proc1,&arg1);
    pthread_create(&id2,NULL,proc2,&arg2);
    printf("The program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    arg1.flag = 1;
    arg2.flag = 1;
    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);
    pthread_mutex_destroy(&mutex);
    printf("exitcode1 = %p\n", exitcode1);
    printf("exitcode2 = %p\n", exitcode2);
    printf("Program ended");
    return 0;
}
