#include "basment.h"



void generate_map()
{
  int start_x;

  if (map_demo)
  {
    nodelay(stdscr, true);
  }

  // map_demo = false;

  do
  {
    clear_cellmap();

    // Pick a random starting point on the first floor (the door)
    start_x = 10 + rand() % (CELLS_W - 20);

    // Recursively build dungeon
    corridor(0, start_x, 0, false);

    // map_demo = true;

    add_extra_rooms();

    /*
      nodelay(stdscr, false);
      getch();
      nodelay(stdscr, true);
    */

    link_portals();
    replace_remainders();
    add_ambushes();
    populate_cellmap();
	
    set_cell(0, start_x - 1, CELL_ROOM);
    set_cell(0, start_x + 1, CELL_ROOM);
    set_cell(0, start_x, CELL_START);

    if (map_demo)
    {
      delay(2000);
    }
  } while (map_demo);
  
  clear_tilemap();
  convert_cellmap();
  fix_walls();
  decorate_walls();

  return;
}


void replace_remainders(void)
{
  int y;
  int x;
  int c;

  // Disable map demo mode, this is just boring to watch
  bool old_map_demo;
  old_map_demo = map_demo;
  map_demo = false;

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      c = get_cell(y, x);

      // Do not replace dead ends here, since we don't want
      // them to become chasms or keeprooms
      if (c == CELL_RMNDR)
	set_cell(y, x, CELL_ROOM);
    }
  }

  // Restore map demo mode
  map_demo = old_map_demo;

  return;
}


void add_ambushes(void)
{
  int y;
  int x;
  int dir;

  for (y = 15 + rand() % 3; y < 22; y++)
  {
    if (rand() % 2)
    {
      dir = +1;
      x = rand() % (MAP_W / 2);
    }
    else
    {
      dir = -1;
      x = (MAP_W / 2) + rand() % (MAP_W / 2);
    }

    while (x > 3 && x < MAP_W - 4)
    {
      if (get_branch(y, x) != BRANCH_DUNGEON ||
	  get_branch(y + 1, x) != BRANCH_DUNGEON ||
	  get_branch(y, x + dir * 4) != BRANCH_DUNGEON ||
	  get_branch(y + 1, x + dir * 4) != BRANCH_DUNGEON)
      {
	goto proceed;
      }

      if (cell_range(y, x, y + 1, x + dir * 4, CELL_ROOM, false))
      {
	cell_range(y, x, y + 1, x + dir * 4, CELL_KEEPROOM, true);

	if (dir > 0)
	  set_cell(y, x, CELL_GORZOTH_R);
	else
	  set_cell(y, x, CELL_GORZOTH_L);

	return;
      }

    proceed:
      x += dir;
    } 
  }

  return;
}


/*
  B and R inclusive.
*/
bool cell_range(int t, int l, int b, int r, int type, bool write)
{
  int y;
  int x;

  int temp;

  if (t > b)
  {
    temp = b;
    b = t;
    t = temp;
  }

  if (l > r)
  {
    temp = r;
    r = l;
    l = temp;
  }

  for (y = t; y <= b; y++)
  {
    for (x = l; x <= r; x++)
    {
      if (write)
      {
	set_cell(y, x, type);
      }
      else
      {
	if (get_cell(y, x) != type)
	  return false;
      }
    }
  }

  return true;
}



void add_wide_chasms(void)
{
//  int i;

  int y;
  int x;

//  i = 20;

/*  while (i--)
  {
    y = rand() % (BOARD_H - 2);
    x = 1 + rand() % (BOARD_W - 2);*/

  for (y = 0; y < MAX_FLOORS - 2; y++)
  {
    for (x = 1; x < CELLS_W - 2; x++)
    {
      if (get_cell(y, x) == CELL_ROCK)
      {
	dig_wide_chasm(y, x);
      }
    }
  }

  return;
}



bool dig_wide_chasm(int start_y, int x)
{
  bool done = false;
  int y;

  y = start_y;

  while (1)
  {
    if (y >= MAX_FLOORS - 1)
      return false;

    if (get_cell(y, x) != CELL_ROCK)
      break;

    y++;
  }

//  y--;

  while (--y >= start_y)
  {
    set_cell(y, x, CELL_CHASM);
//    y--;
    done = true;
  }

  set_cell(start_y, x, CELL_CHASM_T);

  return done;
}


void link_portals(void)
{
  bool has_portal;
  int y;
  int x;
  int c;

  has_portal = false;

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      if (get_cell(y, x) == CELL_PORTAL)
      {
	has_portal = true;
	break;
      }
    }
  }

  if (!has_portal)
    return;

  while (1)
  {
    y = rand() % (MAX_FLOORS - 1);
    x = 1 + rand() % (CELLS_W - 2);

    c = get_cell(y, x);

    if (c == CELL_ROOM || c == CELL_RMNDR)
    {
      set_cell(y, x, CELL_PORTAL);
      return;
    }
  }

  return;
}




