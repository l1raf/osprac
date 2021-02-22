#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd;
  size_t  size;
  char    name[] = "aaa.fifo";

  if (mkfifo(name, 0666) < 0)
  {
    printf("Can\'t create FIFO\n");
    exit(-1);
  }

  while(1)
  {
    fd = open(name, O_WRONLY);

    if(fd > 0)
    {
      write(fd, "Hello, world!\n", 15);

      close(fd);
      return 0;
    }
  }

  return 0;
}
