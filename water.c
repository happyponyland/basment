#include "basment.h"



int water_cell(int c)
{
  return wcorr_cell(c) || wopen_cell(c);
}


int wcorr_cell(int c)
{
  switch (c)
  {
  case CELL_WCORR:
  case CELL_WCORRLOOT:
  case CELL_WCORRMON:
  case CELL_WOPENDOWN:
  case CELL_WCORRTRAP:
    return true;

  default:
    return false;
  }
}



int wopen_cell(int c)
{
  switch (c)
  {
  case CELL_WATER:
  case CELL_WMONSTER:
  case CELL_WLOOT:
  case CELL_WTRAP:
    return true;

  default:
    return false;
  }
}



int water_join(int t)
{
  if (t >= TL_UNDERWATER && t < TL_LASTUNDERWATER)
    return true;

  return false;
}



/**
   Convert the cell at @cy, @cx to the tilemap.
*/
void make_water(int cy, int cx)
{
  int tx;
  int feet;
  int x;
  int y;
  int w_l;
  int w_r;
  int here;
  int cell_u;
  int cell_l;
  int cell_r;
  int cell_ul;
  int cell_ur;

  here = get_cell(cy, cx);
  cell_u = get_cell(cy - 1, cx);
  cell_l = get_cell(cy, cx - 1);
  cell_r = get_cell(cy, cx + 1);
  cell_ul = get_cell(cy - 1, cx - 1);
  cell_ur = get_cell(cy - 1, cx + 1);
  
  feet = (cy * BOARD_H) + FEET_Y;
  tx = (cx * CELL_TO_TILES) + 4;

  if (here == CELL_WSURFACE)
  {
    w_l = 2;
    w_r = 2;
    
    if (water_cell(get_cell(cy + 1, cx)))
    {
      w_l = (get_cell(cy + 1, cx - 1) == CELL_WATER ? 4 : 2);
      w_r = (get_cell(cy + 1, cx + 1) == CELL_WATER ? 4 : 2);
    }

    if (cell_l == CELL_WSURFACE)
      w_l = 4;
    else
    {
      if (gtile(feet, tx - 4) == TL_FLOOR)
	stile(feet, tx - 4, TL_STOP);
      
      stile(feet, tx, TL_STOP);
    }
    
    if (cell_r == CELL_WSURFACE)
      w_r = 4;
    else
    {
      if (gtile(feet, tx - 4) == TL_FLOOR)
	stile(feet, tx + 4, TL_STOP);
      
      stile(feet, tx, TL_STOP);
    }

    for (x = tx - w_l; x <= tx + w_r; x++)
    {
      stile(feet + 1, x, TL_SURFACE);
      stile(feet + 2, x, TL_WATER);
    }
  }
  else if (water_cell(here)/* || here == CELL_WCORR*/)
  {
    w_l = ((water_cell(cell_l) /*|| wcorr_cell(cell_l)*/) ? 4 : 2);
    w_r = ((water_cell(cell_r) /*|| wcorr_cell(cell_r)*/) ? 4 : 2);

    for (x = tx - w_l; x <= tx + w_r; x++)
    {
      for (y = feet - 5; y <= feet; y++)
      {
	stile(y, x, TL_WATER);
      }
    }

    if ((water_cell(cell_u) || cell_u == CELL_WSURFACE) &&
	(here == CELL_WATER    ||
	 here == CELL_WMONSTER ||
	 here == CELL_WLOOT))
    {
      w_l = w_r = 2;

      if (water_cell(cell_r) &&
	  (water_cell(cell_ur) || cell_ur == CELL_WSURFACE))
	w_r = 4;

      if (water_cell(cell_l) &&
	  (water_cell(cell_ul) || cell_ul == CELL_WSURFACE))
	w_l = 4;
    
      for (x = tx - w_l; x <= tx + w_r; x++)
      {
	for (y = feet - FLOOR_H + 1; y <= feet - 6; y++)
	{
	  if (gtile(y, x) != TL_SURFACE)
	    stile(y, x, TL_WATER);
	}
      }
    }
  }

  return;
}



