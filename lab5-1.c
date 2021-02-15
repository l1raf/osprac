#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  size_t  size;
  char    resstring[15];

  if ((fd = open("myfile", O_RDONLY)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = read(fd, resstring, 15);

  if (size != 15) {   
    printf("Can\'t read all string\n");
    exit(-1);
  }

  printf(resstring);

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  return 0;
}


