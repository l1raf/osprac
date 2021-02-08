#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    printf("cmd args:\n");

    for (int i = 0; i < argc; i++) 
    {
        printf("%s\n", argv[i]);
    }

    printf("environment vars:\n");

    int i = 0;
    while (envp[i] != NULL)
    {
        printf("envp[%d] %s\n", i, envp[i]);
        i++;
    }

    return 0;
}