int air_pocket(int y, int start_x)
{
  int dir = 0;

  if (get_cell(y, start_x)     != CELL_ROCK ||
      get_cell(y, start_x - 1) != CELL_ROCK ||
      get_cell(y, start_x + 1) != CELL_ROCK)
  {
    return false;
  }

  set_cell(y, start_x, CELL_WSURFACE);

  if (rand() % 2)
  {
    dir = (rand() % 2 ? -1 : +1);
    corridor(y, start_x, dir,  2);
    corridor(y, start_x, -dir, 2);
  }
  else
  {
    set_cell(y, start_x - 1, CELL_RESERVED);
    set_cell(y, start_x + 1, CELL_RESERVED);

    int x;
    int step;
    int w;
    
    dir  = (rand() % 2 ? -1 : +1);
    step = (dir == -1  ? +2 : -2);

    while (dir == -1 || dir == +1)
    {
      x = start_x;
      w = 0;
      
      while (x > 0 && x < CELLS_W - 2)
      {
	x += dir;
	w++;
	
	if (get_cell(y, x + dir) != CELL_ROCK)
	  break;

	set_cell(y, x + dir, CELL_RESERVED);
	set_cell(y, x, CELL_ROOM);

	if (w > 4)
	{
	  if (dir > 0)
	    set_cell(y, x, CELL_SUSHI_R);
	  else
	    set_cell(y, x, CELL_SUSHI_L);
	  
	  return true;
	}
      }

      dir += step;
    }
  }
  
  return true;
}



void put_lakes()
{
  int y;
  int x;
  int dir;
   
  for (y = LAST_NORMAL_FLOOR - 1; y > 3; y--)
  {
    x = 5 + rand() % (CELLS_W - 10);
    dir = (rand() % 2 ? +1 : -1);

    while (x > 3 && x < CELLS_W - 3)
    {
      if (get_cell(y - 1, x - 1) == CELL_ROCK &&
	  get_cell(y - 1, x - 0) == CELL_ROCK &&
	  get_cell(y - 1, x + 1) == CELL_ROCK)
      {
	dig_lake_up(y - 1, x, -1, 5);
	dig_lake_up(y - 1, x, +1, 5);
	goto next_floor;
      }
      
      x += dir;
    }

  next_floor:
    ;
  }

  return;
}



void add_surfaces()
{
  int y;
  int x;
  
  int here;
  int there;

  NOW_WORKING;
  
  for (y = MAX_FLOORS - 2; y > 2; y--)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      here = get_cell(y, x);
      there = get_cell(y - 1, x);

      if (here == CELL_WATER && there == CELL_WCORR)
      {
	set_cell(y - 1, x, CELL_WOPENDOWN);
      }
      else if (here == CELL_WCORR && there == CELL_WCORR)
      {
	if (rand() % 8)
	{
	  set_cell(y, x, CELL_WATER);

	  // Prevent placing anything on this spot
	  set_cell(y - 1, x, CELL_WOPENDOWN);
	}
      }
      else if (there == CELL_ROOM || there == CELL_RMNDR || there == CELL_DEADEND)
      {
	if (rand() % 4 &&
	    (here == CELL_WCORR ||
	     here == CELL_WCORRMON ||
	     here == CELL_WCORRLOOT))
	{
	  set_cell(y, x, CELL_WATER);
	}

	here = get_cell(y, x);
	
	if (here == CELL_WATER)
	  set_cell(y - 1, x, CELL_WSURFACE);
      }
    }
  }

  return;
}



