#include <sys/time.h>

#include "basment.h"


/* Causes a short delay */
void spause()
{
  delay(20);
}


/* Causes a long delay */
void lpause()
{
  delay(150);
}


/* Causes a very long delay */
void opause()
{
  delay(500);
}



#ifdef _WIN32
#include "windows.h"
#endif

/* Delays execution for @ms milliseconds */
void delay(long ms)
{
#ifdef _WIN32

  DWORD tiem;
  DWORD wait;

  tiem = timeGetTime();
  
  wait = tiem + ms;
  
  do
  {
    tiem = timeGetTime();
  } while (tiem < wait);
  
#else

  long wait;
  long now;
  struct timeval tv;
  
  gettimeofday(&tv, NULL);

  wait = tv.tv_sec * 1000 + tv.tv_usec / 1000 + ms;

  do
  {
    gettimeofday(&tv, NULL);
    now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  }
  while (now < wait);
#endif

  return;
}



/* Discards all keyboard input waiting */
void flush_input()
{
  nodelay(stdscr, true);
  while (getch() != ERR) { }
  nodelay(stdscr, false);

  return;
}
