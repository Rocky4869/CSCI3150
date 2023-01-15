/* Use pipe to implement parent/child communication */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
        char *cmd;
        char *argv[3];
	int fd1;

	
	fd1 = open("myfile", O_CREAT |O_TRUNC |O_RDWR, S_IRUSR| S_IWUSR );
	/* Close the stdout*/
	close(1);
	dup(fd1);
	close(fd1);

       	cmd = "ls";
       	argv[0] = "ls";    
	argv[1] = "-l";     
	argv[2] = NULL;
	execvp(cmd, argv); 

	return 1;
}

