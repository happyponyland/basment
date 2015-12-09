#include <sys/stat.h>

#include "basment.h"



void blank_score(score_t * score)
{
  int i;

  for (i = 0; i < SCORE_ITEMS; i++)
  {
    score->label[i][0] = 0;
    score->amount[i] = 0;
    score->multi[i] = 0;
  }

  return;
}


void make_score(score_t * score)
{
  int temp;
  
  blank_score(score);

  add_score(score, "EXPERIENCE", game->player_exp, 1);
  add_score(score, "GOLD EARNED", game->total_gold_earned, SCORE_GOLD_MULT);

  if (game->max_floor > 1)
    add_score(score, "MAX DEPTH", game->max_floor, SCORE_MAX_DEPTH);
  
  if (game->weapon > WPN_DAGGER)
    add_score(score, "WEAPON BONUS", game->weapon, 100);

  add_score(score, "ARMOR BONUS", player->armor_type, SCORE_ARMOR_MULT);

  if (game->won)
    add_score(score, "WINNER BONUS", 1, SCORE_WIN_BONUS);

  temp = (game->skill_lockpick ? 1 : 0) + (game->skill_detect_traps ? 1 : 0);
  add_score(score, "SKILLS", temp, SCORE_SKILLS);
  
  temp = (game->has_torch ? 1 : 0) + (game->has_torch ? 1 : 0);
  add_score(score, "TOOLS", temp, SCORE_TOOLS);
  
  add_score(score, "TURNS TAKEN", game->turns, SCORE_TURN_PEN);

  add_score(score, "TRAPS SPRUNG", game->traps_triggered, SCORE_TRAP_PEN);


  return;
  
//  sum += (player->strength - 1) * SCORE_ATTR_MULT;
//  sum += MAX(0, player->speed - 10) * SCORE_ATTR_MULT;

/*  if (game->skill_lockpick)
   sum += SCORE_PER_SKILL;
  if (game->skill_detect_traps)
  sum += SCORE_PER_SKILL;*/

  // Penalties
//  sum += game->monsters_killed * SCORE_MONSTER_PEN;
//  sum += game->traps_triggered * SCORE_TRAP_PEN;

//  sum += game->turns * SCORE_TURN_PEN;

//  if (sum < 0)
//    return 0;
}


void list_score(score_t * score)
{
  int i;
  int x = 50;
  int y = 1;
  int total;
  int lines = 0;

  for (i = 0; i < SCORE_ITEMS; i++)
  {
    if (score->label[i][0] == 0)
      break;

    lines++;
  }

  lines += 2; // For total
      
    
  for (i = 0; i < SCORE_ITEMS; i++)
  {
    if (score->label[i][0] == 0)
      break;

    mvprintw(y, x, "%-13s %6d X %-5d", score->label[i], score->amount[i], score->multi[i]);

    refresh();
    lpause();
    
    y++;
  }

  total = calc_score(score);
  
  y++;
  mvprintw(y, x, "%-12s %6d", "TOTAL", total);

  return;
}


void add_score(score_t * score, char * new_label, int new_amount, int new_multi)
{
  int i;

  if (new_amount == 0)
    return;

  for (i = 0; i < SCORE_ITEMS; i++)
  {
    if (score->label[i][0] == 0)
    {
      snprintf(score->label[i], DEFLEN, "%s", new_label);
      score->amount[i] = new_amount;
      score->multi[i] = new_multi;
      return;
    }
  }

  return;
}


int calc_score(score_t * score)
{
  int i;
  int total = 0;

  for (i = 0; i < SCORE_ITEMS; i++)
  {
    if (score->label[i][0] == 0)
      break;

    total += score->amount[i] * score->multi[i];
  }

  return total;
}



