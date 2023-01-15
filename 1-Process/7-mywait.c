#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
        int i;
        int n=5;
        pid_t childpid;
        int status;
        pid_t waitreturn;

        for (i = 1; i < n;  ++i)
                if ( (childpid = fork() ) > 0)
                        break;
	  if((waitreturn = wait(&status))<0)
                 printf("wait(): Returns - %d.\n", waitreturn);
        
	  printf( "I am process %d, my parent is %d, childpid-%d, i-%d\n", getpid(), getppid(), childpid, i);

        return 0;
}

