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

  for (int i = 0; i < 5; i++) {
    mybuf.mtype = 2;
    strcpy(mybuf.mtext, "text message from 1 program");
    len = strlen(mybuf.mtext) + 1;

    if (msgsnd(msqid, (struct msbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }

    if ((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 3, 0)) < 0) {
      printf("Can't receive message from queue\n");
      exit(-1);
    }

    printf("First program received: %s, type = %d\n", mybuf.mtext, mybuf.mtype);
  }

  mybuf.mtype = LAST_MESSAGE;
  len = 0;

  if (msgsnd(msqid, (struct msbuf *) &mybuf, len, 0) < 0) {
    printf("Can\'t send message to queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }

  return 0;
}