/*
  Calculates player score for the current game. See SCORE_* in rules.h
 for weighting.
*/
int calculate_score()
{
/*  int sum = 0;

  sum += game->player_exp;
  sum += (game->player_level - 1) * SCORE_PER_LEVEL;
  sum += game->total_gold_earned * SCORE_GOLD_MULT;

  if (game->skill_lockpick)
    sum += SCORE_PER_SKILL;

  if (game->skill_detect_traps)
    sum += SCORE_PER_SKILL;

  if (game->weapon > WPN_DAGGER)
    sum += SCORE_WEAPON;

  sum += player->armor_type * SCORE_ARMOR_MULT;

  sum += (player->strength - 1) * SCORE_ATTR_MULT;
  sum += MAX(0, player->speed - 10) * SCORE_ATTR_MULT;

  sum += (game->max_floor - 1) * SCORE_FLOOR_BONUS;

  if (game->won)
    sum += SCORE_WIN_BONUS;

  // Penalties
  sum += game->monsters_killed * SCORE_MONSTER_PEN;
  sum += game->traps_triggered * SCORE_TRAP_PEN;

  sum += game->turns * SCORE_TURN_PEN;

  if (sum < 0)*/
    return 0;

//  return sum;
}



/*
  Adds SCORE to highscore table, with character NAME and CAUSE of
  death. Returns the place the new entry ended up in, or 0 if it
  wasn't added to the table at all.
*/
int add_highscore(long score, char * name, char * cause)
{
  char * old_file;
  long this_one = 0;
  int new_place = 0;
  int place = 1;
  char * p;
  char * dumb = "";
  FILE * out;

  // Read the current highscore table
  old_file = read_file(scores_file);

  // If we can't read the current table, fake an empty file
  if (old_file == NULL)
    old_file = dumb;

  // Open the same file for writing
  out = fopen(scores_file, "w");

  if (out == NULL)
    return 0;

  // We'll work on it line by line; split on newline
  p = strtok(old_file, "\n");

  // Sort the new entry into the highscore table
  bool listed = false;

  /*
    Keep doing this until a) the new entry has been added and b) we
    have gone through all old entries and added them back to the
    table. 
  */
  // TODO: This would be a good place to limit the number of highscore entries.

  while (!listed || p != NULL)
  {
    /*
      Read a highscore entry and convert its score (first word) to
      numeric. If we're starting from an empty file (p is NULL) we
      will allow only one iteration. We will fake a score (lower than
      you can ever get) so the new entry is added and nothing else.
    */

    if (p == NULL)
      this_one = -1;
    else
      this_one = strtol(p, NULL, 10);

    /*
      If the new entry has a higher score, insert it before the old
      entry and set it as "listed" so we don't add it multiple times.
      Print new and old entries back to the highscore table file.
   */

    if (!listed && score > this_one)
    {
      fprintf(out, "%ld %s, %s\n", score, name, cause);
      listed = true;
      
      // Remember which place we stored this at
      new_place = place;
      place++;
    }

    /*
      Break if this was an empty score file.
      The new file should only have a single entry.
    */
    if (p == NULL)
      break;

    // Print old entry
    fprintf(out, "%ld %s\n", this_one, strchr(p, ' ') + 1);
    
    place++;

    // Get next line
    p = strtok(NULL, "\n");
  }

  // We're done writing
  fclose(out);

  // Free memory if we read the highscore file
  if (old_file != dumb && old_file != NULL)
    free(old_file);

  // Return the place the entry ended up in
  return new_place;
}



