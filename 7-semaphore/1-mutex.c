#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>

sem_t mutex;

volatile int counter = 0;

void *child(void *arg) {
    int i;

    for (i = 0; i < 10000000; i++) {
	assert(sem_wait(&mutex) == 0);
	counter++;
	assert(sem_post(&mutex) == 0);
    }

    return NULL;
}



int main(int argc, char *argv[]) {

    assert(sem_init(&mutex, 0, 1) == 0);

    pthread_t c1, c2;

    assert(pthread_create(&c1, NULL, child, NULL) == 0);
    assert(pthread_create(&c2, NULL, child, NULL) == 0);

    assert(pthread_join(c1, NULL) == 0);
    assert(pthread_join(c2, NULL) == 0);

    printf("result: %d (should be 20000000)\n", counter);

    return 0;
}

    
