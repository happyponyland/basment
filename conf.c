#include "basment.h"


void read_conf()
{
  int line;
  char * cf;
  char * p;
  bool err = false;

  cf = read_file(CONF_PATH);

  if (cf == NULL)
    return;

  p = strtok(cf, "\n");
  line = 1;

  while (p != NULL)
  {
    if (ffwd_ptr(&p))
      goto next_line;

    if (p[0] == '#')
    {
      goto next_line;
    }
    else if (strncmp(p, "forcename", 9) == 0)
    {
      forcenameprompt = true;
    }
    else if (strncmp(p, "scores", 6) == 0)
    {
      p += 6;
      
      if (ffwd_ptr(&p))
      {
	printf("Expecting scores path in %s, line %d (got end of line)\n", CONF_PATH, line);
	err = true;
	goto next_line;
      }

      char * g;

      g = p;

      while (*g != '\0')
      {
	g++;
	
	if (*g == ' ' || *g == '\t' || *g == '\n')
	  *g = '\0';
      }

      strncpy(scores_file, p, DEFLEN - 2);
      scores_file[DEFLEN - 1] = '\0';

      goto next_line;
    }
    else
    {
      printf("Unknown option in %s, line %d: %s\n", CONF_PATH, line, p);
      err = true;
    }
    
  next_line:
    p = strtok(NULL, "\n");
    line++;
  }

  free(cf);

  if (err)
    exit(1);

  return;
}



/*
  Advances the pointer at P to the first character that isn't
  whitespace. Returns true if the end of the string is reached,
  false if there are more characters.
*/
bool ffwd_ptr(char ** p)
{
  if (p == NULL || *p == NULL)
    return true;

  while (1)
  {
    if (**p == '\0')
      return true;
    else if (**p == ' ' || **p == '\t' || **p == '\n')
      (*p)++;
    else
      return false;
  }
}
