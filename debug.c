
#include <stdio.h>
#include <stdarg.h>

#include "cra.h"

static int dodebug = 0;

void debug(const char *fmt, ...)
{
  if(dodebug == 0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}

void debug_set(int state)
{
  dodebug = state;
}

