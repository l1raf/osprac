#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  char     *array;
  int     shmid;
  char    pathname[] = "lab7a.c";
  key_t   key;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  shmid = shmget(key, 6*sizeof(char), 0666|IPC_CREAT|IPC_EXCL);
  array = shmat(shmid, NULL, 0);

  array[0] = 'H';
  array[1] = 'e';
  array[2] = 'l';
  array[3] = 'l';
  array[4] = 'o';
  array[5] = 0;

  shmdt(array);

  return 0;
}

