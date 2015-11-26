#include <ctype.h>

#include "basment.h"


int title_frame;

int title_running;


void title_screen(void)
{
  int inkey;
  int mode;
  int t;
  int l_edge;

  title_running = true;
  
  board = newwin(7, BOARD_W, 16, (COLS - BOARD_W) / 2);
  mode = 0;
  title_frame = 0;
  l_edge = (COLS - BOARD_W) / 2;

redraw_title:

  erase();

  if (mode == 0)
  {
    // Regular title screen

    t = 0;

    attrset(COLOR_PAIR(PAIR_RED));
   
    mvaddstr(t++, l_edge, "           ___   _   ___ __  __ ___ _  _ _____ ");
    mvaddstr(t++, l_edge, "          | _ ) / \\ / __|  \\/  | __| \\| |_   _|");
    mvaddstr(t++, l_edge, "          | _ \\/ _ \\\\__ \\ |\\/| | __| .  | | |  ");
    mvaddstr(t++, l_edge, "          |___/_/ \\_\\___/_|  |_|___|_|\\_| |_|  ");
    mvaddstr(t++, l_edge, "         ___  _    _ ___ _    _    ___ ___  ___ ");
    mvaddstr(t++, l_edge, "        |   \\| |  | | __| |  | |  | __|   \\/ __|");
    mvaddstr(t++, l_edge, "        |    | |/\\| | __| |__| |__| __|   /\\__ \\");
    mvaddstr(t++, l_edge, "        |___/|__/\\__|___|____|____|___|_|_\\|___/");
    
    attrset(0);
    
    t++;
    move(t++, l_edge);
    
    addstr("            PRESS  ");
    attrset(COLOR_PAIR(PAIR_BLACK) | A_BOLD); addstr(">>"); attrset(0);
    addstr(" ENTER ");
    attrset(COLOR_PAIR(PAIR_BLACK) | A_BOLD); addstr("<<"); attrset(0);
    addstr("  TO START GAME");
    
    t++;
    mvaddstr(t++, l_edge, "    \"H\" FOR HELP   \"S\" TO VIEW HIGH SCORES   \"Q\" TO QUIT ");
  }
  else if (mode == 1)
  {
    // Help screen

    t = 1;

    move(t++, l_edge);
    addstr("\" ");
    attrset(COLOR_PAIR(PAIR_GREEN));
    addstr("BASMENT DWELLERS");
    attrset(0);
    addstr(" \" IS A GAME ABOUT COLLECTING TREASURE");

    mvaddstr(t++, l_edge, "                    AND SLAYING MONSTERS");
    t++;
    mvaddstr(t++, l_edge, "CONTROL YOUR CHARACTER WITH THE DIRECTIONAL KEYS");
    mvaddstr(t++, l_edge, "\" UP \", \" DOWN \", \" LEFT \", \" RIGHT \"");
    t++;
    mvaddstr(t++, l_edge, "PRESS \" UP \" TO INTERACT WITH ENVIRONMENT");
    t++;
    mvaddstr(t++, l_edge, "PRESS \" SPACE \" TO WAIT A TURN, SHOOT YOUR BOW");
    mvaddstr(t++, l_edge, "                   OR BLOCK (IF U HAVE A SHIELD)");
    t++;
    mvaddstr(t++, l_edge, "\" M \" TO VIEW MAP");

  }
    
  // Footer
  attrset(COLOR_PAIR(PAIR_BLACK) | A_BOLD);
  
  move(23, l_edge);
  addstr("HAPPYPONYLAND.NET");
  
  move(23, l_edge + BOARD_W - strlen("VERSION " BD_VERSION));
  addstr("VERSION " BD_VERSION);
  
  attrset(0);

  refresh();

  title_anim();

  while(1)
  {
    nodelay(stdscr, true);

    while(1)
    {
      inkey = getch();

      if (inkey != ERR)
	break;

      title_anim();
      lpause();
    }

    inkey = toupper(inkey);
    
    nodelay(stdscr, false);

    if (mode == 1)
    {
      mode = 0;
      goto redraw_title;
    }
    else if (inkey == 'Q')
    {
      quit_game();
      return;
    }
    else if (inkey == 'S')
    {
      werase(board);
      wrefresh(board);
      show_highscore(10, 0, true);
      goto redraw_title;
    }
    else if (inkey == 'H')
    {
      mode = 1;
      goto redraw_title;
    }
    else if (inkey == 'N' || inkey == '\n')
    {
      // New game
      erase();
      refresh();
      delwin(board);
      board = newwin(BOARD_H, BOARD_W + 1, BOARD_T + 1, (COLS - BOARD_W) / 2);
      new_game();
    }
  }


  erase();
  refresh();

  return;
}



