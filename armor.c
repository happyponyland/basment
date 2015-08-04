#include "basment.h"


char * armor_name[ARMOR_LAST] =
{
  [ARMOR_NONE] = "(BUG)", /* Same as SHD_NONE */
  [SHD_WOODEN] = "WOODEN SHIELD",
  [SHD_METAL] = "METAL SHIELD",
  [SHD_MAGIC] = "MAGIC SHIELD",
  [ARMOR_LEATHER] = "LEATHER ARMOR",
  [ARMOR_SCALE] = "SCALE ARMOR",
  [ARMOR_PLATE] = "PLATE MAIL",
  [ARMOR_MAGIC] = "MAGIC ARMOR",
  [ARMOR_DRAGON] = "DRAGON SCALE MAIL",
  [ARMOR_SPIDER] = "SPIDER (BUG)",
};


int armor_loot[ARMOR_LOOT_LEVELS] =
{
  ARMOR_LEATHER,
  SHD_WOODEN,
  SHD_WOODEN,
  ARMOR_LEATHER,
  ARMOR_SCALE,
  SHD_WOODEN,
  SHD_METAL,
  ARMOR_SCALE,
  ARMOR_PLATE,
  SHD_METAL,
  SHD_METAL,
  ARMOR_PLATE,
  ARMOR_MAGIC,
  SHD_METAL,
  SHD_MAGIC,
  ARMOR_PLATE,
  ARMOR_DRAGON,
  SHD_MAGIC,
  SHD_MAGIC,
  ARMOR_MAGIC,
  ARMOR_MAGIC,
  SHD_MAGIC,
  ARMOR_DRAGON,
  ARMOR_MAGIC,
  ARMOR_PLATE
};


void damage_armor(mob_t * mob)
{
  char line[DEFLEN];

  if (mob != player ||
      player->armor_type == ARMOR_NONE)
    return;

  if (--game->armor_dur <= 0)
  {
    snprintf(line, DEFLEN,
	     "YOUR %s HAS BEEN DESTROYED!",
	     armor_name[player->armor_type]);

    player->armor_type = 0;
    
    pwait(line);

    draw_board();
  }

  return;
}



void damage_shield(mob_t * mob)
{
  char line[DEFLEN];

  if (player->shd_type == SHD_NONE ||
      mob != player)
    return;

  if (--game->shd_dur <= 0)
  {
    snprintf(line, DEFLEN,
	     "YOUR %s HAS BEEN DESTROYED!",
	     armor_name[player->shd_type]);

    player->shd_type = 0;
    player->shd_up = 0;
    
    pwait(line);

    draw_board();
  }

  return;
}



/*
  Rolls if MOB succeeds in blocking an attack. The chance will be
  based on the shield MOD has (if any). Returns true if the attack was
  blocked, false if it hit.
*/
bool shield_block(mob_t * mob)
{
  switch (mob->shd_type)
  {
  case SHD_WOODEN:
    if (rand() % 100 < SHD_WOODEN_BLOCK)
      return true;
    else
      return false;

  case SHD_METAL:
    if (rand() % 100 < SHD_METAL_BLOCK)
      return true;
    else
      return false;

  case SHD_MAGIC:
    if (rand() % 100 < SHD_MAGIC_BLOCK)
      return true;
    else
      return false;

  case SHD_NONE:
  default:
    return false;
  }

  return false;
}



/*
  Tries to give the player a random piece of armor or shield. If the
  player already has another kind a prompt will be displayed.
*/
void find_random_armor(char * msg)
{
  char line[DEFLEN];
  int new_type;
  bool has;
  int loot;
  char * none = "";

  if (msg == NULL)
    msg = none;

  loot = rand() % MIN(game->current_floor, ARMOR_LOOT_LEVELS);

  do
  {
    /* Try to find something we don't already have */
    new_type = armor_loot[loot];

    has = false;

    if (new_type <= SHD_SHIELDS && player->shd_type == new_type)
      has = true;
    else if (player->armor_type == new_type)
      has = true;

    if (has)
    {
      loot++;

      if (loot >= ARMOR_LOOT_LEVELS)
	return;
    }
  } while (has);

  if (new_type >= ARMOR_LAST)
    new_type = 1;

  if (new_type <= SHD_SHIELDS && game->weapon == WPN_BOW)
  {
    draw_board();

    snprintf(line, DEFLEN,
	     " YOU FIND A %s\n\n"
	     "DISCARD YOUR %s?\n"
	     "\n"
	     "<- NO#YES ->",
	     armor_name[new_type],
	     weapon_name[game->weapon]);
    
    if (psel(line) == 1)
    {
      give_weapon(WPN_UNARMED);
      give_armor(new_type);
    }
  }
  else if ((new_type <= SHD_SHIELDS && player->shd_type) ||
	   (new_type > SHD_SHIELDS && player->armor_type))
  {
    int take_it = 0;

    if (new_type <= SHD_SHIELDS &&
	     player->shd_type &&
	     new_type > player->shd_type)
    {
      take_it = 1;
    }
    else if (new_type > SHD_SHIELDS &&
	     player->armor_type &&
	     new_type > player->armor_type)
    {
      take_it = 1;
    }

    if (take_it == 1)
    {
      snprintf(line, DEFLEN,
	       "%s"
	       "    YOU FIND %s%s\n\n"
	       "YOU REPLACE YOUR %s",
	       msg,
	       (new_type <= SHD_SHIELDS ? "A " : ""),
	       armor_name[new_type],
	       (new_type <= SHD_SHIELDS ?
		armor_name[player->shd_type] :
		armor_name[player->armor_type]));

      pwait(line);
    }
    else
    {
      snprintf(line, DEFLEN,
	       "%s"
	       "  YOU FIND %s%s\n"
	       "REPLACE YOUR %s?\n"
	       "\n"
	       "<- NO#YES ->",
	       msg,
	       (new_type <= SHD_SHIELDS ? "A " : ""),
	       armor_name[new_type],
	       (new_type <= SHD_SHIELDS ?
		armor_name[player->shd_type] :
		armor_name[player->armor_type]));

      if (psel(line) == 1)
	take_it = true;
    }

    if (take_it)
      give_armor(new_type);
  }
  else
  {
    // Player doesn't have anything of this type

    snprintf(line, DEFLEN,
	     "%sYOU FIND %s%s",
	     msg,
	     (new_type <= SHD_SHIELDS ? "A " : ""),
	     armor_name[new_type]);
    pwait(line);
    give_armor(new_type);
  }
  
  return;
}



/*
  Gives player TYPE armor
*/
void give_armor(int type)
{
  switch (type)
  {
  case SHD_WOODEN:
    player->shd_type = type;
    game->shd_dur = 15 + rand() % 10;
    break;

  case SHD_METAL:
    player->shd_type = type;
    game->shd_dur = 20 + rand() % 10;
    break;

  case SHD_MAGIC:
    player->shd_type = type;
    game->shd_dur = 30 + rand() % 10;
    break;

  case ARMOR_LEATHER:
    player->armor_type = type;
    game->armor_dur = 15 + rand() % 15;
    break;

  case ARMOR_SCALE:
    player->armor_type = type;
    game->armor_dur = 20 + rand() % 10;
    break;

  case ARMOR_PLATE:
    player->armor_type = type;
    game->armor_dur = 25 + rand() % 10;
    break;

  case ARMOR_MAGIC:
    player->armor_type = type;
    game->armor_dur = 30 + rand() % 20;
    break;

  case ARMOR_DRAGON:
    player->armor_type = type;
    game->armor_dur = 30 + rand() % 20;
    break;

  default:
    break;
  }

  return;
}

