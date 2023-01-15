#include <stdlib.h>
#include <stdio.h>


int main()
{
	int a;
	int b[10];
	int *p;

	p = & a;

	a = 5;
 
	printf("%d, %x\n", *p, p);

	p = b;

	b[0] = 10;
	b[1] = 20;

	printf("%d, %x\n", * (p+1), p);
	
	printf("Size of: a - %d, b - %d, p - %d\n", sizeof(a), sizeof(b), sizeof(p));

	return 0;
}

