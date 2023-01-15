/* Use pipe to implement parent/child communication */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd[2];
	int ret;
        char *cmd;
        char *argv[3];

	
	pipe(fd);

	if ( (ret=fork()) > 0 ){
		/* Parent process*/
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]); 

        	cmd = "ls";
        	argv[0] = "ls";    
		argv[1] = "-l";     
		argv[2] = NULL;
		execvp(cmd, argv); 
	}else if (ret == 0 ){
		/* Child process*/
		close(0);
		dup( fd[0]);
		close( fd[0]);
		close ( fd[1]);  

        	cmd = "wc";
        	argv[0] = "wc";    
		argv[1] = "-l";     
		argv[2] = NULL;
		execvp(cmd, argv); 
	} else{
		/* Error in fork()*/
		printf("Error occurs when executing fork().\n");
		exit(-1);
	}
}

