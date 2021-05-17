#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
  int msqid;
  char pathname[] = "server.c";
  key_t key;

  int len, maxlen;
  float num;

  struct clientmsgbuf {
    long mtype;
    struct {
      pid_t pid;
      float message;
    } info;
  } clientbuf;

  struct servermsgbuf {
    long mtype;
    struct {
      float message;
    } info;
  } serverbuf;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  clientbuf.mtype = 1;
  clientbuf.info.pid = getpid();

  printf("Enter number: ");
  scanf("%f", &num);

  len = sizeof(clientbuf.info);

  clientbuf.info.message = num;

  if (msgsnd(msqid, (struct clientmsgbuf *) &clientbuf, len, 0) < 0) {
    printf("Can\'t send message to queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds*) NULL);
    exit(-1);
  }

  printf("Client waiting for response\n");

  maxlen = sizeof(serverbuf.info);

  if (len = msgrcv(msqid, &serverbuf, maxlen, getpid(), 0) < 0) {
    printf("Can\'t receive message from queue\n");
    exit(-1);
  }

  printf("Client received from server: %f\n", serverbuf.info.message);

  return 0;
}