void add_extra_rooms(void)
{
  int y;
  int x;
  int w;
  int d;
  int start_x;
  int dir;

//  for (y = MAX_FLOORS - 2; y >= 1; y--)
  for (y = 1; y < MAX_FLOORS - 2; y++)
  {
    if (rand() % 2)
    {
      dir = -1;
      start_x = CELLS_W - 2;
    }
    else
    {
      dir = +1;
      start_x = 1;
    }

    w = 4 + rand() % 10;
    d = 0;
    
    for (x = start_x ; /* */ ; x += dir)
    {
      if (dir == -1 && x < 1)
	break;
      else if (dir == +1 && x >= CELLS_W - 1)
	break;

      w--;

      if (w == 0)
	break;

      if (w < 1 ||
	  get_cell(y, x) != CELL_ROCK ||
	  get_cell(y, x + dir) != CELL_ROCK)
      {
	goto new_room;
      }

      if ((d == 0) && dig_up(y, x, CELL_ROCK) == false)
      {
	goto new_room;
      }
      else
      {
	if (d == 0)
	{
	  set_cell(y, x, CELL_LADDER_B);
	  w = 4 + rand() % 8;
	  d = 1;
	}
	else
	{
	  set_cell(y, x, CELL_DEADEND);
	  d++;
	}
      }

      continue;

    new_room:
      x += dir;
      w = 4 + rand() % 10;
      d = 0;
      continue;
    }

  }

  return;
}



bool dig_up(int start_y, int x, int carve)
{
  int y;
  int c;

  for (y = start_y - 1; y > 0 && y > start_y - 2; y--)
  {
    c = get_cell(y, x);

    if (c == CELL_ROOM || c == CELL_RMNDR ||
	(c == CELL_DEADEND && (get_cell(y, x - 1) == carve ||
			       get_cell(y, x + 1) == carve)) )
    {
      set_cell(y, x, CELL_LADDER_T);
      
      y++;

      while (y < start_y)
      {
	set_cell(y, x, CELL_LADDER);
	y++;
      }

      return true;
    }
    else if (c != carve)
    {
      return false;
    }
  }

  return false;
}



/*
  Digs a ladder on the cellmap from (START_Y, X).
*/
void dig(int start_y, int x, int speed, int depth)
{
  int y;
  bool chasm = false;

  if (speed < 0 && rand() % 3 == 0)
    chasm = true;

  y = start_y;

  if (speed < 0)
  {
    if (!chasm)
      set_cell(y, x, CELL_LADDER_B);
  }
  else
  {
    set_cell(y, x, CELL_LADDER_T);
  }

  while (depth--)
  {
    if (y >= MAX_FLOORS - 1)
      break;

    y += speed;

    if (chasm)
      set_cell(y, x, CELL_CHASM);
    else
      set_cell(y, x, CELL_LADDER);
  }

  if (speed > 0)
  {
    // When digging down we're still in the main corridor; pick a
    // random direction (0) for the next levels corridor
    corridor(y, x, 0, false);
  }
  else
  {
    corridor(y, x, -1, true);
    corridor(y, x, +1, true);

    if (chasm)
    {
      if (rand() % 5 > 0)
	set_cell(y, x, CELL_TRAPDOOR);
      else
	set_cell(y, x, CELL_CHASM_T);
    }
    else
      set_cell(y, x, CELL_LADDER_T);
  }

  return;
}



