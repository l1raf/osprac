#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

int counter = 128;
char res = 0;
int pid;

void sig1() {
  res += counter;
  counter /= 2;
  kill(pid, SIGUSR1);
}

void sig2() {
  counter /= 2;
  kill(pid, SIGUSR1);
}

int main() {
  signal(SIGUSR1, sig1);
  signal(SIGUSR2, sig2);

  pid = getpid();

  printf("PID: %d\n", pid);
  printf("Enter sender PID:\n");
  scanf("%d", &pid);

  kill(pid, SIGUSR2);

  while (counter != 0);

  printf("%d\n", res);

  pause();
  return 0;
}
