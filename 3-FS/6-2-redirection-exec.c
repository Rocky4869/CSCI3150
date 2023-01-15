/* Processes - Example 4.1: Redirection */
/* Can we use exec to implemeent "ls -l > myfile"?*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
        char *cmd = "ls";
        char *argv[5];
        argv[0] = "ls";    
	argv[1] = "-l";     
	argv[2] = ">";     
	argv[3] = "myfile";     
	argv[4] = NULL;

        execvp(cmd, argv);
}


