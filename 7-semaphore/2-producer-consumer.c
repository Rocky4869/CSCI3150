#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>



int max;
int loops;
int *buffer;

int use  = 0;
int fill = 0;


sem_t empty;
sem_t full;
sem_t mutex;


#define CMAX (10)

int consumers = 1;


void do_fill(int value) {
    buffer[fill] = value;
    fill++;
    if (fill == max)
    	fill = 0;

}



int do_get() {
    int tmp = buffer[use];
    use++;
    if (use == max)
    	use = 0;

    return tmp;
}



void *producer(void *arg) {
    int i;

    for (i = 0; i < loops; i++) {
    	assert( sem_wait(&empty) == 0);

    	assert( sem_wait(&mutex) == 0);
    	do_fill(i);
    	assert( sem_post(&mutex) == 0);

        assert( sem_post(&full) == 0);
    }



    // end case
    for (i = 0; i < consumers; i++) {
    	assert( sem_wait(&empty) == 0);

    	assert( sem_wait(&mutex) == 0);
    	do_fill(-1);
    	assert( sem_post(&mutex) == 0);

        assert( sem_post(&full) == 0);
    }

    return NULL;
}

                                                                               

void *consumer(void *arg) {

    int tmp = 0;

    while (tmp != -1) {
    	assert( sem_wait(&full) == 0);

    	assert( sem_wait(&mutex) == 0);
    	tmp = do_get();
    	assert( sem_post(&mutex) == 0);

        assert( sem_post(&empty) == 0);

        printf("consumer-%d: %d\n", (int) arg, tmp);

    }

    return NULL;

}



int main(int argc, char *argv[]) {

    if (argc != 4) {
    	fprintf(stderr, "usage: %s <buffersize> <loops> <consumers>\n", argv[0]);
    	exit(1);
    }

    max   = atoi(argv[1]);
    loops = atoi(argv[2]);

    consumers = atoi(argv[3]);

    assert(consumers <= CMAX);

    buffer = (int *) malloc(max * sizeof(int));

    assert(buffer != NULL);

    int i;

    for (i = 0; i < max; i++) {
    	buffer[i] = 0;
    }



    assert( sem_init(&empty, 0, max) == 0 ); // max are empty 

    assert( sem_init(&full, 0, 0) == 0 );    // 0 are full

    assert( sem_init(&mutex, 0, 1) == 0 );   // mutex


    pthread_t pid, cid[CMAX];

    assert( pthread_create(&pid, NULL, producer, NULL) == 0 ); 

    for (i = 0; i < consumers; i++) {
    	assert( pthread_create(&cid[i], NULL, consumer, (void *) i) == 0 ); 
    }

    assert( pthread_join(pid, NULL) == 0 ); 

    for (i = 0; i < consumers; i++) {
    	assert( pthread_join(cid[i], NULL) == 0 ); 
    }

    return 0;
}

