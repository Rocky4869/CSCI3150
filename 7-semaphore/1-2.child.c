#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>

sem_t mutex;

void *child(void *arg) {
    printf("child\n");
    assert(sem_post(&mutex) == 0);	

    return NULL;
}

void thr_join()
{
   
    assert(sem_wait(&mutex) == 0);	
    assert(sem_wait(&mutex) == 0);	
}

int main(int argc, char *argv[]) {

    assert(sem_init(&mutex, 0, 0) == 0);

    pthread_t c1, c2;

    printf("Parent start\n");

    assert(pthread_create(&c1, NULL, child, NULL) == 0);
    assert(pthread_create(&c2, NULL, child, NULL) == 0);

    thr_join();

    printf("Parent finish\n");

    return 0;
}

    
