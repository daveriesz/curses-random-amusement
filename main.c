
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "cra.h"

void main_stop(int sig);
void main_loop();
void main_signals();

int main(int argc, char **argv)
{
  if(!strcmp(argv[1], "-g")) { debug_set(1); }
  main_signals();
  main_loop();
  return 0;
}

int continue_loop = 1;
void main_loop()
{
  for ( ; continue_loop != 0 ; )
  {
    display();
    usleep(1000);
    debug("main loop\n");
  }
}

void main_stop(int sig)
{
  display_uninitialize();
  continue_loop = 0;
  if(sig == SIGSEGV)
  {
    fprintf(stderr, "Caught SIGSEGV.  Reset, exit\n");
    exit(sig);
  }
}

void main_signals()
{
  signal(SIGINT , (void(*)(int))main_stop);
  signal(SIGSEGV, (void(*)(int))main_stop);
}

