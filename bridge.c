/*
  bridge.c - bridge generation.
*/

#include "basment.h"



/**
   Checks if @cell is any kind of bridge cell.
*/
int is_bridge(int cell)
{
  switch (cell)
  {
  case CELL_BRIDGE_C:
  case CELL_BRIDGE_W:
  case CELL_BRIDGE_CM:
  case CELL_BRIDGE_WM:
    return true;

  default:
    return false;
  }
}



/**
   Adds bridges to the cellmap.
*/
void add_bridges()
{
  int y;
  int x;
  int dir;
  int cell;
  int cell_below;
  
  int bridge_len;
  int next_dist;

  bridge_len = 0;
  next_dist = 20 + rand() % 50;

  if (rand() % 2)
  {
    dir = +1;
    x = 0;
  }
  else
  {
    dir = -1;
    x = CELLS_W - 1;
  }
  
  for (y = 0; y < LAST_NORMAL_FLOOR; y++)
  {
    while (x >= 0 && x < CELLS_W)
    {
      cell       = get_cell(y,     x);
      cell_below = get_cell(y + 1, x);

      if (cell != CELL_ROOM && cell != CELL_RMNDR)
	goto move_on;

      if (cell_below == CELL_ROCK ||
	  cell_below == CELL_RESERVED ||
	  cell_below == CELL_DOOR)
      {
	/*
	  Don't add bridges on top of solid walls and doors. Jump to
	  set up a new distance to avoid making bridges over chasm and
	  water with 1 cell left unchanged between them.
	*/
	goto new_dist;
      }
      
      if (bridge_len)
      {
	set_cell(y, x, CELL_BRIDGE_C);
	
	if (--bridge_len == 0)
	{
	new_dist:
	  bridge_len = 0; // In case we jumped here
	  	  
	  if (rand() % 3 == 0)
	    next_dist = 1 + rand() % 10;
	  else
	    next_dist = 20 + rand() % 25;
	}
      }
      else if (--next_dist == 0)
      {
	bridge_len = 1 + rand() % 5;
      }

    move_on:
      x += dir;
    }

    dir *= -1;
    x += dir;
  }

  return;
}



/**
   Converts cell @cy, @cx to a bridge on the tilemap.
*/
void make_bridge(int cy, int cx)
{
  int cell_l;
  int cell;
  int cell_r;
  int tx;
  int feet;
  int w_l;
  int w_r;
  int y;
  int x;

  feet = (cy * BOARD_H) + FEET_Y;
  tx = (cx * CELL_TO_TILES) + 4;

  cell_l = get_cell(cy, cx - 1);
  cell   = get_cell(cy, cx);
  cell_r = get_cell(cy, cx + 1);

  w_l = is_bridge(cell_l) ? 4 : 2;
  w_r = is_bridge(cell_r) ? 4 : 2;

  for (x = tx - w_l; x <= tx + w_r; x++)
  {
    stile(feet + 1, x, TL_BRIDGE);

    if (cell == CELL_BRIDGE_W)
    {
      /*
	Bridges over water have two empty tiles below, a decorative
	water surface and an underwater "stop" tile.
      */
      stile(feet + 2, x, TL_VOID);
      stile(feet + 3, x, TL_VOID);
      stile(feet + 4, x, TL_BRIDGESURFACE);
      stile(feet + 5, x, TL_UW_BELOW_BRIDGE);

      // Fill up the rest with water
      for (y = feet + 6; y < feet + 9; y++)
	stile(y, x, TL_WATER);
    }
    else
    {
      // Regular bridge; open up a chasm underneath
      for (y = feet + 2; y < feet + 9; y++)
	stile(y, x, TL_VOID);
    }
  }

  // Add a decorative support beam at the end of the bridge
  if (w_l == 2)
    stile(feet + 2, tx - w_l, TL_BRIDGE_SUPPORT_L);
  
  if (w_r == 2)
    stile(feet + 2, tx + w_r, TL_BRIDGE_SUPPORT_R);

  return;
}
