#include <stdio.h>   // printf()
#include <unistd.h>  // getpid()

int main(void) {
    printf("My PID is %d, UID is %d, My Parent PID is %d\n", getpid(), getuid(), getppid() );
    return 0;
}

