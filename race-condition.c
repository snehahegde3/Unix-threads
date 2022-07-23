#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int mails = 0;
// the routine the thread executes
// adds mails to mailbox
void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        mails++;
    }
}

/*
the routine:
normally,
                     t1             t2
read mails           23             24
inc mails            23             24
write mails          24             25

if t2 stops after reading and t1 runs for lets say 7 iterations
                     t1             t2
read mails           29             23
inc mails            29             30
write mails          30             24
now the new value becomes 24

this is called a race condition

if the number is low, theres no interleaving or chance is lower
*/

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
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
    printf("Mails: %d\n", mails);
    return 0;
}
