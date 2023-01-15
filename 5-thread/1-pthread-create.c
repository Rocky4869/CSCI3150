#include <pthread.h>
#include <stdio.h>
 
typedef struct __myarg_t {
	int a;
	int b;
} myarg_t;
 
void *mythread(void *arg) {
	myarg_t *m = (myarg_t *) arg;
	printf("%d, %d\n", m->a, m->b);
	return NULL;
}
 
int main(int argc, char *argv[]) {
	pthread_t p;
 
	myarg_t args;
	args.a = 10;
	args.b = 20;
	pthread_create(&p, NULL, mythread, &args);
	pthread_join(p, NULL);

        return 0;
}

