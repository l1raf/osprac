#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd;
  char    resstring[14];
  char    name[] = "aaa.fifo";

  while(1) 
  {
    fd = open(name, O_RDONLY);

    if (fd > 0)
    {
      read(fd, resstring, 15);

      printf("resstring from fifo: %s\n", resstring);

      close(fd);
      return 0;
    }
  }

  return 0;
}
