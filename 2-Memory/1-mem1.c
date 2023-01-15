#include <stdlib.h>
#include <stdio.h>


int main()
{
	int *x = malloc(10 * sizeof(int));
	int y[10];
	printf("Size: pointer-%d; array-Y-%d\n", sizeof(x), sizeof(y));
}

