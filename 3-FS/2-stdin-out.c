/* Processes - Example 1: File descriptor */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void)
{
	char buf[20]="\n \n Hello World \n\n";
	read(0, buf, 20);
	write(1, buf, 20); 
}
