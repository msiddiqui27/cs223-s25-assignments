#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigInt(int sig)
{
  printf("Help! I've been shot!\n");
  exit(0);
}

int main()
{
  signal(SIGINT, handle_sigInt);

  while (1)
  {
    sleep(1);
  }

  return 0;
}

