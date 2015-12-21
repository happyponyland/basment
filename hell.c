/*
  hell.c - some special functions for generating the Hell floors
*/

#include "basment.h"



void add_archdemon_floor()
{
  int y;
  int x;
  int sl;
  int sr;

  y = ARCHDEMON_FLOOR;

  sl = 2 + rand() % 5;
  sr = CELLS_W - 3 - rand() % 5;
  
  for (x = sl; x <= sr; x++)
  {
    set_cell(y, x, CELL_ROOM);
  }

  set_cell(y, CELLS_W / 2, CELL_BOSS);
  
  for (x = sl; x <= sr; x++)
  {
    if (get_cell(y - 2, x) == CELL_ROCK ||
	get_cell(y - 2, x) == CELL_ROOM)
    {
      sl = x;
      break;
    }
  }

  for (x = sr; x >= sl; x--)
  {
    if (get_cell(y - 2, x) == CELL_ROCK ||
	get_cell(y - 2, x) == CELL_ROOM)
    {
      sr = x;
      break;
    }
  }
  
  for (x = sl; x <= sr; x++)
    set_cell(y - 1, x, CELL_OPENDOWN);

  set_cell(y,     sl, CELL_OPENLADDER_B);
  set_cell(y,     sr, CELL_OPENLADDER_B);
  set_cell(y - 1, sl, CELL_OPENLADDER);
  set_cell(y - 1, sr, CELL_OPENLADDER);
  set_cell(y - 2, sl, CELL_LADDER_T);
  set_cell(y - 2, sr, CELL_LADDER_T);

/*  set_cell(y - 1, sl - 1, CELL_OPENDOWN);
  set_cell(y - 1, sr + 1, CELL_OPENDOWN);
  set_cell(y,     sl - 1, CELL_ROOM);
  set_cell(y,     sr + 1, CELL_ROOM);*/

  for (x = sl; x <= sr; x++)
  {
    if (get_cell(y - 2, x) == CELL_ROCK)
    {
      set_cell(y - 2, x, CELL_ROOM);
    }
  }

  for (x = 0; x < CELLS_W; x++)
  {
    if (get_cell(y - 2, x) == CELL_BOSS)
      set_cell(y - 2, x, CELL_ROOM);
  }

  return;
}


int hell_floor(int floor)
{
  return (floor >= FIRST_HELL_FLOOR && floor <= ARCHDEMON_FLOOR);
}



void decorate_hell()
{
  int cy;
  int cx;
  int this_cell;
  int cell_above;
  int feet;
  int tx;

  for (cy = FIRST_HELL_FLOOR; cy <= ARCHDEMON_FLOOR; cy++)
  {
    /*
      Don't do this on edge cells. They should not be rooms but
      sometimes are anyway; convert_cellmap() won't touch them so
      there's nothing there and adding decorations will look weird.
    */
    for (cx = 1; cx < CELLS_W - 1; cx++)
    {
      this_cell = get_cell(cy, cx);
      cell_above = get_cell(cy - 1, cx);

      CELL_CENTER(cy, cx, feet, tx);
      
      if (this_cell == CELL_ROCK)
      {
	continue;
      }

      if (this_cell == CELL_SPIKEPIT)
      {
	hell_crack(feet, tx,     true);
      }
      else if (this_cell  != CELL_LADDER &&
	       this_cell  != CELL_LADDER_B &&
	       this_cell  != CELL_OPENLADDER &&
	       this_cell  != CELL_OPENLADDER_B &&
	       this_cell  != CELL_CHASM &&
	       cell_above != CELL_BRIDGE_C &&
	       cell_above != CELL_BRIDGE_CM &&
	       cell_above != CELL_CHASM &&
	       cell_above != CELL_OPENDOWN &&
	       cell_above != CELL_TRAPDOOR)
      {
	hell_crack(feet, tx,     true);
	hell_crack(feet, tx - 3, true);
	hell_crack(feet, tx + 3, true);
      }

      if (this_cell != CELL_LADDER_T &&
	  this_cell != CELL_LADDER &&
	  this_cell != CELL_OPENLADDER &&
	  this_cell != CELL_OPENDOWN &&
	  this_cell != CELL_TRAPDOOR &&
	  this_cell != CELL_SPIKEPIT &&
	  this_cell != CELL_WSURFACE &&
	  this_cell != CELL_CHASM &&
	  this_cell != CELL_BRIDGE_C &&
	  this_cell != CELL_BRIDGE_CM &&
	  this_cell != CELL_CHASM_T)
      {
	hell_crack(feet, tx,     false);
	hell_crack(feet, tx - 3, false);
	hell_crack(feet, tx + 3, false);
      }
    }
  }

  return;
}