void corridor(int y, int start_x, int speed, bool remainder)
{
  int x;
  int i;
  int length;
  int dug;

  int edge_clear;

  x = start_x;

  dug = 0;

  if (remainder)
    edge_clear = 0;
  else
    edge_clear = 0;

  if (speed == 0)
    length = 3 + rand() % 35;
  else
    length = 3 + rand() % 20;

  if (speed == 0)
  {
    // If we're close to the edge we want to go the other way,
    // otherwise we can pick any direction.

    if (x < 5 + edge_clear)
      speed = +1;
    else if (x >= CELLS_W - 6 - edge_clear)
      speed = -1;
    else
    {
      if (rand() % 2 == 0)
	speed = +1;
      else
	speed = -1;

      // No wait, it might be better to go the other way
      if (game->cell[y][x + speed] != CELL_ROCK &&
	  game->cell[y][x - speed] == CELL_ROCK)
      {
	speed *= -1;
      }
    }
  }
  
  if (!remainder)
    set_cell(y, x, CELL_LADDER_B);

  for (i = 0; i < length; i++)
  {
    if ((x <= 1 + edge_clear && speed < 0) || (x >= CELLS_W - 2 - edge_clear && speed > 0))
      break;

    x += speed;

    if (game->cell[y][x] != CELL_ROCK)
    {
      x -= speed;
      break;
    }

    set_cell(y, x, (remainder ? CELL_RMNDR : CELL_ROOM));
    dug++;
  }

  if (y >= MAX_FLOORS - 1)
  {
    if (!remainder)
    {
      set_cell(y, x, CELL_BOSS);

      for (i = 0; i < 3; i++)
	make_branch();

      put_lakes();
      
//      for (i = 0; i < 7; i++)
//	make_lake();
    }
  }
  else if (!remainder)
  {
    // We're still in the main corridor; dig down (random number of
    // floors, biased towards 1) and start a new corridor.

//    dig(y, x, +1, 1 + (rand() % (1 + rand() % 3)));
    dig(y, x, +1, 1);

    corridor(y, x, speed, true);
  }
  else if (remainder && dug > 3)
  {
    int up;

    up = 1 + (rand() % (1 + rand() % 4));

    for (i = 0; i < up; i++)
    {
      if (y - i - 1 < 1)
      {
	up = 0;
	break;
      }
      else if (game->cell[y - i - 1][x] != CELL_ROCK ||
	       (game->cell[y - i - 1][x - 1] != CELL_ROCK &&
		game->cell[y - i - 1][x + 1] != CELL_ROCK))
      {
	up = i;
	break;
      }
    }

    if (up > 0)
      dig(y, x, -1, up);
  }

  if (!remainder && y >= 0)
  {
    corridor(y, start_x, speed * -1, true);
  }

  return;
}



void make_lake()
{
  int start_y;
  int start_x;

  int dir;

  dir = (rand() % 2 ? +1 : -1);
  
  start_y = 2 + rand() % (MAX_FLOORS - 8);

  while (start_y < MAX_FLOORS - 10)
  {
    start_x = 5 + rand() % (CELLS_W - 10);

    while (start_x > 5 && start_x <= CELLS_W - 10)
    {
      if (get_cell(start_y, start_x) == CELL_ROOM)
      {
	dig_lake(start_y, start_x,     dir);
//	dig_lake(start_y, start_x - 1, -1);
	return;
      }
      
      start_x += dir;
    }

    start_y++;
  }
   
  return;
}



void dig_lake(int start_y, int start_x, int dir)
{
  int y;
  int x;
  int depth;

  y = start_y;
  x = start_x;

  depth = 1 + rand() % 5;
//  depth = 0;

  while (get_cell(start_y, x) == CELL_ROOM)
  {
    set_cell(start_y, x, CELL_WSURFACE);

/*    switch (rand() % 3)
    {
    case 0: break;
    case 1: depth++; break;
    case 2: depth = MIN(1, depth - 1); break;
    }*/
    
    for (y = start_y + 1; y <= start_y + depth; y++)
    {
      if (get_cell(y, x) != CELL_ROCK)
	break;

      if ((get_cell(y, x - 1) != CELL_ROCK &&
	   get_cell(y, x - 1) != CELL_WATER)
	  ||
	  (get_cell(y, x + 1) != CELL_ROCK &&
	   get_cell(y, x + 1) != CELL_WATER))
      {
	set_cell(y, x, CELL_RESERVED);
	break;
      }
      
      set_cell(y, x, CELL_WATER);
    }
     
    x += dir;
  }

  return;
}



