#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
  if (nsig == SIGINT)
    printf("Received signal %d, CTRL+C\n", nsig);
  else if (nsig == SIGQUIT)
    printf("Received signal %d, CTRL+4\n", nsig);
}

int main() {
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);

  while(1);
  return 0;
}
