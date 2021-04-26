#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 1

int main(void)
{
  int msqid;
  char pathname[] = "lab11-2a.c";
  key_t  key;
  int len, maxlen;

  struct mymsgbuf
  {
    long mtype;
    char mtext[81];
  } mybuf;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  while (1) {
    maxlen = 81;

    if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, -2, 0)) < 0) {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }

    if (mybuf.mtype == LAST_MESSAGE) {
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(0);
    }

    printf("Second program received: %s, type = %d\n", mybuf.mtext, mybuf.mtype);

    mybuf.mtype = 3;
    strcpy(mybuf.mtext, "text message from 2 program");
    len = strlen(mybuf.mtext) + 1;

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      exit(-1);
    }
  }

  return 0;
}