bool make_branch()
{
  int start_y;
  int start_x;
  int dir;

  int y;
  int x;
//  int i;
  int l;

  int branch;

//  branch = BRANCH_ORGANIC;
  branch = 1 + rand() % (BRANCHES - 1);

  start_y = 1 + rand() % (MAX_FLOORS - 6);

  if (rand() % 2)
  {
    dir = -1;
    start_x = CELLS_W - 3;
  }
  else
  {
    dir = 1;
    start_x = 1;
  }

  while (get_cell(start_y, start_x) != CELL_ROCK ||
	 get_cell(start_y, start_x + dir) != CELL_ROCK ||
	 get_cell(start_y, start_x + dir * 2) != CELL_ROCK)
  {
    start_y++;

    if (start_y > 20)
      return false;
  }

  x = start_x;
  y = start_y;
  
  while (x >= 1
	 && x <= CELLS_W - 1)
  {
    if (get_cell(y, x + dir) != CELL_ROCK && get_cell(y, x + dir) != CELL_RESERVED)
    {
      // Door
      set_cell_branch(y, x, CELL_DOOR, branch);
//      set_cell(y, x, CELL_DOOR);
      break;
    }
    else
    {
      set_cell_branch(y, x, CELL_ROOM, branch);
      x += dir;
    }
  }

  x = start_x;
  dir *= -1;
  
next_level:

  if (y >= 20 ||
      get_cell(y + 1, x) != CELL_ROCK ||
      get_cell(y + 1, x - dir) != CELL_ROCK
    )
  {
    if (get_cell(y + 1, x) == CELL_ROOM)
    {
      set_cell_branch(y, x, CELL_CHASM_T, branch);
      set_cell_branch(y, x - dir, CELL_LOOT, branch);
    }
    else
    {
      set_cell_branch(y, x, CELL_LOOT, branch);
    }

    return true;
  }

  set_cell_branch(y, x, CELL_LADDER_T, branch);

  if (get_cell(y, x + dir) == CELL_ROCK)
    set_cell_branch(y, x + dir, CELL_RESERVED, branch);

  y++;

  set_cell_branch(y, x, CELL_LADDER_B, branch);

  if (get_cell(y, x + dir) == CELL_ROCK)
    set_cell_branch(y, x + dir, CELL_RESERVED, branch);

  dir *= -1;

  l = 15 + rand() % 45;

  while (--l)
  {
    x += dir;

    if (x < 2 || x >= CELLS_W - 2)
      goto next_level;

    if (get_cell(y, x + dir) != CELL_ROCK)
      goto next_level;

    if (get_cell(y, x + (dir * 2)) != CELL_ROCK)
    {
      set_cell_branch(y, x + dir, CELL_RESERVED, branch);
      goto next_level;
    }
    
    set_cell_branch(y, x, CELL_ROOM, branch);
  }

  goto next_level;
  
  return false;
}




int get_cell(int y, int x)
{
  if (y < 0 || y >= MAX_FLOORS || x < 0 || x >= CELLS_W)
    return CELL_ROCK;

  return game->cell[y][x];
}



void set_cell_branch(int y, int x, int token, int branch)
{
  set_branch(y, x, branch);
  set_cell(y, x, token);

  return;
}



void set_branch(int y, int x, int branch)
{
  game->branch[y][x] = branch;

  return;
}


/*
  Sets (Y, X) on the cellmap to TOKEN. If map demo mode is active it
  will also draw the current cellmap on screen and pause for a few ms.
*/
void set_cell(int y, int x, int token)
{
  game->cell[y][x] = token;

  if (map_demo)
  {
    draw_cellmap();
    spause();
    
    if (getch() != ERR)
    {
      quit_game();
      exit(0);
    }
  }

  return;
}



/*
  Returns the branch type for (Y, X) on the cellmap.
*/
int get_branch(int y, int x)
{
  if (y < 0) y = 0;
  if (x < 0) x = 0;
  if (y >= MAX_FLOORS) y = MAX_FLOORS;
  if (x >= CELLS_W) x = CELLS_W;

  return game->branch[y][x];
}



/*
  Resets the cellmap to all rock.
*/
void clear_cellmap()
{
  int y, x;

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      game->cell[y][x] = CELL_ROCK;
      game->branch[y][x] = BRANCH_DUNGEON;
    }
  }

  return;
}



