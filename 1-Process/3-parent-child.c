#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        pid_t childpid;

        if ((childpid = fork()) == -1){
                printf("Error in the fork");
                return -1;
        } else  if (childpid == 0) {
                /*child code*/
                printf("Before sleep: I am the child (PID - %d, PPID -%d)\n", getpid(), getppid());
		sleep(10);
                printf("After sleep: I am the child (PID - %d, PPID -%d)\n", getpid(), getppid());
                return 0;
        }else{
                /* parent code */
		sleep(1);
                printf("I am the parent (PID - %d, PPID -%d)\n", getpid(), getppid());
                return 0;
        }
}

