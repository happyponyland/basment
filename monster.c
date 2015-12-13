#include "basment.h"
#include "map.h"


char * article[] =
{
  [ART_NONE] = "",
  [ART_THE]  = "THE ",
  [ART_A]    = "A ",
  [ART_AN]   = "AN "
};


char * mob_name[MOB_LAST] =
{
  [MOB_NONE] = "(BUG)",
  [MOB_PLAYER] = "(BUG)",
  [MOB_GORE] = "(BUG)",
  [MOB_SPIDER] = "SPIDER",
  [MOB_SNAKE] = "SNAKE",
  [MOB_GHOUL] = "GHOUL",
  [MOB_GIANT] = "GIANT",
  [MOB_KNAVE] = "KNAVE",
  [MOB_MIMIC] = "MIMIC",
  [MOB_EYE] = "FLOATING EYE",
  [MOB_GNOBLIN] = "GNOBLIN",
  [MOB_ROGUE] = "ROGUE",
  [MOB_LICH] = "LICH",
  [MOB_DKNIGHT] = "DEATH KNIGHT",
  [MOB_IMP] = "IMP",
  [MOB_SCAAL] = "SCAAL",
  [MOB_DEMON] = "DEMON",
  [MOB_BLURK] = "BLURK",
  [MOB_NOSE] = "GIANT NOSE",
  [MOB_ELEMENTAL] = "ELEMENTAL",
  [MOB_EVILTREE] = "EVIL TREE",
  [MOB_SKELETON] = "SKELETON",
  [MOB_SAUCEROR] = "SAUCEROR",
  [MOB_ARCHDEMON] = "ARCHDEMON",
  [MOB_GORZOTH] = "GORZOTH",
  [MOB_MOTH] = "MOTH-THING",
  [MOB_SHRUBBERY] = "SHRUBBERY",
  [MOB_BIGSPIDER] = "ARAQNO",
  [MOB_BRICKWALL] = "BRICK WALL",
  [MOB_FISH] = "FISH",
  [MOB_CRAB] = "CRAB"
};



