#include "basment.h"



char working_label[DEFLEN];

int automap_view_y = 0;



void now_working(const char * func)
{
  snprintf(working_label, DEFLEN, "%s", func);
  return;
}



/*
  Adds the area around the players position to the automap.
*/
void update_automap(void)
{
  int y;
  int x;
  
  y = player->y / FLOOR_H;
  x = player->x / CELL_TO_TILES;

  y = MAX(0, MIN(MAX_FLOORS - 1, y));
  x = MAX(1, MIN(CELLS_W - 2, x));

  game->automap[y][x]     |= AUTOMAP_VISITED;
  game->automap[y][x - 2] |= AUTOMAP_VISITED;
  game->automap[y][x - 1] |= AUTOMAP_VISITED;
  game->automap[y][x + 1] |= AUTOMAP_VISITED;
  game->automap[y][x + 2] |= AUTOMAP_VISITED;
  
  return;
}



void fill_automap(int mode)
{
  int y;
  int x;

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      if (mode == 0)
	game->automap[y][x] = AUTOMAP_BLANK;
      else if (mode == 1)
	game->automap[y][x] |= AUTOMAP_KNOWN;
      else if (mode == 2)
	game->automap[y][x] = (AUTOMAP_KNOWN | AUTOMAP_VISITED);
    }
  }

  return;
}



/*
  Draws the map of generator cells. This will overwrite the whole
  stdscr.
*/
void draw_cellmap()
{
  int y;
  int x;
  int sc_y;

  chtype attr = 0;
  chtype glyph = ' ';

  erase();

  for (y = automap_view_y; y < automap_view_y + 24; y++)
  {
    sc_y = y % 24;
    move(sc_y, 0);

    for (x = 0; x < CELLS_W; x++)
    {
      attr = 0;

      if (!map_demo && game->automap[y][x] == AUTOMAP_BLANK)
      {
	addch(' ');
	continue;
      }

      if (game->cell[y][x] == CELL_TRAP && game->automap[y][x] & AUTOMAP_KNOWN)
      {
	glyph = ACS_HLINE;
	attr = COLOR_PAIR(PAIR_GREEN);
      }
      else
      {
	automap_glyph(game->cell[y][x], &glyph, &attr);
      }

      if ((game->automap[y][x] & AUTOMAP_VISITED) == 0)
	attr = COLOR_PAIR(PAIR_BLACK) | A_BOLD;

//      if (game->branch[y][x])
//	attr = COLOR_PAIR(PAIR_BLACK) | A_BOLD;

      addch(glyph | attr);
    }
  }

  map_legend();

  if (!map_demo)
  {
    mvaddch(player->y / FLOOR_H, player->x / 9,
	    ACS_CKBOARD | COLOR_PAIR(PAIR_MAGENTA) | A_BLINK);
  }

  if (map_demo)
  {
    mvaddstr(MAX_FLOORS - 1, CELLS_W + 2, working_label);
  }

  refresh();

  return;
}


void map_legend()
{
  int y;
  int x;

  chtype attr = 0;
  chtype glyph = ' ';

  x = CELLS_W + 2;
  y = 1;

  mvaddch(y, x, ACS_CKBOARD | COLOR_PAIR(PAIR_MAGENTA));
  addstr(" YOUR HERE");
  y++;

#define LEGEND(a,b) \
  automap_glyph(a, &glyph, &attr); \
  mvaddch(y, x, glyph | attr); \
  addstr(" " b); \
  y++;

  LEGEND(CELL_START,     "START");
  LEGEND(CELL_BOSS,      "BOSS");
  y++;
  LEGEND(CELL_MONSTER,   "MONSTER");
  LEGEND(CELL_LOOT,      "LOOT");
  LEGEND(CELL_NPC_L,     "SHOP");
  y++;

  LEGEND(CELL_LADDER_T,  "");
  LEGEND(CELL_LADDER,    "LADDER");
  LEGEND(CELL_LADDER_B,  "");
  y++;
  LEGEND(CELL_TRAP,      "TRAP");
  LEGEND(CELL_TRAPDOOR,  "TRAPDOOR");
  LEGEND(CELL_SPIKEPIT,  "SPIKED PIT");
  y++;
  LEGEND(CELL_CHASM_T,   "");
  LEGEND(CELL_CHASM,     "CHASM");
  LEGEND(CELL_CHASM,     "");
  
  return;
}


