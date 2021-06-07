#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

int stopper = 1;
int starter = 0;

void my_handler(int sign) {
  if (sign != SIGUSR1)
    starter++;
  else
    stopper--;
}

int main() {
  int pid;
  char num = 0;

  signal(SIGUSR1, my_handler);
  signal(SIGUSR2, my_handler);

  printf("Enter number:\n");
  scanf("%d", &num);

  pid = getpid();

  printf("PID: %d\n", pid);
  printf("Enter receiver PID:\n");
  scanf("%d", &pid);

  while (starter != 1);

  for (int i = 128; i >= 1; i /= 2) {
    stopper = 1;

    if (i & num)
      kill(pid, SIGUSR1);
    else
      kill(pid, SIGUSR2);

    while(stopper);
  }

  return 0;
}
