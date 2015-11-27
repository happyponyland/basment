#include "basment.h"
#include "map.h"



void fix_walls()
{
  int y;
  int x;
  int lt;
  int rt;
  int tt;
  int bt;
  int mask;
  int tile;
  int water;

  for (y = 0; y < MAP_H; y++)
  {
    for (x = 0; x < MAP_W; x++)
    {
      tile = gtile(y, x);

      if (tile < TL_JOIN_WALL || tile > TL_NO_MODIFY)
	continue;

      lt = gtile(y, x - 1);
      rt = gtile(y, x + 1);
      tt = gtile(y - 1, x);
      bt = gtile(y + 1, x);

      water =
 	lt == TL_WATER || lt == TL_SURFACE ||
 	rt == TL_WATER || rt == TL_SURFACE ||
 	tt == TL_WATER || tt == TL_SURFACE ||
 	bt == TL_WATER || bt == TL_SURFACE ||
	gtile(y - 1, x - 1) == TL_WATER ||
	gtile(y + 1, x - 1) == TL_WATER ||
	gtile(y + 1, x + 1) == TL_WATER ||
	gtile(y - 1, x + 1) == TL_WATER;
      
      mask =
	(lt < TL_JOIN_WALL ? 1 : 0) + 
	(rt < TL_JOIN_WALL ? 2 : 0) +
	(tt < TL_JOIN_WALL ? 4 : 0) +
	(bt < TL_JOIN_WALL ? 8 : 0);

      if (water)
      {
	switch (mask)
	{
	case 0:
	  if (gtile(y - 1, x + 1) < TL_JOIN_WALL)
	    stile(y, x, TL_W_CORNER_LL);
	  else if (gtile(y + 1, x + 1) < TL_JOIN_WALL)
	    stile(y, x, TL_W_CORNER_UL);
	  else if (gtile(y - 1, x - 1) < TL_JOIN_WALL)
	    stile(y, x, TL_W_CORNER_LR);
	  else if (gtile(y + 1, x - 1) < TL_JOIN_WALL)
	    stile(y, x, TL_W_CORNER_UR);
	  else
	    stile(y, x, TL_BWALL);
	  
	  break;
	  
	case 1:
	  if (rand() % 2)
	  {
	    stile(y, x, TL_W_LEFT);

	    if (rand() % 3 == 0)
	      stile(y, x + 1, TL_W_HFLAT);
	  }
	  else
	    stile(y, x, TL_W_VFLAT);
	  break;
	  
	case 2:
	  if (rand() % 2)
	  {
	    stile(y, x, TL_W_RIGHT);

	    if (rand() % 3 == 0)
	      stile(y, x - 1, TL_W_HFLAT);
	  }
	  else
	    stile(y, x, TL_W_VFLAT);
	  break;
	  
	case 3:
	case 4:
	  if (rand() % 2)
	  {
	    stile(y, x, TL_W_BOTTOM);

    	    if (rand() % 3 == 0)
	      stile(y + 1, x, TL_W_VFLAT);
	  }
	  else
	    stile(y, x, TL_W_HFLAT);
	  break;

	case 8:
	  if (rand() % 2)
	  {
	    stile(y, x, TL_W_TOP);

    	    if (rand() % 3 == 0)
	      stile(y - 1, x, TL_W_VFLAT);
	  }
	  else
	    stile(y, x, TL_W_HFLAT);
	  break;
	  
	case 5:  stile(y, x, TL_W_CORNER_UL); break;
	case 6:  stile(y, x, TL_W_CORNER_UR); break;
	case 9:  stile(y, x, TL_W_CORNER_LL); break;
	case 10: stile(y, x, TL_W_CORNER_LR); break;
	  
	default: stile(y, x, TL_BWALL); break;
	}
      } /* water */
      else
      {
	switch (mask)
	{
	case 0:
	  if (gtile(y - 1, x + 1) < TL_JOIN_WALL)
	    stile(y, x, TL_CORNER_LL);
	  else if (gtile(y + 1, x + 1) < TL_JOIN_WALL)
	    stile(y, x, TL_CORNER_UL);
	  else if (gtile(y - 1, x - 1) < TL_JOIN_WALL)
	    stile(y, x, TL_CORNER_LR);
	  else if (gtile(y + 1, x - 1) < TL_JOIN_WALL)
	    stile(y, x, TL_CORNER_UR);
	  else
	    stile(y, x, TL_BWALL);
	  
	  break;
	  
	case 1: stile(y, x, TL_WALL); break;
	case 2: stile(y, x, TL_WALL); break;
	  
	case 3:
	case 4:
	case 8:
	  stile(y, x, TL_FLOOR);
	  break;
	  
	case 5: stile(y, x, TL_CORNER_UL); break;
	case 6: stile(y, x, TL_CORNER_UR); break;
	case 9: stile(y, x, TL_CORNER_LL); break;
	case 10: stile(y, x, TL_CORNER_LR); break;
	  
	default: stile(y, x, TL_BWALL); break;
	}
      } /* not water */
    }
  }

  return;
}



