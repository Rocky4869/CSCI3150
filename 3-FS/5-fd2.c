/* Processes - Example 3: Create/read/write */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


void main(void)
{
	char buf[20]="Hello";
	char rbuf[20]="LAHA";
	int fd1, fd2;

	fd1 = open("myfile", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR| S_IWUSR );
	fd2 = open("myfile", O_RDWR);
	
	printf("file descriptors: fd1-%d; fd2-%d\n", fd1, fd2);

	write(fd1, buf, 20);

	read(fd2, rbuf, 20); 
	
	write(1, rbuf, 20); 
}