void automap_glyph(int celltype, chtype * glyph, chtype * attr)
{
  switch (celltype)
  {
  case CELL_ROCK:
  case CELL_OPENDOWN:
    *glyph = ' ';
    break;
    
  case CELL_RESERVED:
    *glyph = 'R';
    *attr = COLOR_PAIR(PAIR_RED);
    break;
	
/*
  case CELL_KEEPROOM:
    *glyph = 'K';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_GORZOTH_L:
    *glyph = '<';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_GORZOTH_R:
    *glyph = '>';
    *attr = COLOR_PAIR(PAIR_RED);
    break;
*/

  case CELL_KEEPROOM:
  case CELL_GORZOTH_L:
  case CELL_GORZOTH_R:
  case CELL_ROOM:
    *glyph = ACS_HLINE;
    *attr = COLOR_PAIR(PAIR_GREEN);
    break;
	
  case CELL_RMNDR:
    *glyph = ACS_HLINE;
    *attr = COLOR_PAIR(PAIR_MAGENTA);
    break;

  case CELL_DEADEND:
    *glyph = ACS_HLINE;
    *attr = COLOR_PAIR(PAIR_CYAN);
    break;

  case CELL_LADDER:
  case CELL_OPENLADDER:
    *glyph = ACS_VLINE;
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;

  case CELL_OPENLADDER_B:
  case CELL_LADDER_B:
    *glyph = ACS_BTEE;
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;
	
  case CELL_LADDER_T:
    *glyph = ACS_TTEE;
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;

  case CELL_MONSTER:
  case CELL_BRIDGE_CM:
  case CELL_BRIDGE_WM:
    *glyph = 'M';
    *attr = COLOR_PAIR(PAIR_WHITE);
    break;

  case CELL_LOOT:
    *glyph = '*';
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;
    
  case CELL_BRIDGE_C:
  case CELL_BRIDGE_W:
    *glyph = '=';
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;
    
  case CELL_CAMP:
    *glyph = '%';
    *attr = COLOR_PAIR(PAIR_MAGENTA);
    break;
    
  case CELL_PORTAL:
    *glyph = 'O';
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;

  case CELL_BRANCH:
    *glyph = ACS_HLINE;
    *attr = COLOR_PAIR(PAIR_BLUE) | A_BOLD;
    break;

  case CELL_TRAPDOOR:
    *glyph = '_';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_CHASM:
    *glyph = 'V';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_CHASM_T:
    *glyph = 'C';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_TRICKY:
    *glyph = '!';
    *attr = COLOR_PAIR(PAIR_RED);
    break;
    
  case CELL_TRAP:
    *glyph = 'T';
    *attr = COLOR_PAIR(PAIR_RED);
    break;

  case CELL_SPIKEPIT:
    *glyph = 'X';
    *attr = COLOR_PAIR(PAIR_RED);
    break;
	
  case CELL_NPC_L:
  case CELL_NPC_R: 
  case CELL_SUSHI_L:
  case CELL_SUSHI_R: 
    *glyph = 'N';
    *attr = COLOR_PAIR(PAIR_CYAN);
    break;

  case CELL_BOSS:
    *glyph = 'B';
    *attr = COLOR_PAIR(PAIR_WHITE);
    break;

  case CELL_START:
    *glyph = 'S';
    *attr = COLOR_PAIR(PAIR_WHITE);
    break;

  case CELL_DOOR:
    *glyph = '|';
    *attr = COLOR_PAIR(PAIR_BROWN);
    break;

  case CELL_BRICKWALL:
    *glyph = ' ';
    *attr = COLOR_PAIR(PAIR_WHITE);
    break;

  case CELL_SWSTONE:
    *glyph = '8';
    *attr = COLOR_PAIR(PAIR_WHITE);
    break;

  case CELL_WSURFACE:
    *glyph = ACS_TTEE;
    *attr = COLOR_PAIR(PAIR_CYAN);
    break;

  case CELL_WATER:
  case CELL_WCORR:
  case CELL_WOPENDOWN:
    *glyph = ACS_CKBOARD;
    *attr = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
    break;

  case CELL_WTRAP:
  case CELL_WCORRTRAP:
    *glyph = 'T';
    *attr = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
    break;

  case CELL_WMONSTER:
  case CELL_WCORRMON:
    *glyph = 'M';
    *attr = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
    break;

  case CELL_WLOOT:
  case CELL_WCORRLOOT:
    *glyph = '*';
    *attr = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
    break;

  case CELL_WFALL:
    *glyph = 'W';
    *attr = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
    break;
    
  default:
    *glyph = '?';
    break;
  }

  return;
}



/**
   Flips the automap to display the lower half of the dungeon, but
   only if the game is in demo or cheat mode.
*/
void flip_automap()
{
  if (!map_demo && !cheat_mode)
    return;
  
  if (automap_view_y == 0)
    automap_view_y = 24;
  else
    automap_view_y = 0;

  return;
}
