#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h> 

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int main(){
    printf("%s\n", "Program start");
    int flag = 0;
    sem_t *sem;
    FILE* f = fopen("./output.txt", "a+");
    printf("%s\n", "Creating or opening semaphore");
    sem = sem_open("/sem", O_CREAT, S_IRWXU, 1);
    while (flag == 0){
         sem_wait(sem);
         for (int i = 0; i < 3; i++){
              putc('2', f);
       	      fflush(f);
       	      putchar('2');
       	      fflush(stdout);
       	      sleep(1);
         }
         sem_post(sem);
         sleep(1);
         if (kbhit())flag = 1;
    }
    printf("\n%s\n", "Closing semaphore");
    sem_close(sem);
    printf("%s\n", "Unlinking semaphore");
    sem_unlink("/sem");
    fclose(f);
    printf("%s\n", "End of program");
    return 0;
}