int make_monster(int y, int x, int type)
{
  int i;
  mob_t * mob;

  if (type == MOB_ARCHDEMON)
  {
    mob = &game->mob[1];
  }
  else
  {
    i = free_mob();
    
    if (i < 0)
      return -1;

    mob = &game->mob[i];
  }

  mob->type = type;
  mob->x = x;
  mob->y = y;

  mob->breath = 0;
  mob->webbed = 0;

  mob->strength = 1;
  mob->damage = 1;

  mob->gp = 0;

  mob->armor_type = 0;
  mob->shd_type = 0;

  mob->article = ART_A;
  mob->attack_frames = 1;

  mob->attack_phase = 0;

  mob->follow_floor = 0;
  mob->flying = 0;

  mob->w = mob->pack_w = 5;
  mob->front_w = 0;

  if (rand() % 2 == 0)
    mob->flip = true;
  else
    mob->flip = false;
  
  switch (type)
  {
  case MOB_SPIDER:
    mob->w = 3;
    mob->pack_w = 3;
    mob->speed = 5;
    mob->steps = 3;
    mob->range = 5;
    mob->hp = 6;
    mob->exp = 20;
    mob->damage = 5;
    break;

  case MOB_SNAKE:
    mob->w = 3;
    mob->pack_w = 3;
    mob->speed = 4;
    mob->steps = 7;
    mob->range = 5;
    mob->hp = 3;
    mob->exp = 15;
    mob->damage = 3;
    break;

  case MOB_GIANT:
    mob->w = 1;
    mob->pack_w = 1;
    mob->front_w = +1;
    mob->speed = 6;
    mob->steps = 6;
    mob->range = 4;
    mob->hp = 15;
    mob->armor_type = ARMOR_LEATHER;
    mob->exp = 100;
    mob->damage = 7;
    mob->attack_frames = 2;
    break;

  case MOB_ROGUE:
    mob->w = 2;
    mob->pack_w = 1;
    mob->front_w = +1;
    mob->speed = 13;
    mob->steps = 3;
    mob->range = 4;
    mob->hp = 8;
    mob->armor_type = ARMOR_LEATHER;
    mob->exp = 60;
    mob->damage = 3;
    break;

  case MOB_BRICKWALL:
    mob->pack_w = mob->w = 4;
    mob->speed = 0;
    mob->steps = 0;
    mob->range = 0;
    mob->hp = 20;
    mob->armor_type = ARMOR_SPIDER;
    mob->exp = 5;
    mob->damage = 0;
    break;

  case MOB_BIGSPIDER:
    mob->article = ART_AN;
    mob->w = 8;
    mob->pack_w = 7;
    mob->speed = 13;
    mob->steps = 6;
    mob->range = 10;
    mob->hp = 8;
    mob->armor_type = ARMOR_SPIDER;
    mob->exp = 400;
    mob->damage = 6;
    mob->flying = 1; // not actually flying but too large to submerge
    break;

  case MOB_EVILTREE:
    mob->article = ART_AN;
    mob->w = 5;
    mob->pack_w = 7;
    mob->speed = 6;
    mob->steps = 3;
    mob->range = 10;
    mob->hp = 40;
    mob->exp = 1200;
    mob->attack_frames = 2;
    mob->damage = 16;
    break;

  case MOB_SHRUBBERY:
    mob->w = 2;
    mob->pack_w = 3;
    mob->speed = 0;
    mob->steps = 0;
    mob->range = 0;
    mob->hp = 60;
    mob->exp = 100;
    mob->damage = 0;
    break;

  case MOB_BLURK:
    mob->attack_frames = 2;
    mob->w = 4;
    mob->pack_w = 5;
    mob->speed = 12;
    mob->steps = 6;
    mob->range = 10;
    mob->hp = 20;
    mob->exp = 100;
    mob->damage = 6;
    mob->flags = GFX_BLURK_IDLE;
    break;

  case MOB_ELEMENTAL:
    mob->article = ART_AN;
    mob->w = 4;
    mob->speed = 12;
    mob->steps = 6;
    mob->range = 8;
    mob->hp = 20;
    mob->exp = 100;
    mob->damage = 6;
    mob->flying = 1;
    break;

  case MOB_MIMIC:
    mob->w = 3;
    mob->speed = 8;
    mob->steps = 4;
    mob->range = 6;
    mob->hp = 20;
    mob->exp = 150;
    mob->damage = 6;
    mob->attack_phase = 0;
    mob->flags = GFX_MIMIC_IDLE;
    break;

  case MOB_IMP:
    mob->article = ART_AN;
    mob->w = 3;
    mob->pack_w = 3;
    mob->speed = 9;
    mob->steps = 8;
    mob->range = 5;
    mob->hp = 22;
    mob->exp = 250;
    mob->damage = 8;
    mob->flying = 1;
    break;

  case MOB_MOTH:
    mob->w = 3;
    mob->pack_w = 4;
    mob->speed = 12;
    mob->steps = 16;
    mob->range = 5;
    mob->hp = 30;
    mob->exp = 400;
    mob->damage = 12;
    mob->flying = 1;
    break;

  case MOB_FISH:
    mob->w = 3;
    mob->speed = 7;
    mob->steps = 3;
    mob->range = 5;
    mob->hp = 40;
    mob->exp = 500;
    mob->damage = 8;
    break;

  case MOB_CRAB:
    mob->follow_floor = 1;
    mob->w = 4;
    mob->speed = 6;
    mob->steps = 4;
    mob->range = 8;
    mob->hp = 50;
    mob->exp = 800;
    mob->damage = 8;
    break;

  case MOB_NOSE:
    mob->w = 4;
    mob->pack_w = 4;
    mob->speed = 22;
    mob->steps = 2;
    mob->range = 6;
    mob->hp = 25;
    mob->exp = 400;
    mob->damage = 3;
    mob->flying = 1;
    break;

  case MOB_EYE:
    mob->w = 4;
    mob->speed = 5;
    mob->steps = 1;
    mob->range = 5;
    mob->hp = 25;
    mob->exp = 500;
    mob->damage = 12;
    mob->flying = 1;
    break;

  case MOB_GHOUL:
    mob->w = 1;
    mob->pack_w = 2;
    mob->speed = 5;
    mob->steps = 4;
    mob->range = 4;
    mob->hp = 8;
    mob->exp = 40;
    mob->damage = 7;
    break;

  case MOB_GNOBLIN:
    mob->w = 1;
    mob->pack_w = 1;
    mob->front_w = +1;
    mob->speed = 3;
    mob->steps = 6;
    mob->range = 4;
    mob->hp = 8;
    mob->exp = 40;
    mob->damage = 3;
    break;

  case MOB_KNAVE:
    mob->w = 2;
    mob->pack_w = 2;
    mob->speed = 10;
    mob->steps = 4;
    mob->range = 5;
    mob->hp = 35;
    mob->armor_type = ARMOR_SCALE;
    mob->exp = 200;
    mob->damage = 6;
    mob->shd_type = SHD_MAGIC;
    break;

  case MOB_LICH:
    mob->w = 3;
    mob->pack_w = 2;
    mob->front_w = +1;
    mob->speed = 8;
    mob->steps = 4;
    mob->range = 5;
    mob->hp = 28;
    mob->exp = 400;
    mob->damage = 6;
    mob->follow_floor = 1;
    break;

  case MOB_DKNIGHT:
    mob->attack_frames = 2;
    mob->w = 3;
    mob->pack_w = 3;
    mob->speed = 12;
    mob->steps = 6;
    mob->range = 8;
    mob->armor_type = ARMOR_SCALE;
    mob->hp = 30;
    mob->exp = 600;
    mob->damage = 10;
    break;

  case MOB_SKELETON:
    mob->attack_frames = 2;
    mob->w = 2;
    mob->pack_w = 3;
    mob->front_w = -1;
    mob->speed = 12;
    mob->steps = 3;
    mob->range = 6;
//    mob->armor_type = ARMOR_SCALE;
    mob->hp = 20;
    mob->exp = 400;
    mob->damage = 8;
    break;

  case MOB_DEMON:
    mob->w = 3;
    mob->speed = 9;
    mob->steps = 6;
    mob->range = 5;
    mob->hp = 40;
    mob->exp = 800;
    mob->damage = 5;
    break;

  case MOB_ARCHDEMON:
    mob->w = 4;
    mob->speed = 15;
    mob->steps = 8;
    mob->range = 6;
    mob->hp = 98;
    mob->exp = 0;
    mob->damage = 8;
    mob->article = ART_THE;
    break;

  case MOB_GORZOTH:
    mob->w = 4;
    mob->speed = 18;
    mob->steps = 8;
    mob->range = 6;
    mob->armor_type = ARMOR_LEATHER;
    mob->hp = 66;
    mob->exp = 5000;
    mob->damage = 8;
    mob->article = ART_NONE;
    mob->flying = 1;
    break;
  }

  mob->counter = 0;
  mob->alert = false;

  return i;
}



