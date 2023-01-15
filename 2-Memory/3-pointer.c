#include <stdlib.h>
#include <stdio.h>


int main()
{
	int a;
	int *p;

	p = & a;

	a = 5;
 
	printf("%d, %x\n", *p, p);

	return 0;
}