void add_shallow_lakes()
{
  int y;
  int x;
  int dir;
  int paint;

  NOW_WORKING;

  for (y = 1; y < MAX_FLOORS - 1; y++)
  {
    if (rand() % 3 > 0)
      continue;
    
    dir = rnd_dir();
    x = (dir == +1 ? 2 : CELLS_W - 3);
    paint = 0;
    
    while (true)
    {
      x += dir * (rand() % 50);

    short_step:
      
      if (x < 2 || x >= CELLS_W - 2)
	break;

      if (get_cell(y, x) != CELL_ROOM)
      {
	paint = 0;
	continue;
      }
      else if (!paint)
      {
	paint = 3 + rand() % 5;
      }
      
      if (paint)
      {
	paint--;
	set_cell(y, x, CELL_WSURFACE);
	x += dir;

	if (paint > 0)
	  goto short_step;
      }
    }
  }

  return;
}




int dig_lake_up(int start_y, int start_x, int dir, int rec_depth)
{
  int y;
  int x;
  int c;
  int dist;

  NOW_WORKING;

  --rec_depth;
  
  if (rec_depth < 0)
    return false;
     
  if (start_y < 3)
    return false;
  
  y = start_y;
  x = start_x;

  c = get_cell(y, x);

  if (c != CELL_ROCK && c != CELL_WCORR && c != CELL_WATER)
    return false;

  dist = 2 + rand() % 5;

  while (x > 0 && x < (CELLS_W - 1))
  {
    x += dir;

    c = get_cell(y, x);

    if (c != CELL_ROCK)
      break;
    
    set_cell(y, x, CELL_RESERVED);

    if (get_cell(y, - dir) != CELL_WATER)
      set_cell(y, x - dir, CELL_WCORR);

    c = get_cell(y, x + dir);

    if (--dist == 0 ||
	(c != CELL_ROCK)/* && c != CELL_WCORR && c != CELL_WATER)*/)
    {
      int t = false;

      if (rec_depth > 3 || rand() % 2)
      {
	t =  dig_lake_up(y - 1, x - dir, -1, rec_depth);
	t |= dig_lake_up(y - 1, x - dir, +1, rec_depth);
      }
      else if (rand() % 3 == 0)
      {
	t = air_pocket(y - 1, x - dir);
      }

      if (t)
	set_cell(y, x - dir, CELL_WATER);
	
      break;
    }
    
    //set_cell(y, x - dir, CELL_WCORR);
  }

  return true;
}




/**
   Adds a monster suitable for the water cell at @cy, @cx.
*/
void water_monster(int feet, int tx, int cy, int cx)
{
  int left;
  int right;

  int type;

  left  = get_cell(cy, cx - 1);
  right = get_cell(cy, cx + 1);

  /*
    If the cell to the left and/or right isn't a water cell, nudge the
    monster slightly away from the wall. If both sides are walls, it
    will just be recentered.
  */
  if (!water_cell(left))
    tx += 4;

  if (!water_cell(right))
    tx -= 4;

  // Default monster
  type = MOB_FISH;
  
  if (!wopen_down(cy, cx))
    type = MOB_CRAB;

  make_monster(feet, tx, type);
  
  return;
}



int wopen_down(int cy, int cx)
{
  int below;

  below = get_cell(cy + 1, cx);
  
  return (below == CELL_WMONSTER  ||
	  below == CELL_WLOOT     ||
	  below == CELL_WATER);
}



int spend_breath(mob_t * m, int amount)
{
  int b;

  m->breath -= amount;
  
  if (m->breath >= 0)
    return 0;

  b = m->breath * -1;
  m->breath = 0;
  return b;
}



void take_breath(mob_t * m)
{
  if (game->has_scuba)
    m->breath = BREATH_SCUBA;
  else
    m->breath = BREATH_NORMAL;

  return;
}


int player_underwater()
{
  return water_join(gtile(player->y, player->x));
}


void try_to_breathe()
{
  if (player_underwater())
  {
    player->hp -= spend_breath(player, 1);

    if (player->hp <= 0)
      game_over("YOU DROWNED", false);

    // Update breath bar
    draw_bars();
  }

  return;
}
