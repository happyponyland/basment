#include "basment.h"



void shuffle_books()
{
  int i;
  int b;
  int t;

  for (i = 0; i < BOOKS; i++)
    game->book[i] = i;

  for (i = 0; i < BOOKS; i++)
  {
    b = (i + (1 + rand() % (BOOKS - 1))) % BOOKS;
    t = game->book[i];
    game->book[i] = game->book[b];
    game->book[b] = t;
  }

  return;
}



void bookshelf()
{
  char line[DEFLEN];
  char bookname[DEFLEN];
  int i;

  int st_change = 0;
  int sp_change = 0;
  int exp = 0;

  decorate(player->y, player->x, DEC_EMPTY_SHELF);

  bookname[0] = '\0';

  if (game->next_book >= BOOKS)
  {
    return;
  }

  i = game->book[game->next_book];

  switch (i)
  {
  case 0:
    strcpy(bookname,
	   "\"HOW TO CARE FOR\n"
	   "YOUR PET DRAGON\"");

    exp = 100;
    break;

  case 1:
    strcpy(bookname,
	   "\"THE MASOCHISTS' GUIDE\n"
	   " TO THIGH WORKOUT\"\n\n"
	   "YOU FEEL STRONGER!");

    st_change = +2;
    draw_stats();
    break;

  case 2:
    strcpy(bookname,
	   "\"A MANUAL OF LOCKS\n"
	   "(AND HOW TO PICK THEM)\"");

    game->skill_lockpick = true;
    draw_stats();
    break;

  case 3:
    strcpy(bookname,
	   "\"DUNGEON SURVIVAL 101:\n"
	   " HOW TO DETECT TRAPS\"");

    learn_detect_traps();
    draw_stats();
    break;

  case 4:
    strcpy(bookname,
	   "\"THE GRAVE-ROBBERS TOP 10\n"
	   " BACK-STRENGTHENING EXERCISES\"\n\n"
	   "YOU FEEL STRONGER!");

    st_change = +2;
    draw_stats();
    break;

  case 5:
    strcpy(bookname,
	   "\"GNOBLIN EROTICA VOL. 2\"\n\n"
	   "UHHH ...");
    exp = -200;
    break;

  case 6:
    strcpy(bookname,
	   "\"MEMOIRS OF A DEATH KNIGHT:\n"
	   " HOW I STOPPED CARING\n"
	   " AND JOINED THE UNDEAD\"");
    exp = 200;
    break;

  case 7:
    strcpy(bookname,
	   "\"ON THE IMPORTANCE OF LICHEN\"");
    exp = 400;
    break;

  case 8:
    strcpy(bookname,
	   "\"MY HAMSTER DIED\"\n\n"
	   "THAT WAS SERIOUSLY DEPRESSING");
    exp = 600;
    break;

  case 9:
    strcpy(bookname,
	   "\"FORBIDDEN KNOWLEDGE\"\n\n"
	   "YOU FEEL A LITTLE BIT GUILTY NOW");
    exp = 700;
    game->piety -= 500;
    break;

  case 10:
    strcpy(bookname,
	   "\"BUSINESS PRACTICES\"");
    exp = 200;
    break;
  }

  game->next_book++;

//book_read:
  
  if (bookname[0])
  {
    if (exp)
    {
      snprintf(line, DEFLEN,
	       "YOU FIND A BOOK:\n\n%s\n\nYOU GET %d EXP",
	       bookname, exp);
    }
    else
    {
      snprintf(line, DEFLEN,
	       "YOU FIND A BOOK:\n\n%s",
	       bookname);
    }
    
    draw_board();
    pwait(line);

    change_pl_st(st_change);
    change_pl_sp(sp_change);

    draw_stats();

    draw_board();

    if (exp)
    {
      give_exp(exp);
    }
  }
  

  return;
}
