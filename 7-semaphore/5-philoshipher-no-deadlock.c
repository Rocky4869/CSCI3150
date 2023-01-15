#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>


typedef struct {
    int num_loops;
    int thread_id;
} arg_t;


sem_t forks[5];


int left(int p)  {
    return p;
}


int right(int p) {
    return (p + 1) % 5;
}



void get_forks(int p, int i) {
    int l=left(p);
    int r=right(p);
    
    if( p == 4){
    	printf("**Philoshipher-%d (%d-th): wait for right: fork-%d\n", p, i, r);
    	assert( sem_wait(&forks[r]) ==0 );
    	printf("Philoshipher-%d (%d-th): obtain the right: fork-%d; wait for the left: fork-%d.\n", p, i, r, l);
    	assert( sem_wait(&forks[l]) ==0 );
    	printf("&&Philoshipher-%d (%d-th): obtain the left: fork-%d.\n", p, i, l);
    }else{
    	printf("**Philoshipher-%d (%d-th): wait for left: fork-%d\n", p, i, l);
    	assert( sem_wait(&forks[l]) ==0 );
    	printf("Philoshipher-%d (%d-th): obtain the left: fork-%d; wait for the right: fork-%d.\n", p, i, l, r);
    	assert( sem_wait(&forks[r]) ==0 );
    	printf("&&Philoshipher-%d (%d-th): obtain the right: fork-%d.\n", p, i, r);
    }
}



void put_forks(int p) {
    assert( sem_post(&forks[left(p)]) == 0);
    assert( sem_post(&forks[right(p)]) == 0);
}



void think() {
    return;
}



void eat() {
    return;
}



void *philosopher(void *arg) {
    arg_t *args = (arg_t *) arg;
    int p = args->thread_id;

    int i;

    for (i = 0; i < args->num_loops; i++) {
	think();
	get_forks(p, i);
	eat();
	put_forks(p);
    }

    return NULL;
}

                                                                             

int main(int argc, char *argv[]) {

    if (argc != 2) {
	fprintf(stderr, "usage: dining_philosophers_deadlock <num_loops>\n");
	exit(1);
    }

    printf("dining: started\n");


    int i;

    for (i = 0; i < 5; i++) 
	assert( sem_init(&forks[i], 0, 1) == 0);


    pthread_t p[5];

    arg_t a[5];

    for (i = 0; i < 5; i++) {
	a[i].num_loops = atoi(argv[1]);
	a[i].thread_id = i;
	assert( pthread_create(&p[i], NULL, philosopher, &a[i]) == 0);

    }



    for (i = 0; i < 5; i++) 
	assert( pthread_join(p[i], NULL) == 0); 

    printf("dining: finished\n");

    return 0;

}