int mob_packwl(mob_t * mob)
{
  return (mob->pack_w + (mob->flip ? mob->front_w : 0));
}


int mob_packwr(mob_t * mob)
{  
  return (mob->pack_w + (mob->flip ? 0 : mob->front_w));
}





/**
   Returns the index of the first free spot in the mob array, or -1 if
   it's full.
*/
int free_mob()
{
  int i;
  
  // Reserve 0 for player, 1 for boss
  for (i = 2; i < MAX_MOBS; i++)
  {
    if (game->mob[i].type == MOB_NONE)
      return i;
  }
  
  return -1;
}



/**
   Returns if a monster is visible in the viewport.
*/
int on_board(mob_t * mob)
{
  int sc_w;
  int sc_x;
  int sc_y;

  sc_w = mob->w + 1;
  sc_y = mob->y - view_y;
  sc_x = mob->x - view_x;
  
  if (sc_x < -sc_w ||
      sc_x > BOARD_W + sc_w + 1 ||
      sc_y < 1 ||
      sc_y >= BOARD_H + FLOOR_Y - 1)
  {
    return false;
  }
  
  return true;
}



void mob_walk(int mi, int dist)
{
  mob_t * mob;
  int speed;
  int remaining;

  mob = &game->mob[mi];

  if (dist < 0)
  {
    speed = -1;
    dist *= -1;
    mob->flip = true;
  }
  else
  {
    speed = +1;
    mob->flip = false;
  }

  remaining = dist;

  while (remaining-- > 0)
  {
    if (on_board(mob))
    {
      if (melee(mob, speed))
      {
	if (mob->type == MOB_KNAVE)
	{
	  mob->attack_phase = 0;
	  knave_shield(mob, true);
	}

	return;
      }
    }

    if (mob->follow_floor &&
	gtile(mob->y + 1, mob->x + (mob->w) * speed) < TL_BLOCKING)
    {
      frustration(mob);
      return;
    }
    
    if (gtile(mob->y, mob->x + (mob->w + 1) * speed) > TL_BLOCKING)
      return;

    if (anyone_there(mob->y, mob->x + (speed == +1 ? mob_packwr(mob) + 1 : -mob_packwl(mob) - 1)) >= 0)
      return;
    
    mob->x += speed;

    if (on_board(mob))
    {
      draw_board();

      if (monster_trap(mob))
	return;

      if (remaining > 0 || dist == 1)
	spause();
    }
  }

  return;
}



int anyone_there(int y, int x)
{
  int i;
  mob_t * m;

  for (i = 0; i < MAX_MOBS; i++)
  {
    m = &game->mob[i];
    
    if (m->type != MOB_NONE &&
	m->y == y &&
	x > m->x - mob_packwl(m) - 1 &&
	x < m->x + mob_packwr(m) + 1)
    {
      return i;
    }
  }

  return -1;
}



