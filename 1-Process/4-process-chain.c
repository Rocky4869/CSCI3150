#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        int i;
        int childpid;

        for( i = 3; i> 0; i--){

                if ((childpid = fork()) == -1){
                        printf("Error in the fork");
                        return -1;
                } else  if (childpid == 0) {
                        /*child code*/
                        printf("I am the child (PID - %d, PPID -%d)\n", getpid(), getppid());
                }else{
                        /* parent code */
                        printf("I am the parent (PID - %d, Child PID -%d, i-%d\n", getpid(), childpid, i);
			sleep(1);
                        return 0;
                }
        }
}