/*
  List the first highscore TOP_ENTRIES and entries HIGHLIGHT +/- 1. If
  TOP_ENTRIES is less than one, all entries will be listed. If FANCY
  is set curses will be used to display the table, otherwise it will
  be sparsely formatted and written to stdout.
*/
void show_highscore(int top_entries, int highlight, bool fancy)
{
  char * old_file;
  char * p;

  int i;
  int place = 1;
  long this_one;
  bool spacer = false;

  int y;

  // Read the scores file
  old_file = read_file(scores_file);

  if (fancy)
  {
    erase();

    move(1, 1);

    attrset(COLOR_PAIR(PAIR_BLACK) | A_BOLD);

    addch(ACS_ULCORNER);

    for (i = 1; i < COLS - 3; i++)
      addch(ACS_HLINE);

    addch(ACS_URCORNER);

    for (i = 2; i < 22; i++)
    {
      mvaddch(i, 1, ACS_VLINE);
      mvaddch(i, COLS - 2, ACS_VLINE);
    }

    move(LINES - 2, 1);
    
    addch(ACS_LLCORNER);

    for (i = 1; i < COLS - 3; i++)
      addch(ACS_HLINE);

    addch(ACS_LRCORNER);
    attrset(0);

    mvaddstr(1, (COLS - strlen(HIGHSCORE_TITLE)) / 2,
	     HIGHSCORE_TITLE);

    mvaddstr(LINES - 2, (COLS - strlen(HIGHSCORE_ANY_KEY)) / 2,
	     HIGHSCORE_ANY_KEY);
    
  }
  else
  {
    printf("\n  == DE BESTE BASMENT DWELLERS ===========\n\n");
  }

  if (old_file == NULL)
  {
    if (fancy)
    {
      mvaddstr(4, 20, "THERE ARE NO HIGHSCORES :(");
      goto press_any_key;
    }
    else
    {
      printf("\n   THERE ARE NO HIGHSCORES :(\n\n");
      return;
    }
  }

  y = 3;

  // Split it into lines, work through each line
  p = strtok(old_file, "\n");

  while (p != NULL)
  {
    /*
      Print this score only if it's in the top_entries (usually 5) or
      it's in place highlight +/- 1. We want to show who the best players
      are and where the new one ended up.
    */
    if (place <= top_entries ||
	(place >= highlight - 1 &&
	 place <= highlight + 1) ||
	top_entries < 1)
    {
      // Convert score to numeric format, so we can reformat it!
      this_one = strtol(p, NULL, 10);
      
      // Look for a space on the line. If there is none it's an invalid entry.
      p = strchr(p, ' ');

      if (p == NULL)
	continue;

      // Name + cause of death starts after the space
      p++;

      // Attempt some nice formatting. If it's the highlight entry, highlight it.

      if (fancy)
      {
	if (place == highlight)
	  attrset(A_BOLD);

	mvprintw(y, 6,
		 "#%-4d %8ld  %s",
		 place, this_one, p);

	if (place == highlight)
	{
	  mvaddstr(y, 2, ">> ");
	  mvaddstr(y, COLS - 4, "<<");
	  attrset(0);
	}

	y ++;
      }
      else
      {
	printf("%s #%-4d %-9ld %s%s\n",
	       (place == highlight ? ">>" : "  "),
	       place, this_one, p,
	       (place == highlight ? " <<" : ""));
      }
    }
    else if (!spacer)
    {
      /*
	This entry isn't in the interval we wish to show. If we have
	already shown the highlighted entry there's no use continuing
	(we won't show anything more). If we haven't shown it already,
	we should instead print a ... spacer. Only do this once,
	though!
      */

      if (highlight < place)
	goto clean_up;

      if (fancy)
      {
	y++;
	mvaddstr(y, 6, "...");
	y++;
	y++;
      }
      else
      {
	printf("\n ... \n\n");
      }

      spacer = true;
    }

    place++;
    p = strtok(NULL, "\n");
  }
  
clean_up:
  free(old_file);

  if (fancy)
  {
    move(LINES - 1, COLS - 1);
    refresh();
  }
  else
  {
    printf("\n  ========================================\n\n");
  }

press_any_key:
  getch();

  return;
}



/*
  Reads FILENAME into a char array. Returns NULL if it could not be read.
*/
char * read_file(char * filename)
{
  char * result;
  struct stat file_stat;
  int size;
  FILE * f;

  f = fopen(filename, "r");
    
  if (f == NULL)
    return NULL;

  result = NULL;

  stat(filename, &file_stat);

  size = file_stat.st_size;

  /* Make sure to get an extra byte for the \0 */
  result = malloc(size + 1);

  if (result == NULL)
    return NULL;

  fread(result, 1, size, f);

  fclose(f);

  /* Terminate the string */
  result[size] = '\0';

  return result;
} /* read_file */
