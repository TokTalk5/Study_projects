#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
typedef struct
{
    int flag;
    char sym;
}targs;
static void
       display_pthread_attr(pthread_attr_t *attr, char *prefix)
       {
           int s, i;
           size_t v;
           void *stkaddr;
           struct sched_param sp;

           s = pthread_attr_getdetachstate(attr, &i);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getdetachstate");
           printf("%sDetach state        = %s\n", prefix,
                   (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
                   (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
                   "???");

           s = pthread_attr_getscope(attr, &i);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getscope");
           printf("%sScope               = %s\n", prefix,
                   (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
                   (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
                   "???");

           s = pthread_attr_getinheritsched(attr, &i);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getinheritsched");
           printf("%sInherit scheduler   = %s\n", prefix,
                   (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
                   (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
                   "???");

           s = pthread_attr_getschedpolicy(attr, &i);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getschedpolicy");
           printf("%sScheduling policy   = %s\n", prefix,
                   (i == SCHED_OTHER) ? "SCHED_OTHER" :
                   (i == SCHED_FIFO)  ? "SCHED_FIFO" :
                   (i == SCHED_RR)    ? "SCHED_RR" :
                   "???");

           s = pthread_attr_getschedparam(attr, &sp);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getschedparam");
           printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);

           s = pthread_attr_getguardsize(attr, &v);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getguardsize");
           printf("%sGuard size          = %zu bytes\n", prefix, v);

           s = pthread_attr_getstack(attr, &stkaddr, &v);
           if (s != 0)
               handle_error_en(s, "pthread_attr_getstack");
           printf("%sStack address       = %p\n", prefix, stkaddr);
           printf("%sStack size          = %#zx bytes\n", prefix, v);
       }

void * proc1 (void *arg)
{
    printf("\nThread 1 started\n");
    targs *args = (targs*) arg;
    while (args -> flag == 0)
    {
        putchar(args -> sym);
        fflush(stdout);
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
        putchar(args -> sym);
        fflush(stdout);
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
    int *exitcode1, *exitcode2, inherit;
    targs arg1;
    targs arg2;
    arg1.flag = 0;
    arg1.sym = '1';
    arg2.flag = 0;
    arg2.sym = '2';
    char t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&id1,&attr,proc1,&arg1);
    pthread_create(&id2,&attr,proc2,&arg2);
    printf("The program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    arg1.flag = 1;
    arg2.flag = 1;
    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);
    printf("exitcode1 = %p\n", exitcode1);
    printf("exitcode2 = %p\n", exitcode2);
    printf("Program ended");
    //printf("%d",attr);
    printf("Thread attributes:\n");
    display_pthread_attr(&attr, &t);
    return 0;
}