int title_p_x;
int title_p_flags;
int title_p_flip;
int title_e_x;
int title_e_y;
int title_e_flags;
int title_e_type;
int title_e_flip;
int title_hole;
int title_hole_pos;


void title_anim()
{
  int i;

  werase(board);

  wmove(board, 0, 0);

  for (i = 0; i < BOARD_W; i++)
    waddch(board, ACS_HLINE | A_REVERSE);

  wmove(board, 6, 0);

  for (i = 0; i < BOARD_W; i++)
    waddch(board, ACS_HLINE | A_REVERSE);

//  wrefresh(board);

#define TITLE_RESTART           0
#define TITLE_WAIT              (TITLE_RESTART + 16)
#define TITLE_PLAYER_APPEAR     (TITLE_WAIT + 40)
#define TITLE_APPROACH_SPIDER   (TITLE_PLAYER_APPEAR + 8)
#define TITLE_SPIDER_COMBAT     (TITLE_APPROACH_SPIDER + 8)
#define TITLE_ROGUE_APPEAR      (TITLE_SPIDER_COMBAT + 24)
#define TITLE_ROGUE_COMBAT      (TITLE_ROGUE_APPEAR + 20)
#define TITLE_ROGUE_RUN         (TITLE_ROGUE_COMBAT + 12)
#define TITLE_WALK_EAST         (TITLE_ROGUE_RUN + 53)
#define TITLE_PANIC             (TITLE_WALK_EAST + 12)

  if (title_frame == TITLE_RESTART)
  {
    title_p_x = -10;
    title_p_flags = GFX_HUMAN_ARMOR1 | GFX_HUMAN_PLAYER | GFX_HUMAN_DAGGER;
    title_p_flip = false;

    title_e_x = -34;
    title_e_y = 5;
    title_e_flags = 0;
    title_e_type = MOB_SPIDER;
    
    title_hole = 0;
  }
  else if (title_frame < TITLE_WAIT)
  {
  }
  else if (title_frame == TITLE_WAIT)
  {
//    title_p_x++;
  }
/*  else if (title_frame == 25 || title_frame == 15 || title_frame == 10)
  {
    title_e_x += 1;
    }*/
  else if (title_frame < TITLE_PLAYER_APPEAR)
  {
    if (title_frame == TITLE_PLAYER_APPEAR - 26 ||
	title_frame == TITLE_PLAYER_APPEAR - 21 ||
	title_frame == TITLE_PLAYER_APPEAR - 7)
    {
    }
    else
      title_p_x += 1;

    title_e_x += 1;
  }
  else if (title_frame == TITLE_PLAYER_APPEAR)
  {
    title_p_flip = true;
  }
  else if (title_frame == 38)
  {
    title_e_x += 1;
  }
  else if (title_frame < TITLE_APPROACH_SPIDER)
  {
    if (title_frame % 8)
      title_p_x -= 1;

    title_e_x += 1;
  }
  else if (title_frame < TITLE_SPIDER_COMBAT)
  {
    if (title_frame % 2)
      title_e_flags ^= GFX_HURT;
    else
      title_p_flags ^= GFX_ATTACK;
  }
  else if (title_frame == TITLE_SPIDER_COMBAT)
  {
    title_e_x = 39;
    title_e_y = -1;
    title_e_type = MOB_ROGUE;
    title_e_flags = 0;
    title_e_flip = false;
  }
  else if (title_frame == TITLE_ROGUE_APPEAR - 7
	   || title_frame == TITLE_ROGUE_APPEAR - 14
	   || title_frame == TITLE_ROGUE_APPEAR - 21)
  {
  }
  else if (title_frame < TITLE_ROGUE_APPEAR)
  {
    title_p_flip = false;
    title_p_x += 1;
    title_e_x -= 1;
  }
  else if (title_frame == TITLE_ROGUE_APPEAR)
  {
    title_hole_pos = 0;

    title_hole = 1;
  }
  else if (title_frame == TITLE_ROGUE_APPEAR + 1)
  {
    title_hole = 2;
  }
  else if (title_frame == TITLE_ROGUE_APPEAR + 2)
  {
    title_hole = 3;
  }
  else if (title_frame == TITLE_ROGUE_APPEAR + 3)
  {
    title_p_flip = true;
  }
  else if (title_frame < TITLE_ROGUE_APPEAR + 10)
  {
    title_e_y++;
  }
  else if (title_frame < TITLE_ROGUE_APPEAR + 13)
  {
    title_hole--;
  }
  else if (title_frame < TITLE_ROGUE_COMBAT)
  {
    title_p_x--;
    title_e_x++;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT)
  {
    title_e_flags ^= GFX_ATTACK;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 1)
  {
    title_e_flags ^= GFX_ATTACK;
    title_p_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 2)
  {
    title_p_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 3)
  {
    title_p_flags ^= GFX_ATTACK;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 4)
  {
    title_p_flags ^= GFX_ATTACK;
    title_e_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 5)
  {
    title_e_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 6)
  {
    title_e_flags ^= GFX_ATTACK;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 7)
  {
    title_e_flags ^= GFX_ATTACK;
    title_p_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 8)
  {
    title_p_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 9)
  {
    title_p_flags ^= GFX_ATTACK;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 10)
  {
    title_p_flags ^= GFX_ATTACK;
    title_e_flags ^= GFX_HURT;
  }
  else if (title_frame == TITLE_ROGUE_COMBAT + 11)
  {
    title_e_flags ^= GFX_HURT;
  }
  else if (title_frame < TITLE_ROGUE_RUN)
  {
    title_e_flip = false;

    if (title_frame % 3)
      title_e_x--;
  }
  else if (title_frame < TITLE_ROGUE_RUN + 4)
  {
    if (title_frame % 3)
      title_e_x--;

    title_p_flags ^= GFX_ATTACK;
    title_hole_pos = 6;
  }
  else if (title_frame < TITLE_ROGUE_RUN + 7)
  {
//    title_p_x--;
    title_hole++;
  }
  else if (title_frame < TITLE_ROGUE_RUN + 12)
  {
    title_e_y++;
  }
  else if (title_frame < TITLE_ROGUE_RUN + 15)
  {
    title_hole--;
  }
  else if (title_frame < TITLE_ROGUE_RUN + 17)
  {
    title_p_flip = false;
  }
  else if (title_frame < TITLE_WALK_EAST)
  {
    if (title_frame % 7 > 1)
      title_p_x++;
  }
  else if (title_frame == TITLE_WALK_EAST)
  {
    title_p_flags ^= GFX_HUMAN_FALL1;
  }
  else if (title_frame < TITLE_WALK_EAST + 4)
  {
    title_p_flags ^= GFX_HUMAN_FALL1;
    title_p_flags ^= GFX_HUMAN_FALL2;
  }
  else if (title_frame == TITLE_WALK_EAST + 4)
  {
    title_p_flags ^= GFX_HUMAN_FALL2;
    title_e_type = MOB_GIANT;
    title_e_flip = true;
    title_e_x = BOARD_W + 4;
    title_e_y = 5;
    title_p_flip = true;
  }
  else if (title_frame < TITLE_PANIC)
  {
    title_p_x -= 2;
    title_e_x --;
  }
  else if (title_frame < TITLE_PANIC + 4)
  {
    title_p_x -= 2;
    title_e_flags ^= GFX_ATTACK;
  }
  else if (title_frame < TITLE_PANIC + 6)
  {
    title_p_x -= 2;
  }
  else if (title_frame < TITLE_PANIC + 8)
  {
    title_p_x -= 2;
    title_e_flags ^= GFX_ATTACK;
  }
  else if (title_frame < TITLE_PANIC + 16)
  {
    title_e_flip = false;
    title_p_x -= 2;
    title_e_x++;
  }
  
  if (title_hole > 0)
  {
    mvwaddch(board, title_hole_pos, title_e_x, ' ');
  }

  if (title_hole > 1)
  {
    mvwaddch(board, title_hole_pos, title_e_x - 1, ' ');
    mvwaddch(board, title_hole_pos, title_e_x + 1, ' ');
  }

  if (title_hole > 2)
  {
    mvwaddch(board, title_hole_pos, title_e_x - 2, ' ');
    mvwaddch(board, title_hole_pos, title_e_x + 2, ' ');
  }

  draw_human(5, title_p_x, MOB_PLAYER, title_p_flip, title_p_flags);
  draw_thing(NULL, title_e_y, title_e_x, title_e_type, title_e_flip, title_e_flags);

  wrefresh(board);

  title_frame++;

  return;
}
