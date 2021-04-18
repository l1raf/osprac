#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>

int main() {
  int     semid;
  int     *array;
  int     shmid;
  int     new = 1;
  char    pathname[] = "07-3a.c";
  key_t   key;
  long    i;
  struct  sembuf sbuf;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
      new = 0;
    }
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if ((semid = semget(key, 1, 0)) < 0) {
      printf("Cannot find shared memory\n");
      exit(-1);
    }
  } else {
    sbuf.sem_flg = 0;
    sbuf.sem_op = 1;
    sbuf.sem_num = 0;

    if (semop(semid, &sbuf, 1) < 0) {
      printf("Condition error\n");
      exit(-1);
    }
  }

  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  sbuf.sem_flg = 0;
  sbuf.sem_num = 0;
  sbuf.sem_op = -1;

  if (semop(semid, &sbuf, 1) < 0) {
    printf("Condition error\n");
    exit(-1);
  }

  if (new) {
    array[0] =  1;
    array[1] =  0;
    array[2] =  1;
  } else {
    array[0] += 1;
    for(i = 0; i < 2000000000L; i++);
    array[2] += 1;
  }

  printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[0], array[1], array[2]);

  sbuf.sem_flg = 0;
  sbuf.sem_op = 1;
  sbuf.sem_num = 0;

  if (semop(semid, &sbuf, 1) < 0) {
    printf("Condition error\n");
    exit(-1);
  }

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  return 0;
}