void frustration(mob_t * mob)
{
  if (mob->type == MOB_CRAB && on_board(mob))
  {
    mob->flags = GFX_ATTACK2;
    draw_board(); lpause();
    mob->flags = 0;
  }

  return;
}



void move_towards_player(mob_t * mob)
{
  if (player->x < mob->x)
    mob_walk(mob->index, mob->steps * -1);
  else
    mob_walk(mob->index, mob->steps);

  return;
}



mob_t * find_enemy(mob_t * mob, int y, int x)
{
  int i;
  mob_t * t;
  int r;

  if (mob == player)
  {
    r = 1;
    i = MAX_MOBS - 1;
  }
  else if (mob == NULL)
  {
    r = 0;
    i = MAX_MOBS - 1;
  }
  else
  {   
    r = 0;
    i = 0;
  }

  for (   ; i >= r; i--)
  {
    t = &game->mob[i];

    if (t == mob)
      continue;

    if (t->type == MOB_NONE)
      continue;

    if (y != t->y)
      continue;

    if (x <= t->x - t->w || x >= t->x + t->w + 1)
      continue;

    return t;
  }

  return NULL;
}



/*
  Returns the index of a random monster suitable for FLOOR. Note that
  floor is 0-based in this function.
*/
int random_monster(int floor, int branch)
{
  int base;
  int random;
  int choice;
  
//  return MOB_BRICKWALL;
//  return MOB_ELEMENTAL;
//  return MOB_SKELETON;
//  return MOB_ARCHDEMON;
//  return MOB_GORZOTH;
//  return MOB_BIGSPIDER;

  if (branch == BRANCH_CRYPT)
  {
    switch (rand() % 7)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      choice = MOB_GHOUL;
      break;

    case 4:
      choice = MOB_LICH;
      break;

    case 5:
      choice = MOB_DKNIGHT;
      break;

    default:
      goto regular;
    }
  }
  else if (branch == BRANCH_ORGANIC)
  {
    switch (rand() % 4)
    {
    case 0:
    case 1:
    case 2:
      choice = MOB_BLURK;
      break;

    case 3:
      choice = MOB_BIGSPIDER;
      break;

    default:
      goto regular;
    }
  }
  else if (branch == BRANCH_CAVE)
  {
    switch (rand() % 7)
    {
    case 0:
      choice = MOB_SNAKE;
      break;

    case 1:
      choice = MOB_SPIDER;
      break;

    case 2:
      choice = MOB_BLURK;
      break;

    case 3:
      choice = MOB_IMP;
      break;

    case 4:
      choice = MOB_BIGSPIDER;
      break;

    case 5:
      choice = MOB_GIANT;
      break;

    default:
      goto regular;
    }
  }
  else
  {
  regular:
    base = (floor + 1) / 3;
    random = 2 + ((floor + 1) / 3);
    choice = MOB_FIRSTRND + base + (rand() % random);
  }

  return MIN(choice, MOB_LASTRND - 1);
}



/*
  Adds a monster on FLOOR. The monster will be slightly out of depth
  and somewhat stronger than usually found on this floor.
*/
void add_another_monster(int floor)
{
  int start_x;
  int x;
  int speed;

  // Display <-> structure adjustment. In the cellmap, floor 1 is index 0.
  floor -= 1;

  // Pick a random direction left/right
  speed = 1 * (rand() % 2 ? -1 : 1);
  
  // Pick a random starting point
  x = start_x = rand() % CELLS_W;

  // Find a "room" cell to spawn the monster in
  while (true)
  {
    // Move left or right
    x += speed;

    // Wrap around the edge
    if (x < 0)
      x = CELLS_W - 1;
    else if (x >= CELLS_W)
      x = 0;

    if (game->cell[floor][x] == CELL_ROOM)
    {
      // Place a monster in the cell, slightly out of depth
      make_monster(floor * FLOOR_H + FEET_Y,
		   x * CELL_TO_TILES,
		   random_monster(floor + ANOTHER_MONSTER_ADJUSTMENT,
				  branch_at_tile(floor, x)));
      break;
    }
    else if (game->cell[floor][x] == CELL_WATER)
    {
      water_monster(floor * FLOOR_H + FEET_Y, x * CELL_TO_TILES, floor, x);

      break;
    }

    // If we get back to the start position without finding a suitable
    // spawn location, no monster is created. This won't happen the
    // first iteration since we have already moved one step.

    if (x == start_x)
      break;
  }

  return;
}


