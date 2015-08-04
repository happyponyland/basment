#include "basment.h"


/* Prints MSG and waits for confirmation */
void pwait(char * msg)
{
  int inp;

  popup(msg, -1, 1);

  do
  {
    inp = getch();
  }
  while (inp != ' ' && inp != '\n');

  return;
}


/* Prints msg and gives the player a left/right prompt */
int psel(char * msg)
{
  popup(msg, -1, 1);

  int input;

  while (1)
  {
    input = getch();

    if (input == KEY_LEFT || input == key_left)
      return 0;
    else if (input == KEY_RIGHT || input == key_right)
      return 1;
  }
}



int pchoose(char * msg, int start_row, int items, int options)
{
  int input;
  int sel;

  sel = 0;

  while (1)
  {
    popup(msg, start_row + sel, 0);
    
    input = getch();

/*    mvprintw(0, 0, "%d   ", input);
    refresh();
    getch();*/

    if (sel > 0 && input == KEY_UP)
    {
      sel--;
    }
    else if (sel < items - 1 && input == KEY_DOWN)
    {
      sel++;
    }
    else if (input == '\n')
    {
      return sel;
    }
    else if ((options & POPUP_LEAVE_LEFT) &&
	     ((input == KEY_LEFT) || (input == key_left)))
    {
      return -1;
    }
    else if ((options & POPUP_LEAVE_RIGHT) &&
	     ((input == KEY_RIGHT) || (input == key_right)))
    {
      return -1;
    }
    else if (input == ' ')
    {
      return -1;
    }
  }

  // Won't get here
}



/*
  Draws a small box and prints MSG. The height and width will be
  adjusted after the size of the message. FLAGS is a bitmask with
  extra options (see POPUP_* constants).
*/
void popup(char * msg, int hlight, int flags)
{
  int lines;
  int w;
  int max_w;
  char * p;

  /* Count the number of lines and the width of the longest line */
  lines = 1;
  max_w = 0;
  w = 0;
  p = msg;

  while (*p != '\0')
  {
    if (*p == '\n')
    {
      w = 0;
      lines++;
    }
    else
    {     
      w++;

      if (w > max_w)
	max_w = w;
    }
    
    p++;
  }

  /* Display the message */
  int y; int x;
  int t; int l;
  int c; int d;
  int a;

  /* Box position */
  t = 3;
  l = BOARD_W / 2 - max_w / 2 - 1;

  c = PAIR_RED;

  p = msg;

  wattrset(board, 0);

  /* Upper edge */
  wmove(board, t - 2, l - 2);
  waddch(board, ACS_ULCORNER | COLOR_PAIR(c));

  for (x = 0; x < max_w + 2; x++)
    waddch(board, ACS_HLINE | COLOR_PAIR(c));

  waddch(board, ACS_URCORNER | COLOR_PAIR(c));

  /* Empty first row */
  wmove(board, t - 1, l - 2);
  waddch(board, ACS_VLINE | COLOR_PAIR(c));

  for (x = 0; x < max_w + 2; x++)
    waddch(board, ' ');

  waddch(board, ACS_VLINE | COLOR_PAIR(c));

  /* Draw each line of text, padded with space and box */
  for (y = 0; y < lines; y++)
  {
    wmove(board, t + y, l - 2);
    waddch(board, ACS_VLINE | COLOR_PAIR(c));
    waddch(board, ' ');

    x = max_w;
    d = 0;

    if (hlight == y)
      a = A_REVERSE;
    else
      a = 0;

    while (x)
    {
      if (*p == '\n' || *p == '\0')
      {
	while (x--)
	  waddch(board, ' ' | a);

	break;
      }
      else
      {
	if (*p == '#')
	{
	  int left;
	  int fill;

	  left = strlen(p + 1) + 1;
	  fill = max_w - d - left;

	  waddch(board, ' ' | a);

	  while (fill--)
	  {
	    x--;
	    waddch(board, ' ' | a);
	  }
	}
	else
	{
	  waddch(board, *p | a);
	  d++;
	}

	p++;
	x--;
      }
    }

    waddch(board, ' ' | a);
    waddch(board, ACS_VLINE | COLOR_PAIR(c));
    
    if (*p == '\0')
      break;

    p++;
  }

  /* Empty bottom row */
  wmove(board, t + lines, l - 2);
  waddch(board, ACS_VLINE | COLOR_PAIR(c));

  for (x = 0; x < max_w + 2; x++)
    waddch(board, ' ');

  waddch(board, ACS_VLINE | COLOR_PAIR(c));

  /* Bottom edge */
  wmove(board, t + lines + 1, l - 2);
  waddch(board, ACS_LLCORNER | COLOR_PAIR(c));

  for (x = 0; x < max_w + 2; x++)
    waddch(board, ACS_HLINE | COLOR_PAIR(c));

  waddch(board, ACS_LRCORNER | COLOR_PAIR(c));

  wattrset(board, 0);

  /* Displays ... at the bottom of the popup */
  if (flags & POPUP_ELLIPSIS)
  {
    wmove(board, t + lines + 1, l + max_w - 5);
    waddch(board, ' ');
    waddch(board, PORTABLE_DOT | A_BOLD);
    waddch(board, PORTABLE_DOT | A_BOLD);
    waddch(board, PORTABLE_DOT | A_BOLD);
    waddch(board, ' ');
  }

  wrefresh(board);

  return;
}
