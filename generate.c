#include "basment.h"



int corridor_stop_y = 0;
int corridor_stop_x = 0;
int hell_ent_y = 0;
int hell_ent_x = 0;



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

    // Remember where the entrance to Hell is (coordinates left by corridor())
    hell_ent_y = corridor_stop_y;
    hell_ent_x = corridor_stop_x;
    set_cell(hell_ent_y, hell_ent_x, CELL_CHASM_T);
    set_cell(hell_ent_y + 1, hell_ent_x, CELL_CHASM);

    // Build Hell below the regular dungeon
    corridor(hell_ent_y + 2, hell_ent_x, 0, false);
    paint_branch(FIRST_HELL_FLOOR - 1, 0, ARCHDEMON_FLOOR, CELLS_W - 1, BRANCH_HELL);

    add_archdemon_floor();

    //normalise_branches();
    add_extra_rooms();
    replace_remainders();

    add_bridges();
    add_surfaces();

    add_ambushes();

    add_shallow_lakes();

    flatten_rooms();
    populate_cellmap();
	
//    link_portals();

    // Fix the start pos
    set_cell(0, start_x, CELL_START);
    set_cell(0, start_x - 1, CELL_ROOM);
    set_cell(0, start_x + 1, CELL_ROOM);

    // Fix the hell entrance
    set_cell(hell_ent_y + 2, hell_ent_x, CELL_HELL_ENT);

    if (get_cell(hell_ent_y + 2, hell_ent_x - 1) != CELL_LADDER_T)    
      set_cell(hell_ent_y + 2, hell_ent_x - 1, CELL_ROOM);

    if (get_cell(hell_ent_y + 2, hell_ent_x + 1) != CELL_LADDER_T)    
      set_cell(hell_ent_y + 2, hell_ent_x + 1, CELL_ROOM);

    if (map_demo)
    {
      delay(2000);
    }
  } while (map_demo);
  
  clear_tilemap();
  convert_cellmap();
  fix_walls();
  decorate_walls();
  decorate_hell();

  return;
}


void normalise_branches()
{
  int y;
  int x;
//  int sx;
  int dir;
  int branch;
  int cell;

  for (y = 0; y <= LAST_NORMAL_FLOOR; y++)
  {
    for (dir = -1; dir <= +1; dir += 2)
    {
      x = (dir == +1 ? 1 : CELLS_W - 2);
      
      branch = get_branch(y, x);

      while (x > 0 && x < CELLS_W - 1)
      {
	cell = get_cell(y, x);

/*	if (cell == CELL_ROCK)
	{
	  branch = get_branch(y, x + dir);
	  x += dir;
	  continue;
	  }*/
	
	if (cell == CELL_DOOR || cell == CELL_ROCK || cell == CELL_RMNDR)
	{
	  branch = get_branch(y, x + dir);
	  x += dir * 2;
	  continue;
	}

	if (get_branch(y, x) != branch)
	  set_branch(y, x, branch);

	x += dir;
      }
    }
  }
}


void replace_remainders()
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
	// Reserve 5 cells on 2 floors; these must be reserved as rooms
	cell_range(y, x, y + 1, x + dir * 4, CELL_KEEPROOM, true);

	// Add the Gorzoth ambush on the left or right end
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



/**
 */