void decorate_walls(void)
{
  int y;
  int x;
  int branch;
  int branch_l;
  int branch_r;
  int t;
  int n;
  int cy;
  int cx;

  for (y = 0; y < MAP_H; y++)
  {
    for (x = 0; x < MAP_W; x++)
    {
      cy = y / FLOOR_H;
      cx = x / CELL_TO_TILES;

//      branch_ll = get_branch(cy, cx - 2);
      branch_l = get_branch(cy, cx - 1);
      branch = get_branch(cy, cx);
      branch_r = get_branch(cy, cx + 1);
//      branch_rr = get_branch(cy, cx + 2);

      t = gtile(y, x);
      
      if (get_cell(cy, cx) == CELL_DOOR)
      {
	if (x % CELL_TO_TILES == 4)
	{
	  if (branch_l < branch_r)
	    branch = branch_l;
	  else
	    branch = branch_r;
	}
	else if (x % CELL_TO_TILES < 4)
	{
	  branch = branch_l;
	}
	else if (x % CELL_TO_TILES > 4)
	{
	  branch = branch_r;
	}
      }
      
      // Ceiling decorations
      if (cy == MAX_FLOORS - 1)
      {
	if (y % FLOOR_H == 3 && gtile(y, x) > TL_JOIN_WALL)
	  stile(y, x, TL_IWALL);
      }
      else if (branch == BRANCH_CAVE)
      {
	switch (t)
	{
	case TL_FLOOR:
	case TL_WALL:
	case TL_CORNER_UR:
	case TL_CORNER_UL:
	case TL_CORNER_LR:
	case TL_CORNER_LL:
	  stile(y, x, TL_DIRT);
	  
	default: break;
	}

	if (y % FLOOR_H == 4)
	{
	  // Make sure we don't overwrite the walls or
	  // draw stalactites under a chasm
	  if (gtile(y, x) != TL_VOID ||
	      gtile(y - 1, x) == TL_VOID)
	    continue;
	  
	  int t;
	  t = rand() % 220;
	  
	  if (gtile(y - 1, x) == TL_ROOTS1)
	    stile(y, x, TL_ROOTS2);
	  else if (t < 3)
	    stile(y, x, TL_ROOTS1);
	  else if (t < 6)
	    stile(y, x, TL_ROOTS3);
	  else if (t < 9)
	    stile(y, x, TL_ROOTS4);
	  else if (t < 25)
	    stile(y, x, TL_STALACTITE3);
	  else if (t < 48)
	    stile(y, x, TL_STALACTITE2);
	  else if (t < 70)
	    stile(y, x, TL_STALACTITE1);
	}
      }
      else if (branch == BRANCH_ORGANIC)
      {
	bool wall;

	if (get_cell(cy, cx) == CELL_ROCK)
	  continue;

	if (t == TL_FLOOR ||
	    t == TL_WALL ||
	    t == TL_CORNER_UR ||
	    t == TL_CORNER_UL ||
	    t == TL_CORNER_LR ||
	    t == TL_CORNER_LL)
	{
	  wall = true;
	}
	else if (t == TL_BWALL)
	  wall = false;
	else
	  continue;

	if (y % FLOOR_H == 10)
	{
	  n = TL_ORG11 + rand() % 5;
	}
	else if (y % FLOOR_H == 3)
	{
	  n = TL_ORG21 + rand() % 4;
	}
	else if ((wall || rand() % 4 > 0) &&
		 (y % FLOOR_H == 2 || y % FLOOR_H == 11))
	{
	  n = TL_ORG31 + rand() % 4;
	}
	else if ((wall || rand() % 4 == 0) &&
		 (y % FLOOR_H == 1 || y % FLOOR_H == 12))
	{
	  n = TL_ORG31 + rand() % 4;
	}
	else if (wall)
	{
	  n = TL_ORG11 + rand() % 3;
	}
	else
	{
	  continue;
	}

	stile(y, x, n);
      }
      else if (branch == BRANCH_CRYPT)
      {
	switch (t)
	{
	case TL_FLOOR:
	case TL_WALL:
	case TL_CORNER_UR:
	case TL_CORNER_UL:
	case TL_CORNER_LR:
	case TL_CORNER_LL:
	  stile(y, x, TL_CRYPTF);

	default: break;
	}
      }
    }
  }


  return;
}



int gtile(int y, int x)
{
  if (y < 0 || y >= MAP_H || x < 0 || x >= MAP_W)
    return TL_OOB;

  return game->tile[y][x];
}



int branch_at_tile(int y, int x)
{
  int cy;
  int cx;

  cy = y / FLOOR_H;
  cx = x / CELL_TO_TILES;

  return game->branch[cy][cx];
}



int stile(int y, int x, int n)
{
  int old;

  if (y < 0 || y >= MAP_H || x < 0 || x >= MAP_W)
    return TL_OOB;

  old = game->tile[y][x];

  game->tile[y][x] = n;

  return old;
}
