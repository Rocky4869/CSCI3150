#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int  ret_from_fork;

    printf("Before: my pid is %d\n", getpid());

    ret_from_fork = fork();

    sleep(1);

    printf("After: my pid is %d, return value from fork():%d\n",
                getpid(),  ret_from_fork);

    return 0;
}