/*
  Populates the cellmap with interesting encounters.
*/
void populate_cellmap(void)
{
  int y;
  int x;
  int original;
  int dir;

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      original = get_cell(y, x);

      // Convert all remainders and dead ends to regular rooms
      if (original == CELL_RMNDR || original == CELL_DEADEND)
	set_cell(y, x, CELL_ROOM);
    }
  }

  place_single_cell(12, CELL_SWSTONE);
  
  for (y = 0; y < MAX_FLOORS; y++)
  {
    if (rand() % 5)
    {
      x = rand() % CELLS_W;
      dir = (x > CELLS_W / 2 ? -1 : +1);
//      x = 1;
//      dir = +1;
      
      while (x > 0 && x < CELLS_W - 1)
      {
	if (get_cell(y, x - 1) > CELL_BLOCKING &&
	    get_cell(y, x + 1) > CELL_BLOCKING &&
	    !water_cell(get_cell(y, x - 1)) &&
	    !water_cell(get_cell(y, x + 1)) &&
	    (get_cell(y, x) == CELL_ROCK ||
	     get_cell(y, x) == CELL_RESERVED))
	{
	  if (get_cell(y, x) == CELL_RESERVED)
	  {
	    int a; int b;
	    a = get_branch(y, x - 1);
	    b = get_branch(y, x + 1);

	    set_branch(y, x, MIN(a, b));
	  }

	  set_cell(y, x, CELL_BRICKWALL);

	  break;
	}
	
	x += dir;
      }
    }

    // Add a tricky enemy (maybe)
    if (y >= 2 && rand() % 2)
    {
      x = rand() % CELLS_W;
      dir = (x > CELLS_W / 2 ? -1 : +1);
      
      do
      {
	if (get_cell(y, x) == CELL_ROOM)
	{
	  set_cell(y, x, CELL_TRICKY);
	  break;
	}
	
	x += dir;
      } while (x > 0 && x < CELLS_W - 1);
    }

    for (x = 0; x < CELLS_W; x++)
    {
      original = get_cell(y, x);

      if (original == CELL_RESERVED)
      {
	set_cell(y, x, CELL_ROCK);
	continue;
      }

      if (original == CELL_WATER)
      {
	if (rand() % 4 == 0)
	  set_cell(y, x, CELL_WMONSTER);
      }

      if (original != CELL_ROOM)
	continue;

      if (y >= NPC_MIN_FLOOR &&
	  game->cell[y][x - 1] < CELL_BLOCKING &&
	  game->cell[y][x + 1] > CELL_BLOCKING &&
	  open_down(game->cell[y - 1][x]) == false)
      {
	set_cell(y, x, CELL_NPC_L);
      }
      else if (y >= NPC_MIN_FLOOR &&
	       game->cell[y][x - 1] > CELL_BLOCKING &&
	       game->cell[y][x + 1] < CELL_BLOCKING &&
	       open_down(game->cell[y - 1][x]) == false)
      {
	set_cell(y, x, CELL_NPC_R);
      }
      else if (original == CELL_ROOM)
      {
	switch (rand() % 50)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	  set_cell(y, x, CELL_MONSTER);
	  break;
	  
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	  set_cell(y, x, CELL_LOOT);
	  break;
	  
	case 20:
	  if (open_down(game->cell[y - 1][x]) == false)
	  {
	    if (y < MAX_FLOORS - 1 &&
		game->cell[y + 1][x] == CELL_ROCK &&
		y > 10 &&
		rand() % 5 == 0)
	    {
	      set_cell(y, x, CELL_TRAPDOOR);
	      set_cell(y + 1, x, CELL_SPIKEPIT);
	    }
	    else if (y >= TRAP_FREE_LEVELS)
	    {
	      // Don't place traps on the first few levels
	      set_cell(y, x, CELL_TRAP);
	    }
	  }
	  break;

	case 21:
	  if (get_cell(y, x - 1) == CELL_ROOM &&
	      get_cell(y, x + 1) == CELL_ROOM)
	  {
	    set_cell(y, x, CELL_CAMP);
	    set_cell(y, x - 1, CELL_KEEPROOM);
	    set_cell(y, x + 1, CELL_KEEPROOM);
	  }
	  break;
	  
	default:
	  break;
	}

	//set_cell(y, x, CELL_TABLET);
      }
    }
  }

  return;
}



/*
  Places a single CELL in a random location below level START_Y.
*/
void place_single_cell(int start_y, int cell)
{
  int y;
  int x;
  int start_x;
  
  y = start_y + (rand() % MAX(1, (MAX_FLOORS - start_y)));

  start_x = x = rand() % CELLS_W;

  while (true)
  {
    if (get_cell(y, x) == CELL_ROOM)
    {
      set_cell(y, x, cell);
      return;
    }
      
    x = (x + 1) % CELLS_W;

    if (x == start_x)
      return;
  }

  return;
}



void make_water(int cy, int cx)
{
  int tx;
  int feet;
  int x;
  int y;
  int w_l;
  int w_r;
  int here;
  int cell_l;
  int cell_r;
  int cell_ul;
  int cell_ur;

  here = get_cell(cy, cx);
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

    if (cell_r == CELL_WSURFACE)
      w_r = 4;

    for (x = tx - w_l; x <= tx + w_r; x++)
    {
      stile(feet + 1, x, TL_SURFACE);
      stile(feet + 2, x, TL_WATER);
    }
  }
  else if (water_cell(here) || here == CELL_WCORR)
  {
    w_l = ((water_cell(cell_l) || cell_l == CELL_WCORR) ? 4 : 2);
    w_r = ((water_cell(cell_r) || cell_r == CELL_WCORR) ? 4 : 2);

/*    if (here == CELL_WCORR && water_cell(cell_ll))
      w_l = 4;

    if (here == CELL_WCORR && water_cell(cell_lr))
    w_r = 4;*/
    
    for (x = tx - w_l; x <= tx + w_r; x++)
    {
      for (y = feet - 5; y <= feet; y++)
      {
	stile(y, x, TL_WATER);
      }
    }

//    w_l = ((water_cell(cell_ul) || cell_ul == CELL_WCORR) ? 4 : 2);
//    w_r = ((water_cell(cell_ur) || cell_ur == CELL_WCORR) ? 4 : 2);
    //tile = get_cell(cy + 1, cx);

    if (here == CELL_WATER/* || tile == CELL_WSURFACE*/)
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



void put_lakes()
{
  int y;
  int x;
  int dir;
   
  for (y = MAX_FLOORS - 2; y > 3; y--)
  {
    x = 5 + rand() % (CELLS_W - 10);
    dir = (rand() % 2 ? +1 : -1);

    while (x > 3 && x < CELLS_W - 3)
    {
      if (get_cell(y - 1, x - 1) == CELL_ROCK &&
	  get_cell(y - 1, x - 0) == CELL_ROCK &&
	  get_cell(y - 1, x + 1) == CELL_ROCK)
      {
	dig_lake_up(y - 1, x, -1);
	dig_lake_up(y - 1, x, +1);
	goto next_floor;
      }
      
      x += dir;
    }

  next_floor:
    ;
  }

  int here;
  int there;
  
  for (y = MAX_FLOORS - 2; y > 3; y--)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      here = get_cell(y, x);
      there = get_cell(y - 1, x);
      
      if ((here == CELL_WCORR)
	  && (there == CELL_WCORR))
      {
	if (rand() % 4)
	  set_cell(y, x, CELL_WATER);
      }
      else if (there == CELL_ROOM)
      {
	if (here == CELL_WCORR && rand() % 4)
	  set_cell(y, x, CELL_WATER);

	here = get_cell(y, x);
	
	if (here == CELL_WATER)
	  set_cell(y - 1, x, CELL_WSURFACE);
      }
    }
  }

  return;
}



