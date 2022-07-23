#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// multiple threads in same process
// address space: same
// accessing the same variables no duplication

int x = 2;

void *routine()
{
    x += 5;
    sleep(2);
    printf("I'm the thread with id: %d, res: %d\n", getpid(), x);
}

void *routine2()
{
    sleep(2);
    printf("I'm the thread with id: %d, res: %d\n", getpid(), x);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
    {
        printf("failed to create thread\n");
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
    {
        printf("failed to create thread\n");
        return 2;
    }
    if (pthread_join(t1, NULL) != 0)
    {
        printf("failed to join\n");
        return 3;
    }
    if (pthread_join(t2, NULL) != 0)
    {
        printf("failed to join\n");
        return 4;
    }

    return 0;
}
