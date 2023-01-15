#include <stdlib.h>
#include <stdio.h>


int main()
{
	int a;
	int *p;

	p = & a;

	a = 5;
 
	printf("%d, %x\n", *p, p);

        int8_t * p1;
	p1 = (int8_t *) &a;

        int8_t low_addr_value = *p1;
        int8_t sec_addr_value = *(p1+1);
        int8_t third_addr_value = *(p1+2);
        int8_t high_addr_value = *(p1+3);       

        /* Intel32 is little endian - the least significant byte first (lowest address) and the most significant byte last (highest address) */
        printf("Addr-%x, a-%d; LowAddr-%d,Second-%d,Third-%d,HighAddr-%d\n",
                    p, a, low_addr_value, sec_addr_value, third_addr_value, high_addr_value);


	return 0;
}

