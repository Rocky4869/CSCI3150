#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        fork();
        fork();
        fork();
        printf("PID - %d, PPID -%d\n", getpid(), getppid());
        sleep(1);
        return 0;
}

