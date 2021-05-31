#include <signal.h>

int main()
{
  (void) signal(SIGQUIT, SIG_IGN);
  (void) signal(SIGINT, SIG_IGN);

  while(1);
  return 0;
}
