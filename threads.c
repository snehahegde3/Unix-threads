#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// the routine the thread executes
void *routine()
{
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(int argc, char *argv[])
{
    // where api stores
    pthread_t t1, t2;
    // pthread_create(pointer to thread, some attr NULL if default, function pointer, arguments to the function)
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
    {
        printf("failed to create thread\n");
        return 1;
    }

    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
    {
        printf("failed to create thread\n");
        return 2;
    }
    // wait for all threads
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
