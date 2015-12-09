#include <curses.h>
#include <time.h>
#include <stdio.h>
#include <setjmp.h>

//#include <locale.h>

#include "basment.h"
#include "map.h"


int key_left   = 'h';
int key_down   = 'j';
int key_up     = 'k';
int key_right  = 'l';

bool cheat_mode = false;

#ifdef FORCENAME
bool forcenameprompt = true;
#else
bool forcenameprompt = false;
#endif


char scores_file[DEFLEN];


jmp_buf restart_game;


int main(int argc, char ** argv)
{
  int i;

//  setlocale(LC_ALL, "");

  working_label[0] = '\0';
  
  strcpy(scores_file, "./SCORES");
  
  read_conf();

  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-dvorak") == 0)
    {
      key_left  = 'd';
      key_down  = 'h';
      key_up    = 't';
      key_right = 'n';
    }
    else if (strcmp(argv[i], "-demo") == 0)
    {
      map_demo = true;
    }
    else if (strcmp(argv[i], "-cheat") == 0)
    {
      cheat_mode = true;
    }
    else if (strcmp(argv[i], "-forcename") == 0)
    {
      forcenameprompt = true;
    }
    else if (strcmp(argv[i], "-scores") == 0)
    {
      i++;

      if (i >= argc)
      {
	printf("Please provide a scores file.\n");
	exit(1);
      }

      strncpy(scores_file, argv[i], DEFLEN - 2);
      scores_file[DEFLEN - 1] = '\0';
    }
    else if (strcmp(argv[i], "-hiscore") == 0 ||
	     strcmp(argv[i], "-highscore") == 0)
    {
      show_highscore(HIGHSCORE_TOP_ENTRIES, 0, false);
      exit(0);
    }
    else if (strcmp(argv[i], "-allscores") == 0)
    {
      show_highscore(0, 0, false);
      exit(0);
    }
    else
    {
      printf("What do you mean by \"%s\"?\n", argv[i]);
      exit(1);
    }
  }

  srand(time(NULL));
  
  init_ui();
  init_gfx_map();

  if (map_demo)
  {
    game = malloc(sizeof(game_t));
    fill_automap(2);

    if (game == NULL)
      exit(1);

    generate_map();
  }


/*  addstr("");
  gtch();
  endwin();

  return 0;*/

  title_screen();

  return 0;
}



void new_game(void)
{
  int i;

  title_running = false;
  
  // Start a new game
  game = malloc(sizeof(game_t));

  // This must be set before the jump point; it's reset in game_over
  game->win_streak = 0;
  
  setjmp(restart_game);

  if (game == NULL)
    exit(1);

  enemy_bar = -1;
  enemy_bar_time = 0;
  view_y = 0;
  view_x = 0;
  
  game->total_gold_earned = 0;
  game->monsters_killed = 0;
  game->traps_triggered = 0;
  game->won = false;

  game->tablet_diff = TABLET_START_DIFF;

  reset_trap_tiles();

  generate_map();
  
  new_player();

  /*
    Find the starting position for the player; there should be an
    entrance tile somewhere on the first floor.
  */
  for (i = 0; i < MAP_W; i++)
  {
    if (gtile(FEET_Y, i) == TL_P_ENTRANCE)
      player->x = i;
  }
  
  player->y = FEET_Y;

  stile(player->y, player->x, TL_STAIR_HL);

  calculate_floor();

  recenter(false);

/*
  pwait("HELLO AND WELCOME\n"
	"       TO\n"
	"BASMENT DWELLERS");
*/

  draw_frames();
  draw_stats();
  draw_bars();

  intro();

  update_automap();

  play();

  quit_game();
}



/* Sets up curses */
void init_ui()
{
  initscr();

  board  = NULL;
  stats  = newwin(4, BOARD_W, 0, (COLS - BOARD_W) / 2 + 1);
  lowwin = newwin(4, BOARD_W, BOARD_H + BOARD_T + 2, (COLS - BOARD_W) / 2);
  rwin   = newwin(BOARD_H, 8, BOARD_T, (COLS - BOARD_W) / 2 + BOARD_W + 2);

  cbreak();
  noecho();
  nl();
  curs_set(0);
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  start_color();

  init_pair(PAIR_WHITE,   COLOR_WHITE, COLOR_BLACK);
  init_pair(PAIR_CYAN,    COLOR_CYAN, COLOR_BLACK);
  init_pair(PAIR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(PAIR_GREEN,   COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_RED,     COLOR_RED, COLOR_BLACK);
  init_pair(PAIR_BLUE,    COLOR_BLUE, COLOR_BLACK);
  init_pair(PAIR_BROWN,   COLOR_YELLOW, COLOR_BLACK);
  init_pair(PAIR_BLACK,   COLOR_BLACK, COLOR_BLACK);
  init_pair(PAIR_RED_ON_GREEN, COLOR_RED, COLOR_GREEN);
  init_pair(PAIR_BLACK_ON_RED, COLOR_BLACK, COLOR_RED);
  init_pair(PAIR_CYAN_ON_BLUE, COLOR_CYAN, COLOR_BLUE);
  init_pair(PAIR_BROWN_ON_RED, COLOR_YELLOW, COLOR_RED);
  init_pair(PAIR_RED_ON_BROWN, COLOR_RED, COLOR_YELLOW);
  init_pair(PAIR_GREEN_ON_RED, COLOR_GREEN, COLOR_RED);
  init_pair(PAIR_BLUE_ON_GREEN, COLOR_BLUE, COLOR_GREEN);
  init_pair(PAIR_BROWN_ON_MAGENTA, COLOR_YELLOW, COLOR_MAGENTA);
  init_pair(PAIR_CYAN_ON_GREEN, COLOR_CYAN, COLOR_GREEN);
  init_pair(PAIR_RED_ON_BLUE, COLOR_RED, COLOR_BLUE);
  init_pair(PAIR_LIGHTNING,    COLOR_YELLOW, COLOR_BLACK);
  init_pair(PAIR_BLACK_ON_GREEN, COLOR_BLACK, COLOR_GREEN);
  init_pair(PAIR_GREEN_ON_MAGENTA, COLOR_GREEN, COLOR_MAGENTA);
  init_pair(PAIR_RED_ON_WHITE, COLOR_RED, COLOR_WHITE);
  init_pair(PAIR_BLACK_ON_BLUE, COLOR_BLACK, COLOR_BLUE);
  init_pair(PAIR_WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);
  init_pair(PAIR_BLACK_ON_CYAN, COLOR_BLACK, COLOR_CYAN);
  init_pair(PAIR_WHITE_ON_CYAN, COLOR_WHITE, COLOR_CYAN);

  erase();
  refresh();

  return;
}



/*
  Prepare to end execution; shuts down curses
  and frees allocated memory.
*/
void quit_game()
{
  delwin(board);
  delwin(lowwin);
  delwin(stats);
  delwin(rwin);

  endwin();

  free(game);

  return;
}



