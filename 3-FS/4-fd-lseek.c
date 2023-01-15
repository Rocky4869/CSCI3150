/* Processes - Example 2: Create/read/write */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/* file e2*/
void main(void)
{
	char buf[20]="Hello World";
	char rbuf[20]="HA-HA-HAHA-HAHAHA\n";
	int fd;
	int num1, num2;

	fd = open("myfile", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR| S_IWUSR );
	
	printf("The file descriptor - fd: %d\n", fd);

	write(fd, buf, 20);
	lseek(fd, 0, SEEK_SET);

	read(fd, rbuf, 20); 

	write(1, rbuf, 20); 

	close(fd);
}