int dig_lake_up(int start_y, int start_x, int dir)
{
  int y;
  int x;
  int c;
  int dist;

  if (start_y < 2)
    return false;
  
  y = start_y;
  x = start_x;

  dist = 5 + rand() % 5;

  while (x >= 1 && x <= (CELLS_W - 1))
  {
    c = get_cell(y, x);

    if (c != CELL_ROCK && c != CELL_WCORR)
      break;
    
    x += dir;

    c = get_cell(y, x);

    if (--dist == 0 ||
	(c != CELL_ROCK && c != CELL_WCORR))
    {
      set_cell(y, x - dir, CELL_RESERVED);

      if (dig_lake_up(y - 1, x - dir * 2, dir))
	set_cell(y, x - dir, CELL_WATER);
	
      break;
    }
      
    set_cell(y, x - dir, CELL_WCORR);
  }

  return true;
}




/*
  Converts a populated cellmap to a tilemap.
*/
void convert_cellmap(void)
{
  int cy;
  int cx;
  int tx;
  int feet;
  int this_cell;
  int slide;

  bool open;
  bool open_l;
  bool open_r;
//  int branch;

  for (cy = 0; cy < MAX_FLOORS; cy++)
  {
    for (cx = 1; cx < CELLS_W - 1; cx++)
    {
      this_cell = game->cell[cy][cx];
//      branch = game->branch[cy][cx];

      /*
	Each corridor section will be 9 tiles wide. If we know the
	tiles to the left or right are traversable, we will extend one
	tile further in that direction to meet the next section.
      */
      open   = (cell_open(this_cell)            ? true : false);
      open_l = (cell_open(get_cell(cy, cx - 1)) ? true : false);
      open_r = (cell_open(get_cell(cy, cx + 1)) ? true : false);

      feet = (cy * BOARD_H) + FEET_Y;
      tx = (cx * CELL_TO_TILES) + 4;

      slide = 0;

      if (get_cell(cy, cx - 1) == CELL_ROOM)
	slide -= rand() % 2;

      if (get_cell(cy, cx + 1) == CELL_ROOM)
	slide += rand() % 2;

      if (this_cell == CELL_SPIKEPIT)
	open = false;

      if (open)
      {
	excavate(feet, tx,
		 3 + (open_l ? 1 : 0),
		 3 + (open_r ? 1 : 0));
      }

      switch (game->cell[cy][cx])
      {
      case CELL_WSURFACE:
      case CELL_WATER:
      case CELL_WCORR:
	make_water(cy, cx);
	break;

      case CELL_WMONSTER:
	make_water(cy, cx);
	make_monster(feet, tx, MOB_FISH);
	break;
	
      case CELL_CAMP:
	tx += slide;
	decorate(feet, tx, DEC_CAMP);
	int m;
	m = random_monster(cy, branch_at_tile(feet, tx));
	make_monster(feet, tx - 5, m);
	make_monster(feet, tx + 5, m);
	break;

      case CELL_BRICKWALL:
	decorate(feet, tx, DEC_BRICKS);
	make_monster(feet, tx, MOB_BRICKWALL);
	break;

      case CELL_LADDER_T:
	make_ladder(feet + 1, tx, 4, false);
	break;
	
      case CELL_LADDER_B:
	make_ladder(feet, tx, -(FLOOR_Y + 1), false);
	break;

      case CELL_LADDER:
	make_ladder(feet - FLOOR_Y, tx, FLOOR_H, false);
	break;

      case CELL_PORTAL:
	decorate(feet, tx, DEC_PORTAL);
	break;

      case CELL_DOOR:
	decorate(feet, tx, DEC_DOOR);
	break;

      case CELL_LOOT:
	tx += slide;
//	decorate(feet, tx, DEC_ORB);
	decorate(feet, tx, floor_loot(cy, cx));
	break;

      case CELL_COFFIN:
	tx += slide;
	decorate(feet, tx, DEC_COFFIN);
	set_cell(cy, cx, CELL_LOOT);
	break;

      case CELL_SWSTONE:
	tx += slide;
	decorate(feet, tx, DEC_SWSTONE);
	set_cell(cy, cx, CELL_LOOT);
	break;

      case CELL_TABLET:
	tx += slide;
	decorate(feet, tx, DEC_TABLET);
	set_cell(cy, cx, CELL_LOOT);
	break;

      case CELL_START:
	decorate(feet, tx, DEC_ENTRANCE);
	break;

      case CELL_TRAP:
	tx += slide;
	switch (rand() % 2)
	{
	case 0:
	  stile(feet, tx, TL_T_CAVEIN);
	  break;

	case 1:
	  stile(feet, tx, TL_T_POISON);
	  break;
	}
	break;

      case CELL_TRICKY:
	switch (rand() % (1 + cy / 3))
	{
	case 0:
	  set_cell(cy, cx, CELL_LOOT);
	  make_monster(feet, tx, MOB_MIMIC);
	  break;

	case 1:
	  set_cell(cy, cx, CELL_MONSTER);
	  make_monster(feet, tx, MOB_KNAVE);
	  break;

	case 2:
	  set_cell(cy, cx, CELL_MONSTER);
	  make_monster(feet, tx, MOB_EYE);
	  break;

	default:
	  set_cell(cy, cx, CELL_MONSTER);
	  make_monster(feet, tx, MOB_BIGSPIDER);
	}
	break;

      case CELL_MONSTER:
	make_monster(feet, tx, random_monster(cy, branch_at_tile(feet, tx)));
	break;

      case CELL_BOSS:
	make_monster(feet, tx, MOB_ARCHDEMON);
	break;

      case CELL_GORZOTH_R:
	stile(feet, tx, TL_T_GORZOTH_R);
	break;

      case CELL_GORZOTH_L:
	stile(feet, tx, TL_T_GORZOTH_L);
	break;

      case CELL_CHASM_T:
	make_ladder(feet, tx, 9, true);
	stile(feet + 1, tx, TL_CHASM);
	stile(feet, tx - 3, TL_STOP);
	stile(feet, tx + 3, TL_STOP);

	if (get_cell(cy, cx - 1) == CELL_CHASM_T)
	  make_ladder(feet, tx - 3, 9, true);

	if (get_cell(cy, cx + 1) == CELL_CHASM_T)
	  make_ladder(feet, tx + 3, 9, true);

	break;

      case CELL_CHASM:
	make_ladder(feet - 7, tx, FLOOR_H + 2, true);

	if (get_cell(cy, cx - 1) == CELL_CHASM)
	  make_ladder(feet - 7, tx - 3, FLOOR_H + 2, true);

	if (get_cell(cy, cx + 1) == CELL_CHASM)
	  make_ladder(feet - 7, tx + 3, FLOOR_H + 2, true);

	break;

      case CELL_SPIKEPIT:
	excavate(feet, tx, 1, 1);
	stile(feet, tx - 1, TL_SPIKE);
	stile(feet, tx - 0, TL_SPIKE);
	stile(feet, tx + 1, TL_SPIKE);
	break;
	
      case CELL_TRAPDOOR:
	make_ladder(feet, tx, 9, true);
	decorate(feet, tx, DEC_TRAPDOOR);
	break;

      case CELL_NPC_L:
      case CELL_NPC_R:
	npc_room(feet, tx, game->cell[cy][cx]);
	break;
	
      default:
	break;
      }
      
      if (cx > 0 && get_cell(cy, cx - 1) == CELL_DOOR)
      {
	stile(feet, tx - 4, TL_DOOR_R);
      }
/*      else if (cx < CELLS_W - 1 && get_cell(cy, cx + 1) == CELL_DOOR)
      {
	stile(feet, tx + 5, TL_DOOR_L);
      }
*/
    }
  }
}


