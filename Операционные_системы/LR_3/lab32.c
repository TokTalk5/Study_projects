#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("Program started\n");
    pid_t pid = fork();
    if (pid == -1) printf("Error!\n");
    else if (pid == 0)
    {
        if (execl("lab31", "Program", "children", NULL) == -1) printf("Error!\n");
    }
    else if (pid > 0)
    {
        printf("Parent process ID:");
        printf("%d\n", getppid());
        printf("Program 2 ID:");
        printf("%d\n", getpid());
        printf("Child process ID:");
        printf("%d\n", pid);
        int status;
        while (waitpid(pid, &status, WNOHANG) == 0) {
            printf("Waiting\n");
            usleep(500000);
        }
        printf("Child process exit code:");
        printf("%d\n", WEXITSTATUS(status));
    }
    printf("Program ended\n");
    return 0;
}
