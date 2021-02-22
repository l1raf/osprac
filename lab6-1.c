#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int fd[2], size = 0, bSize = 0;

  if (pipe2(fd, O_NONBLOCK) < 0) 
  {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  do
  {
    size = write(fd[1], "a", 1);
    bSize++;
  } 
  while (size > 0);

  printf("Buffer size: %d\n", --bSize);
}
