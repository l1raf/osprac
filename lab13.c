#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  FILE *ptr;
  char fname[3], next[3];
  int depth = 0, index = 0;

  if ((ptr = fopen("file", "w")) == NULL) {
    printf("Failed to open file\n");
    exit(-1);
  }

  symlink("file", "0");

  fclose(ptr);
  sprintf(fname, "%d", index);

  while ((ptr = fopen(fname, "w")) != NULL) {
    depth++;

    sprintf(fname, "%d", index);
    sprintf(next, "%d", ++index);
    symlink(fname, next);
    sprintf(fname, "%d", index);

    fclose(ptr);
  }

  printf("Recursion depth: %d\n", depth);

  return 0;
}
