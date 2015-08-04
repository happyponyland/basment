#include "basment.h"



int keep_in_range(int a, int b, int c)
{
  if (b > c)
    return c;

  if (b < a)
    return a;

  return b;
}