/*
  Builds a ladder on the tilemap, starting at (START_Y, START_X) and
  extending TILES downward; if TILES is negative the ladder will
  instead lead up. If CHASM is true no stair will be build, only a
  hole will be carved.
 */
void make_ladder(int start_y, int start_x, int tiles, bool chasm)
{
  int speed;
  int y;

  if (tiles < 0)
  {
    speed = -1;
    tiles *= -1;
  }
  else
    speed = +1;

  y = start_y;

  while (tiles--)
  {
    if (chasm)
    {
      stile(y, start_x - 1, TL_VOID);
      stile(y, start_x + 1, TL_VOID);
      stile(y, start_x, TL_VOID);
    }
    else
    {
      stile(y, start_x - 1, TL_LADDER_L);
      stile(y, start_x + 1, TL_LADDER_R);
      stile(y, start_x, TL_LADDER_M);
    }

    y += speed;
  }
}



/*
  Digs a rectangular hole in the tilemap at (FEET, CENTER), extending
  6 tiles up as well as W_L and W_R additional tiles to the left and
  right.
*/
void excavate(int feet, int center, int w_l, int w_r)
{
  int y;
  int x;

  for (y = feet - 5; y <= feet; y++)
  {
    for (x = center - w_l; x <= center + w_r; x++)
    {
      stile(y, x, TL_VOID);
    }
  }

  return;
}



