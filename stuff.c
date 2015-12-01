#include "basment.h"



int keep_in_range(int a, int b, int c)
{
  if (b > c)
    return c;

  if (b < a)
    return a;

  return b;
}



/**
   Returns -1 or +1.
*/
int rnd_dir()
{
  if (rand() % 2)
    return -1;
  else
    return +1;
}
