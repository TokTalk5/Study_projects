
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("Child program started\n");
    printf("Parent process ID:");
    printf("%d\n", getppid());
    printf("Program 2 ID:");
    printf("%d\n", getpid());
    printf("Arguments\n");
    int status = 0;
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
        status += 1;
	sleep(1);
    }
    printf("Child process exit code:");
    printf("%d\n", status);
    printf("Child program ended\n");
    return status;
}