/*
  Clears the tile map (i.e. the one used for play) to BWALL.
  This also resets all mobs.
*/
void clear_tilemap()
{
  int i, y, x;

  for (i = 0; i < MAX_MOBS; i++)
  {
    game->mob[i].index = i;
    game->mob[i].type = MOB_NONE;
  }

  for (y = 0; y < MAP_H; y++)
    for (x = 0; x < MAP_W; x++)
      game->tile[y][x] = TL_BWALL;

  return;
}



void npc_room(int y, int x, int cell_type)
{
  int npc_type;
  int x_off;

  npc_type = TL_P_NPC1 + rand() % 4;

  if (cell_type == CELL_NPC_R)
  {
    x_off = -1;
    decorate(y, x + 2, DEC_NPC);
    decorate(y, x, DEC_DESK);
    stile(y, x - 3, npc_type);
  }
  else
  {
    x_off = -2;
    decorate(y, x - 2, DEC_NPC);
    decorate(y, x, DEC_DESK);
    stile(y, x + 3, npc_type);
  }

  if (npc_type == TL_P_NPC1)
  {
    stile(y - 5, x + x_off + 0, TL_L_F);
    stile(y - 5, x + x_off + 1, TL_L_O);
    stile(y - 5, x + x_off + 2, TL_L_O);
    stile(y - 5, x + x_off + 3, TL_L_D);
  }
  else if (npc_type == TL_P_NPC2)
  {
    stile(y - 5, x + x_off - 1, TL_L_S);
    stile(y - 5, x + x_off + 0, TL_L_M);
    stile(y - 5, x + x_off + 1, TL_L_I);
    stile(y - 5, x + x_off + 2, TL_L_T);
    stile(y - 5, x + x_off + 3, TL_L_H);
    stile(y - 5, x + x_off + 4, TL_L_Y);
  }
  else if (npc_type == TL_P_NPC3)
  {
    stile(y - 5, x - 1, TL_L_T);
    stile(y - 5, x - 0, TL_L_H);
    stile(y - 5, x + 1, TL_L_E);
    stile(y - 4, x - 1, TL_L_G);
    stile(y - 4, x - 0, TL_L_Y);
    stile(y - 4, x + 1, TL_L_M);
  }
  else if (npc_type == TL_P_NPC4)
  {
    stile(y - 5, x + x_off + 0, TL_L_M);
    stile(y - 5, x + x_off + 1, TL_L_A);
    stile(y - 5, x + x_off + 2, TL_L_P);
    stile(y - 5, x + x_off + 3, TL_L_S);
  }

  return;
}



/* Returns if CELL lets the player fall down (chasms, trapdoors, etc). */
bool open_down(int cell)
{
  if (cell == CELL_CHASM ||
      cell == CELL_TRAPDOOR ||
      cell == CELL_CHASM_T)
    return true;

  return false;
}



int floor_loot(int cy, int cx)
{
  int r;

  if (rand() % 10 == 0)
  {
    // Rare features

    switch (rand() % 10)
    {
    case 0:
      r = DEC_ORB;
      break;
      
    default:
      r = DEC_TABLET;
      break;
    }
  }
  else
  {
    r = DEC_FIRSTRND + rand() % (DEC_COFFIN - 1);
    
    r += rand() % 2;
    
    if (cy > 6)
      r += rand() % 3;
  }
    
  return r;
}



/**
   Returns if this cell should have walls removed to connect with neighbour cells.
 */
int cell_open(int c)
{
  if (c > CELL_CLOSED)
    return false;
  
  if (c > CELL_OPEN)
    return true;

  return false;
}



int water_cell(int c)
{
  if (c == CELL_WATER || c == CELL_WMONSTER || c == CELL_WCORR)
    return true;

  return false;
}

