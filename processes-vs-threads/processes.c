#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// multiple processes

// address space: different
// all variables duplicated and copied into child
int main(int argc, char *argv[])
{
    int x = 2;
    int pid = fork();
    if (pid == -1)
    {
        printf("fork failed\n");
        return 1;
    }
    if (pid == 0)
    {
        // child
        x++;
    }
    sleep(2);
    printf("Process with id: %d, result: %d\n", getpid(), x);
    if (pid != 0)
    {
        // parent
        wait(NULL);
    }
    return 0;
}
