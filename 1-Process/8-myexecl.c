#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t childpid;
	int status;
	
	char *cmd = "ls";
	char *argv[2];
	argv[0] = "ls";
	argv[1] = NULL;

	if ((childpid = fork()) == -1){ 
		printf("Error: fork()\n");
  		return -1;
	} else  if (childpid == 0) {
		/*child code*/
  		if (execvp(cmd, argv) < 0) {
			printf("Error: execvp()\n");
     			return -1;
		}
 	}else if (childpid != wait(&status)){   
 		/* parent code */
     		printf("Error: wait()");
     		return -1;
	}

	return 0;
}

