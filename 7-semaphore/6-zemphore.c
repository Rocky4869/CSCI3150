#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>


typedef struct __Zem_t {
    int value;
    pthread_cond_t  cond;
    pthread_mutex_t lock;
} Zem_t;

void Zem_init(Zem_t *z, int value) {
    z->value = value;
    assert( pthread_cond_init(&z->cond, NULL) == 0 );
    assert( pthread_mutex_init(&z->lock, NULL) == 0 );
}

void Zem_wait(Zem_t *z) {
    assert( pthread_mutex_lock(&z->lock) == 0 );
    while (z->value <= 0)
    	assert( pthread_cond_wait(&z->cond, &z->lock) == 0);

    z->value--;
    assert( pthread_mutex_unlock(&z->lock) == 0 );
}

void Zem_post(Zem_t *z) {
    assert( pthread_mutex_lock(&z->lock) == 0);
    z->value++;
    assert( pthread_cond_signal(&z->cond) == 0);
    assert( pthread_mutex_unlock(&z->lock) == 0);
}

Zem_t s;


void *child(void *arg) {
    printf("child\n");
    Zem_post(&s); // signal here: child is done
    return NULL;
}



int main(int argc, char *argv[]) {
    Zem_init(&s, 0); 
    printf("parent: begin\n");

    pthread_t c;
    assert( pthread_create(&c, NULL, child, NULL) == 0);

    Zem_wait(&s); // wait here for child
    printf("parent: end\n");

    return 0;
}
