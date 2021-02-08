#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t  pid;

    pid = fork();

    if (pid == -1)
    {
        printf("Error occured");
        exit(-1);
    }
    else if (pid == 0)
    {
        execle("/bin/cat", "/bin/cat", "lab4-1.c", 0, envp);
    }
    else
    {
        printf("Parent\n");
    }
}