bool eviltree_logic(mob_t * mob)
{
  int i;
  int y;
  int x;
  int dir;

  if (mob->gp > 0)
  {
    mob->gp--;
    return false;
  }

  y = mob->y;
  x = mob->x;
   
  if (x < player->x)
    dir = +1;
  else
    dir = -1;

  x = player->x + dir * 6;

  while (find_enemy(player, y, x) != NULL &&
	 x - view_x > 0 &&
	 x - view_x < BOARD_W &&
	 gtile(y, x) == TL_VOID)
  {
    x += dir * 3;
  }

  if (rand() % 4 == 0)
    return false;
  
  for (i = 0; i < 2; i++)
  {
    mob->flip = !mob->flip;
    mob->flags = GFX_ATTACK;
    draw_board(); lpause();
    mob->flags = 0;
    draw_board(); lpause();
  }
  
  make_monster(y, x, MOB_SHRUBBERY);

  draw_board();

  if ((x > player->x && player->flip == 0) ||
      (x < player->x && player->flip))
  {
    pwait("A SHRUBBERY SPROUTS BEFORE YOU!");
  }
  else
  {
    pwait("A SHRUBBERY SPROUTS BEHIND YOU!");
  }

  mob->gp = 7;

  return true;
}



bool summon_minions(mob_t * mob)
{
  int y;
  int x;
  int dir;
  mob_t * new_mob[5];
  int new_mobs = 0;
  int i;
  int t;

  if (!on_board(mob))
    return false;
  
  if (mob->gp > 0)
  {
    mob->gp--;
    return false;
  }

  if (rand() % 4 == 0)
    return false;

  y = mob->y;
  x = mob->x;
    
  if (x < player->x)
    dir = +1;
  else
    dir = -1;
  
  x = mob->x - dir * 6;
  
  do
  {
    if (find_enemy(NULL, y, x) == NULL &&
	find_enemy(NULL, y, x - 2) == NULL &&
	find_enemy(NULL, y, x + 2) == NULL &&
	gtile(y, x) == TL_VOID &&
	rand() % 5 == 0)
    {
      t = make_monster(y, x, MOB_GHOUL);
      
      if (t == -1)
	break;
      
      new_mob[new_mobs] = &game->mob[t];
      new_mobs++;
      
      if (new_mobs == 5)
	break;
    }

    x += dir * 4;
    continue;
  
  } while (x - view_x > 0 && x - view_x < BOARD_W);
  

  if (new_mobs == 0)
    return false;

  for (i = 0; i < new_mobs; i++)
  {
    new_mob[i]->flags = GFX_GHOUL_DIG1;
    new_mob[i]->flip = rand() % 2;
  }

  if (mob->type == MOB_LICH)
  {
    for (i = 0; i < 2; i++)
    {
      mob->flags = GFX_ATTACK;
      draw_board(); lpause();
      mob->flags = 0;
      draw_board(); lpause();
    }
  }
  
  for (i = 0; i < new_mobs; i++)
    new_mob[i]->flags = GFX_GHOUL_DIG2;

  draw_board(); lpause();

  for (i = 0; i < new_mobs; i++)
    new_mob[i]->flags = GFX_GHOUL_DIG3;

  draw_board(); lpause();

  for (i = 0; i < new_mobs; i++)
    new_mob[i]->flags = GFX_GHOUL_DIG4;

  draw_board(); lpause();

  for (i = 0; i < new_mobs; i++)
    new_mob[i]->flags = 0;

  draw_board();

  mob->gp = 5;

  return true;
}



void knave_logic(mob_t * mob)
{
  mob->speed = player->speed;
  
  if (player->x < mob->x)
    mob->flip = true;
  else
    mob->flip = false;
  
  if (mob->attack_phase == 0)
  {
    knave_shield(mob, true);
    move_towards_player(mob);
  }
  else if (mob->attack_phase == 1)
  {
    knave_shield(mob, true);
    mob->attack_phase++;
  }
  else if (mob->attack_phase == 2)
  {
    knave_shield(mob, false);
    mob->attack_phase++;
  }
  else if (mob->attack_phase == 3)
  {
    knave_shield(mob, true);
    mob->attack_phase = 0;
  }
  else if (mob->attack_phase == 5)
  {
    mob->attack_phase = 0;
  }
  
  return;
}



void knave_shield(mob_t * mob, bool up)
{
  if (up)
  {
    mob->shd_up = true;
    mob->flags = GFX_HUMAN_SHIELD_UP;
  }
  else
  {
    mob->shd_up = false;
    mob->flags = 0;
  }

  return;
}
