#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int a = 0;

    pid_t pid = fork();

    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        a += 5;
        printf("This is child\nresult = %d\n", a);
    } else {
        a += 10;
        printf("This id parent\nresult = %d\n", a);
    }

    return 0;
}

