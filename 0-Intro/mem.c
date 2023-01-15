#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100000000
	
int main(int argc, char *argv[])
{
	int *p = malloc(MAX*sizeof(int));  // a1: allocate some memory
	assert(p != NULL);

	printf("(%d) Address Range: %08x - %08x \n", getpid(), (unsigned) p, (unsigned) (p+MAX-1)); 	// a2: print out the address of the memory

	*p = 0; 	// a3: put zero into the first slot of the memory

	int i=0;
	while (i<10) {
		sleep(1);
		*p = *p + 1;
		i=i+1;
		printf("(%d) p: %d\n", getpid(), *p); // a4
	}

	return 0;
}
