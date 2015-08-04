#include <ncurses.h>


int main()
{
  initscr();

  cbreak();
  noecho();
  nl();
  curs_set(0);
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  erase();
  addstr("BASMENT DWELLERS");
  getch();
  refresh();

  endwin();

  

  return;
}
