#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main()
{
  //Parent
  //for (int i = 0; i < n; i++)
  //  write
  //  A(S,2)
  //  Z(S,0)
  //  read
  //Child
  //for (int i = 0; i < n; i++)
  //  D(S,1)
  //  read
  //  write
  //  D(S,1)

  struct sembuf mybuf;
  int n;
  int fd[2];
  int result;
  int semid;
  size_t size;
  char  resstring[5];

  key_t key;
  char pathname[] = "05-3.c";

  scanf("%d", &n);

  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if ((semid = semget(key, 1, 0)) < 0) {
      printf("Can\'t find shared memory\n");
      exit(-1);
    }
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {
   /* Parent process */
    for (int i = 0; i < n; i++) {
      size = write(fd[1], "Ping", 5);

      if (size != 5) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      printf("Parent wrote message\n");

      //let the child read
      mybuf.sem_op = 2;
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;

      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      //wait for the child to read and write
      mybuf.sem_op = 0;
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;

      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      size = read(fd[0], resstring, 5);

      if (size < 0) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
      }

      printf("Parent read message: %s\n", resstring);
    }

    if (close(fd[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n");
      exit(-1);
    }

    if (close(fd[0]) < 0) {
      printf("parent: Can\'t close reading side of pipe\n");
      exit(-1);
    }
  } else {
    /* Child process */
    for (int i = 0; i < n; i++) {
      //wait for the parent to write
      mybuf.sem_op = -1;
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;

      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      size = read(fd[0], resstring, 5);

      if (size < 0) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
      }

      printf("Child read message: %s\n", resstring);

      size = write(fd[1], "Pong", 5);

      if (size != 5) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      printf("Child wrote message\n");

      //let the parent read
      mybuf.sem_op = -1;
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;

      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }
    }

    if (close(fd[1]) < 0) {
      printf("child: Can\'t close writing side of pipe\n");
      exit(-1);
    }

    if (close(fd[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n");
      exit(-1);
    }
  }

  return 0;
}
