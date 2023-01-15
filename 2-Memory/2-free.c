#include <stdlib.h>
#include <stdio.h>


int main()
{
	int *x = (int *)malloc(sizeof(int)); // allocated	
	free(x); // free memory
	free(x); // free repeatedly -- Errro occurs

}

