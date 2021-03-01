#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  char    *array;
  int     shmid;
  char    pathname[] = "lab7a.c"; 
  key_t   key;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  shmid = shmget(key, 6*sizeof(char), 0);
  array = shmat(shmid, NULL, 0);
  printf("%s\n", array);
  shmdt(array);
  shmctl(shmid, IPC_RMID, 0);

  return 0;
}