void hell_crack(int y, int x, int up)
{
  int y1;
  int y2;
  int y3;
  int r;
  int type;
  int f;

  if (up)
  {
    y1 = y - 7;
    y2 = y - 8;
    y3 = y - 9;
    f = 0;
  }
  else
  {
    y1 = y + 2;
    y2 = y + 3;
    y3 = y + 4;
    f = 1;
  }

  type = rand() % 14;
  
  switch (type)
  {
  case 0:
    stile(y1, x - 0, TL_HELL_CRACK_V);
    break;
    
  case 1:
    stile(y1, x - 1, TL_HELL_CRACK_LTEE);
    stile(y2, x - 1, TL_HELL_CRACK_V);
    stile(y1, x - 0, TL_HELL_CRACK_LR + f);
    break;
    
  case 2:
    stile(y1, x - 0, TL_HELL_CRACK_LTEE);
    stile(y1, x + 1, TL_HELL_CRACK_LR + f);
    stile(y2, x - 0, TL_HELL_CRACK_RTEE);
    stile(y2, x - 1, TL_HELL_CRACK_LL + f);
    stile(y3, x - 0, TL_HELL_CRACK_V);
    break;

  case 3:
    stile(y1, x - 1, TL_HELL_CRACK_V);
    stile(y2, x - 1, TL_HELL_CRACK_V);
    stile(y1, x + 1, TL_HELL_CRACK_V);
    break;

  case 4:
    stile(y1, x - 0, TL_HELL_CRACK_V);

    if (rand() % 2)
      stile(y2, x - 0, TL_HELL_CRACK_V);
    
    stile(y1, x + 1, TL_HELL_CRACK_V);
    stile(y2, x + 1, TL_HELL_CRACK_V);

    if (rand() % 2)
      stile(y3, x + 1, TL_HELL_CRACK_V);
    break;
    
  case 5:
    r = rand() % 2;
    
    if (rand() % 2)
    {
      stile(y1, x - 1 + r, TL_HELL_CRACK_V);
      stile(y2, x - 1 + r, TL_HELL_CRACK_UL - f);
      stile(y2, x - 0 + r, TL_HELL_CRACK_LR + f);
      stile(y3, x - 0 + r, TL_HELL_CRACK_V);
    }
    else
    {
      stile(y1, x + r - 1, TL_HELL_CRACK_UL - f);
      stile(y1, x + r - 0, TL_HELL_CRACK_LR + f);
      stile(y2, x + r - 0, TL_HELL_CRACK_V);
    }
    break;
    
  case 6:
    stile(y1, x - 0, TL_HELL_CRACK_UR - f);
    stile(y1, x - 1, TL_HELL_CRACK_LL + f);
    stile(y2, x - 1, TL_HELL_CRACK_V);
    stile(y1, x + 1, TL_HELL_CRACK_V);
    stile(y2, x + 1, TL_HELL_CRACK_UR - f);
    stile(y2, x - 0, TL_HELL_CRACK_LL + f);
    stile(y3, x - 0, TL_HELL_CRACK_V);
    break;
    
  case 7:
    stile(y1, x - 1 + rand() % 2, TL_HELL_CRACK_V);
    break;
    
  case 8:
    stile(y1, x - 1, TL_HELL_CRACK_V);
    stile(y2, x - 1, TL_HELL_CRACK_UL - f);
    stile(y2, x - 0, TL_HELL_CRACK_LR + f);
    stile(y3, x - 0, TL_HELL_CRACK_V);
    break;
    
  case 9:
    stile(y1, x + 0, TL_HELL_CRACK_RTEE);
    stile(y2, x + 0, TL_HELL_CRACK_V);
    stile(y1, x - 1, TL_HELL_CRACK_LL + f);
    break;
    
  case 10:
    stile(y1, x - 1, TL_HELL_CRACK_V);
    stile(y2, x - 1, TL_HELL_CRACK_V);

    if (rand() % 2)
      stile(y3, x - 1, TL_HELL_CRACK_V);
    
    stile(y1, x + 1, TL_HELL_CRACK_V);
    break;

  case 11:
    stile(y1, x - 0, TL_HELL_CRACK_UR - f);
    stile(y1, x - 1, TL_HELL_CRACK_LL + f);
    stile(y2, x - 1, TL_HELL_CRACK_V);
    stile(y3, x - 1, TL_HELL_CRACK_UL - f);
    stile(y3, x - 0, TL_HELL_CRACK_H);
    stile(y3, x + 1, TL_HELL_CRACK_UR - f);
    stile(y2, x + 1, TL_HELL_CRACK_LR + f);
    stile(y2, x - 0, TL_HELL_CRACK_LL + f);
    break;
    
  case 12:
    stile(y1, x - 1, TL_HELL_CRACK_UL - f);
    stile(y1, x - 0, TL_HELL_CRACK_H);
    stile(y1, x + 1, TL_HELL_CRACK_LR + f);
    stile(y2, x + 1, TL_HELL_CRACK_V);
    stile(y3, x + 1, TL_HELL_CRACK_UR - f);
    stile(y3, x - 0, TL_HELL_CRACK_H);
    stile(y3, x - 1, TL_HELL_CRACK_UL - f);
    stile(y2, x - 1, TL_HELL_CRACK_LL + f);
    stile(y2, x - 0, TL_HELL_CRACK_LR + f);
    break;

  case 13:
    stile(y1, x - 1, TL_HELL_CRACK_LL + f);
    stile(y1, x - 0, TL_HELL_CRACK_RTEE);
    
//    stile(y2, x - 1, TL_HELL_CRACK_LL + f);
    stile(y2, x - 0, TL_HELL_CRACK_LTEE);
    stile(y2, x + 1, TL_HELL_CRACK_LR + f);

    stile(y3, x - 1, TL_HELL_CRACK_LL + f);
    stile(y3, x - 0, TL_HELL_CRACK_H);
    stile(y3, x + 1, TL_HELL_CRACK_UR - f);
    break;

  default:
    break;
  }
  
/*    stile(y1, x - 0, TL_HELL_CRACK_EYE);
    stile(y2, x - 1, TL_HELL_CRACK_PL);
    stile(y2, x + 1, TL_HELL_CRACK_PR);
    stile(y3, x - 0, TL_HELL_CRACK_EYE);*/
  
  return;
}
