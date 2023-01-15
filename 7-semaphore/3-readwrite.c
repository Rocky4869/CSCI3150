#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>

typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;


void rwlock_init(rwlock_t *lock) {
    lock->readers = 0;
    assert( sem_init(&lock->lock, 0, 1) == 0); 
    assert( sem_init(&lock->writelock, 0, 1) == 0); 
}



void rwlock_acquire_readlock(rwlock_t *lock) {
    assert( sem_wait(&lock->lock) == 0);
    lock->readers++;

    if (lock->readers == 1)
        assert( sem_wait(&lock->writelock) == 0 );

    assert( sem_post(&lock->lock) ==0);
}



void rwlock_release_readlock(rwlock_t *lock) {
    assert( sem_wait(&lock->lock) ==0);
    lock->readers--;

    if (lock->readers == 0)
	    assert( sem_post(&lock->writelock) == 0 );

    assert( sem_post(&lock->lock) == 0);
}



void rwlock_acquire_writelock(rwlock_t *lock) {
    assert( sem_wait(&lock->writelock) == 0);
}



void rwlock_release_writelock(rwlock_t *lock) {
    assert( sem_post(&lock->writelock) == 0);
}



int read_loops;
int write_loops;
int counter = 0;

rwlock_t mutex;

void *reader(void *arg) {
    int i;

    int local = 0;

    for (i = 0; i < read_loops; i++) {
    	rwlock_acquire_readlock(&mutex);
    	local = counter;
    	rwlock_release_readlock(&mutex);
    	printf("Read: time-%d, counter-%d\n", i, local);
    }

    printf("read done: %d\n", local);
    return NULL;
}



void *writer(void *arg) {
    int i;
    
    for (i = 0; i < write_loops; i++) {
    	rwlock_acquire_writelock(&mutex);
    	counter++;
    	rwlock_release_writelock(&mutex);
    	printf("Write: time-%d, counter-%d\n", i, counter);
    }

    printf("write done\n");
    return NULL;
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
    	fprintf(stderr, "usage: rwlock readloops writeloops\n");
    	exit(1);
    }

    read_loops = atoi(argv[1]);
    write_loops = atoi(argv[2]);

    rwlock_init(&mutex); 

    pthread_t c1, c2;

    assert( pthread_create(&c1, NULL, reader, NULL) ==0 );
    assert( pthread_create(&c2, NULL, writer, NULL) ==0 );

    assert( pthread_join(c1, NULL) == 0);
    assert( pthread_join(c2, NULL) ==0);

    printf("all done\n");
    return 0;
}
