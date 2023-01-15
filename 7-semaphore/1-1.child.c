#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>

sem_t mutex;
sem_t parent;

int done=2;

void *child(void *arg) {
    assert(sem_wait(&mutex) == 0);	
    printf("child. - %d\n", done);
    done--;
    if( done == 0)
    	assert(sem_post(&parent) == 0);

    assert(sem_post(&mutex) == 0);

    return NULL;
}

void thr_join()
{
   
    assert(sem_wait(&parent) == 0);	
}

int main(int argc, char *argv[]) {

    assert(sem_init(&mutex, 0, 1) == 0);
    assert(sem_init(&parent, 0, 0) == 0);

    pthread_t c1, c2;

    printf("Parent start\n");

    assert(pthread_create(&c1, NULL, child, NULL) == 0);
    assert(pthread_create(&c2, NULL, child, NULL) == 0);

    thr_join();

    printf("Parent finish\n");

    return 0;
}

    