void add_extra_rooms(void)
{
  int y;
  int x;
  int w;
  int d;
  int start_x;
  int dir;
  int branch = BRANCH_DUNGEON;

  NOW_WORKING;

  for (y = 1; y < LAST_NORMAL_FLOOR - 2; y++)
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

	  // Make it the same branch as the room above
	  branch = get_branch(y - 1, x);
	  set_branch(y, x, branch);
	}
	else
	{
	  set_cell(y, x, CELL_DEADEND);
	  set_branch(y, x, branch);
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
void dig(int start_y, int x, int speed, int depth, int allow_chasms)
{
  int y;
  bool chasm = false;

  if (allow_chasms && speed < 0 && rand() % 3 == 0)
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



int branch;
int branch_dist;


void corridor(int y, int start_x, int speed, int remainder)
{
  int x;
  int i;
  int length;
  int dug;
  int edge_clear;

  NOW_WORKING;

  if (remainder)
  {
    if (speed)
      branch = get_branch(y, start_x - speed);
    else
      branch = get_branch(y + 1, start_x);

//    branch = BRANCH_ICECAVE;
  }
  else if (y == 0)
  {
    branch = BRANCH_DUNGEON;
    branch_dist = 10 + rand() % 20;
  }
  
  x = start_x;

  dug = 0;

  if (remainder)
    edge_clear = 0;
  else
    edge_clear = 0;

  if (speed == 0)
    length = 3 + rand() % 25;
  else
    length = 3 + rand() % 10;

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
      if (get_cell(y, x + speed) != CELL_ROCK &&
	  get_cell(y, x - speed) == CELL_ROCK)
      {
	speed *= -1;
      }
    }
  }
  
  if (!remainder)
  {
    set_cell(y, x, CELL_LADDER_B);
    set_branch(y, x, branch);

    // Try to avoid placing doors next to ladders
    branch_dist += 1 + rand() % 3;
  }

  for (i = 0; i < length; i++)
  {
    if ((x <= 1 + edge_clear && speed < 0) || (x >= CELLS_W - 2 - edge_clear && speed > 0))
      break;

    x += speed;

    if (get_cell(y, x) != CELL_ROCK)
    {
      x -= speed;
      break;
    }

    if (!remainder && branch_dist && --branch_dist == 0)
    {
//	if (rand
//      branch = (branch + (rand() % BRANCH_HELL)) % BRANCH_HELL;
      branch = rand() % BRANCH_HELL;
      branch_dist = 5 + rand() % 15;
      set_cell(y, x, CELL_DOOR);
      set_branch(y, x, branch);
    }
    else
    {
      set_cell(y, x, (remainder ? CELL_RMNDR : CELL_ROOM));
      set_branch(y, x, branch);
    }
    
    dug++;
  }

  if (y == LAST_NORMAL_FLOOR || y == LAST_HELL_FLOOR)
  {
    if (!remainder)
    {
      corridor_stop_y = y;
      corridor_stop_x = x;

      set_cell(y, x, CELL_BOSS);

      if (y == LAST_NORMAL_FLOOR)
      {
	// Only do this for the normal dungeon

	for (i = 0; i < 3; i++)
	  make_branch();
	
	put_lakes();
      }
    }
  }
  else if (!remainder)
  {
    // We're still in the main corridor; dig down and start a new corridor.

    dig(y, x, +1, 1, false);

    corridor(y, x, speed, true);
  }
  else if (remainder && dug > 3)
  {
    int up;

    up = 1 + (rand() % (1 + rand() % 4));

    for (i = 0; i < up; i++)
    {
      if (y - i - 1 < 1 ||
	  (y >= FIRST_HELL_FLOOR && y - i - 1 < FIRST_HELL_FLOOR))
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
    {
      // Don't dig chasms from air pockets
      dig(y, x, -1, up, (remainder == 2 ? false : true));
    }
  }

  if (!remainder && y >= 0)
  {
    corridor(y, start_x, speed * -1, true);
  }

  return;
}




void paint_branch(int t, int l, int b, int r, int branch)
{
  int y;
  int x;

  for (y = t; y <= b; y++)
    for (x = l; x <= r; x++)
      set_branch(y, x, branch);

  return;
}




bool make_branch()
{
  int start_y;
  int start_x;
  int dir;

  int y;
  int x;

  int l;

  int branch;

  NOW_WORKING;

  branch = 1 + rand() % (BRANCHES - 1);
//  branch = BRANCH_ICECAVE;

  start_y = 1 + rand() % (LAST_NORMAL_FLOOR - 4);

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
    int input;
  
    draw_cellmap();
    spause();

    input = getch();

    if (input == 'f')
    {
      flip_automap();
    }
    else if (input != ERR)
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


/**
   Convert all remainders and dead ends to regular rooms.
*/
void flatten_rooms()
{
  int y;
  int x;
  int original;

  NOW_WORKING;
  
  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      original = get_cell(y, x);

      if (original == CELL_RMNDR || original == CELL_DEADEND)
	set_cell(y, x, CELL_ROOM);
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
  int i;

  NOW_WORKING;
    
  place_single_cell(12, CELL_SWSTONE);
  place_single_cell(8, CELL_DISCO);

  for (i = 0; i < 3; i++)
  {
    place_single_cell(1, CELL_TABLET);
    place_single_cell(1, CELL_ORB);
  }

  for (i = 0; i < 5; i++)
    place_single_cell(10, CELL_IDOL);

  // Only place as many of these as there are books
  for (i = 0; i < BOOKS; i++)
    place_single_cell(3, CELL_BOOKSHELF);
 
/*
  for (i = 0; i < 200; i++)
  {
    place_single_cell(10, CELL_TRAP);
  }
*/
 
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

      if (original == CELL_WOPENDOWN)
      {
	switch (rand() % 5)
	{
	case 0:  set_cell(y, x, CELL_WMONSTER);    break;
	case 2:  set_cell(y, x, CELL_WTRAP);       break;
	default: break;
	}
      }
      else if (original == CELL_WATER)
      {
	switch (rand() % 8)
	{
	case 0:
	  if (wopen_cell(get_cell(y + 1, x)) == false)
	  {
	    set_cell(y, x, CELL_WLOOT);
	    break;
	  }
	case 1:  set_cell(y, x, CELL_WMONSTER);    break;
	default: break;
	}
      }
      else if (original == CELL_WCORR)
      {
	switch (rand() % 8)
	{
	case 0:  set_cell(y, x, CELL_WCORRMON);    break;
	case 1:  set_cell(y, x, CELL_WCORRLOOT);   break;
//	case 2:  set_cell(y, x, CELL_WCORRTRAP);   break;
	default: break;
	}
      }
      else if (original == CELL_BRIDGE_C ||
	       original == CELL_BRIDGE_W)
      {
	if (rand() % 5 == 0)
	{
	  set_cell(y, x, (original == CELL_BRIDGE_C ? CELL_BRIDGE_CM : CELL_BRIDGE_WM));
	}
      }

      if (original != CELL_ROOM)
	continue;

      if (y >= NPC_MIN_FLOOR &&
	  get_cell(y, x - 1) < CELL_BLOCKING &&
	  get_cell(y, x + 1) > CELL_BLOCKING &&
	  open_down(get_cell(y - 1, x)) == false)
      {
	set_cell(y, x, CELL_NPC_L);
      }
      else if (y >= NPC_MIN_FLOOR &&
	       get_cell(y, x - 1) > CELL_BLOCKING &&
	       get_cell(y, x + 1) < CELL_BLOCKING &&
	       open_down(get_cell(y - 1, x)) == false)
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
	  if (open_down(get_cell(y - 1, x)) == false)
	  {
	    if (y < LAST_HELL_FLOOR - 1 && // Don't create these in archdemon lair
		get_cell(y + 1, x) == CELL_ROCK &&
		y > 10 &&
		rand() % 4 == 0)
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
  int cell_l;
  int cell_r;
  int cell_above;
  int slide;

  int open;
  int open_l;
  int open_r;
//  int branch;

  for (cy = 0; cy < MAX_FLOORS; cy++)
  {
    for (cx = 1; cx < CELLS_W - 1; cx++)
    {
      this_cell = get_cell(cy, cx);
      cell_l = get_cell(cy, cx - 1);
      cell_r = get_cell(cy, cx + 1);
      cell_above = get_cell(cy - 1, cx);
//      branch = game->branch[cy][cx];

      /*
	Each corridor section will be 9 tiles wide. If we know the
	tiles to the left or right are traversable, we will extend one
	tile further in that direction to meet the next section.
      */
      open   = (cell_open(this_cell) ? 1 : 0);
      open_l = (cell_open(cell_l)    ? 1 : 0);
      open_r = (cell_open(cell_r)    ? 1 : 0);

      feet = (cy * BOARD_H) + FEET_Y;
      tx = (cx * CELL_TO_TILES) + 4;

      slide = 0;

      /*
	If the cells to the left and right are empty rooms we have
	some room to spare; add a chance of nudging any decoration on
	this cell -2 to +2 tiles to make them look less grid-like.
      */
      if (cell_l == CELL_ROOM)
	slide -= rand() % 2;

      if (cell_r == CELL_ROOM)
	slide += rand() % 2;

      if (this_cell == CELL_SPIKEPIT)
	open = false;

      /*
	Trim one tile off the excavation width for water surfaces and
	bridges ending in a wall. This prevents a small useless ledge
	from being created at the end and gives a cleaner result.
      */
      if (this_cell == CELL_WSURFACE ||
	  is_bridge(this_cell))
      {
	if (cell_l == CELL_ROCK)
	  open_l = -1;
	
	if (cell_r == CELL_ROCK)
	  open_r = -1;
      }

      // Hack to make the walls align in archdemon lair
      if (this_cell == CELL_OPENLADDER)
      {
	if (cell_l == CELL_ROCK)
	  open_l += 1;
	else if (cell_r == CELL_ROCK)
	  open_r += 1;
      }
      
      if (open)
      {
	excavate(feet, tx, 3 + open_l, 3 + open_r);
      }

      switch (this_cell)
      {
      case CELL_WSURFACE:
      case CELL_WATER:
      case CELL_WCORR:
      case CELL_WOPENDOWN:
	make_water(cy, cx);
	break;

      case CELL_WLOOT:
      case CELL_WCORRLOOT:
	make_water(cy, cx);
	decorate(feet, tx, DEC_UWCHEST);
	break;

      case CELL_WMONSTER:
      case CELL_WCORRMON:
	make_water(cy, cx);
	water_monster(feet, tx, cy, cx);
	break;

      case CELL_WTRAP:
      case CELL_WCORRTRAP:
	make_water(cy, cx);
	tx += slide;
	stile(feet, tx, TL_T_UWNET);
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
	if (get_branch(cy, cx) == BRANCH_DUNGEON)
	  decorate(feet, tx, DEC_BRICKS);
	
	make_monster(feet, tx, MOB_BRICKWALL);
	break;

      case CELL_DISCO:
	decorate(feet, tx, DEC_DISCO);
	set_cell(cy, cx, CELL_LOOT);
	break;
	
      case CELL_BRIDGE_C:
      case CELL_BRIDGE_W:
      case CELL_BRIDGE_CM:
      case CELL_BRIDGE_WM:
	make_bridge(cy, cx);

	if (this_cell == CELL_BRIDGE_CM || this_cell == CELL_BRIDGE_WM)
	{
	  m = random_monster(cy, branch_at_tile(feet, tx));
	    
	  if (rand() % 3 == 0)
	    m = MOB_IMP;
	  
	  make_monster(feet, tx, m);
	}
	break;

      case CELL_OPENDOWN:
	remove_floor(cy, cx, 4);
	break;

      case CELL_LADDER_T:
	make_ladder(feet + 1, tx, 4, false);
	break;
	
      case CELL_LADDER:
      case CELL_OPENLADDER:
	if (this_cell == CELL_OPENLADDER)
	  remove_floor(cy, cx, 4);
	
	make_ladder(feet - FLOOR_Y, tx, FLOOR_H, false);
	break;

      case CELL_LADDER_B:
      case CELL_OPENLADDER_B:
	if (this_cell == CELL_OPENLADDER_B)
	  excavate(feet, tx, 4, 4);

	make_ladder(feet, tx, -(FLOOR_Y + 1), false);
	break;

      case CELL_PORTAL:
	decorate(feet, tx, DEC_PORTAL);
	break;

      case CELL_DOOR:
	decorate(feet, tx, DEC_DOOR);
	break;

      case CELL_LOOT:
	tx += slide;
	decorate(feet, tx, floor_loot(cy, cx));
	break;

      case CELL_BOOKSHELF:
	tx += slide;
	decorate(feet, tx, DEC_BOOKSHELF);
	set_cell(cy, cx, CELL_LOOT);
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

      case CELL_ORB:
	tx += slide;
	decorate(feet, tx, DEC_ORB);
	set_cell(cy, cx, CELL_LOOT);
	break;

      case CELL_HELL_ENT:
	stile(feet, tx, TL_P_HELL);
	set_cell(cy, cx, CELL_ROOM);
	break;

      case CELL_IDOL:
	tx += slide;
	decorate(feet, tx, DEC_IDOL);
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
	switch (rand() % 4)
	{
	case 0:
	  // Only create these if there is a ceiling
	  if (cell_above != CELL_BRIDGE_C &&
	      cell_above != CELL_BRIDGE_CM &&
	      cell_above != CELL_OPENDOWN &&
	      cell_above != CELL_CHASM &&
	      cell_above != CELL_CHASM_T &&
	      cell_above != CELL_TRAPDOOR)
	  {
	    decorate(feet, tx, DEC_CAVEIN);
	  }
	  break;

	case 1:
	  stile(feet, tx, TL_T_POISON);
	  break;

	case 2:
	  stile(feet, tx, TL_T_WEB);
	  break;

	case 3:
	  stile(feet, tx, TL_T_FLASH);
	  break;
	}
	break;

      case CELL_TRICKY:
	switch (rand() % (1 + cy / 3))
	{
	case 0:
	  // Make this appear as loot on the map
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
      case CELL_SUSHI_L:
      case CELL_SUSHI_R:
	npc_room(feet, tx, game->cell[cy][cx]);
	break;

      default:
	break;
      }
      
      // Hack: add DOOR_R trigger if left cell is door
      if (cx > 0 && get_cell(cy, cx - 1) == CELL_DOOR)
      {
	stile(feet, tx - 4, TL_DOOR_R);
      }
    }
  }
}






/*
  Builds a ladder on the tilemap, starting at (START_Y, START_X) and
  extending TILES downward; if TILES is negative the ladder will
  instead lead up. If CHASM is true no ladder will be built, only a
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

  if (cell_type == CELL_SUSHI_L || cell_type == CELL_SUSHI_R)
  {
    if (rand() % 2 == 0)
      npc_type = TL_P_NPC_SUSHI;
    else
      npc_type = TL_P_NPC_SCUBA;
  }
  else
  {
    npc_type = TL_P_NPC1 + rand() % 6;

    if (rand() % 10 == 0)
      npc_type = TL_P_NPC_SCUBA;

    if (rand() % 20 == 0)
      npc_type = TL_P_NPC_CLOSED;
  }

  npc_type = TL_P_NPC_RANGED;

  if (cell_type == CELL_NPC_R || cell_type == CELL_SUSHI_R)
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
    stile(y - 4, x + x_off + 0, TL_L_F);
    stile(y - 4, x + x_off + 1, TL_L_O);
    stile(y - 4, x + x_off + 2, TL_L_O);
    stile(y - 4, x + x_off + 3, TL_L_D);
  }
  else if (npc_type == TL_P_NPC2)
  {
    if (rand() % 2)
    {
      stile(y - 5, x + x_off - 1, TL_L_B);
      stile(y - 5, x + x_off + 0, TL_L_L);
      stile(y - 5, x + x_off + 1, TL_L_A);
      stile(y - 5, x + x_off + 2, TL_L_C);
      stile(y - 5, x + x_off + 3, TL_L_K);
      stile(y - 4, x + x_off - 1, TL_L_S);
      stile(y - 4, x + x_off + 0, TL_L_M);
      stile(y - 4, x + x_off + 1, TL_L_I);
      stile(y - 4, x + x_off + 2, TL_L_T);
      stile(y - 4, x + x_off + 3, TL_L_H);
    }
    else
    {
      stile(y - 4, x + x_off - 1, TL_L_S);
      stile(y - 4, x + x_off + 0, TL_L_M);
      stile(y - 4, x + x_off + 1, TL_L_I);
      stile(y - 4, x + x_off + 2, TL_L_T);
      stile(y - 4, x + x_off + 3, TL_L_H);
      stile(y - 4, x + x_off + 4, TL_L_Y);
    }
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
    stile(y - 4, x + x_off + 0, TL_L_M);
    stile(y - 4, x + x_off + 1, TL_L_A);
    stile(y - 4, x + x_off + 2, TL_L_P);
    stile(y - 4, x + x_off + 3, TL_L_S);
  }
  else if (npc_type == TL_P_NPC_SCUBA)
  {
    stile(y - 5, x + x_off - 1, TL_L_S);
    stile(y - 5, x + x_off + 0, TL_L_C);
    stile(y - 5, x + x_off + 1, TL_L_U);
    stile(y - 5, x + x_off + 2, TL_L_B);
    stile(y - 5, x + x_off + 3, TL_L_A);
    stile(y - 4, x + x_off + 0, TL_L_G);
    stile(y - 4, x + x_off + 1, TL_L_E);
    stile(y - 4, x + x_off + 2, TL_L_A);
    stile(y - 4, x + x_off + 3, TL_L_R);
  }
  else if (npc_type == TL_P_NPC_BAR)
  {
    stile(y - 4, x - 1, TL_L_BAR_B);
    stile(y - 4, x + 0, TL_L_BAR_A);
    stile(y - 4, x + 1, TL_L_BAR_R);
  }
  else if (npc_type == TL_P_NPC_ARMOR)
  {
    stile(y - 4, x + x_off - 1, TL_L_A);
    stile(y - 4, x + x_off - 0, TL_L_R);
    stile(y - 4, x + x_off + 1, TL_L_M);
    stile(y - 4, x + x_off + 2, TL_L_O);
    stile(y - 4, x + x_off + 3, TL_L_R);
  }
  else if (npc_type == TL_P_NPC_RANGED)
  {
    stile(y - 4, x + x_off - 1, TL_L_M);
    stile(y - 4, x + x_off - 0, TL_L_R);
    stile(y - 4, x + x_off + 1, TL_L_M);
    stile(y - 4, x + x_off + 2, TL_L_O);
    stile(y - 4, x + x_off + 3, TL_L_R);
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
  int branch;

  branch = get_branch(cy, cx);

  if (branch == BRANCH_CRYPT)
  {
    if (rand() % 5 == 0)
      return DEC_COFFIN;
    else if (rand() % 3 == 0)
      return DEC_SKELETON;
  }

  r = DEC_FIRSTRND + rand() % (DEC_LASTRND - DEC_FIRSTRND - 1);
    
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


void remove_floor(int cy, int cx, int w)
{
  int x;
  int y;
  int tx;
  int feet;

  CELL_CENTER(cy, cx, feet, tx);

  for (x = tx - w; x <= tx + w; x++)
  {
    for (y = feet + 1; y < feet + 8; y++)
    {
      stile(y, x, TL_VOID);
    }
  }

  return;
}
