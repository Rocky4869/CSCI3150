#include <stdio.h>
int main()
{
	int var = 789;
 	int *ptr2;
 	int **ptr1;

	ptr2 = &var;
 	ptr1 = &ptr2;

	*ptr2 = 12;
 	printf("%d %d %d\n", var, *ptr2, **ptr1);
 	return 0;
}

