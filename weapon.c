#include "basment.h"
#include "map.h"


char * weapon_name[WPN_LAST] =
{
  [WPN_UNARMED]    = "(BUG)",
  [WPN_DAGGER]     = "DAGGER",
  [WPN_SWORD]      = "SWORD",
  [WPN_MACE]       = "MACE",
  [WPN_AXE]        = "AXE",
  [WPN_FLAIL]      = "FLAIL",
  [WPN_SPEAR]      = "SPEAR",
  [WPN_DRAIN]      = "DRAINING DAGGER",
  [WPN_DIAMOND]    = "DIAMOND MACE",
  [WPN_GLASS]      = "GLASS SWORD",
  [WPN_BOW]        = "BOW",
  [WPN_BLASTER]    = "BLASTER",
  [WPN_FREEZE_RAY] = "FREEZE RAY",
  [WPN_RUNESWORD]  = "RUNESWORD",
  [WPN_BONECLUB]   = "BONE CLUB"
};


/* Replaces players weapon with TYPE */
void give_weapon(int type)
{
  game->weapon = type;
  player->attack_frames = 1;

  switch (type)
  {
  case WPN_DAGGER:
    player->range = 4;
    player->damage = 5;
    game->wpn_dur = 30 + rand() % 30;
    break;

  case WPN_BONECLUB:
    player->range = 4;
    player->damage = 4;
    game->wpn_dur = 10 + rand() % 10;
    break;

  case WPN_DRAIN:
    player->range = 4;
    player->damage = 6;
    game->wpn_dur = 50 + rand() % 50;
    break;

  case WPN_MACE:
    player->range = 4;
    player->damage = 8;
    game->wpn_dur = 100 + rand() % 50;
    break;

  case WPN_DIAMOND:
    player->range = 4;
    player->damage = 9;
    game->wpn_dur = 500;
    break;

  case WPN_SWORD:
    player->range = 5;
    player->damage = 7;
    game->wpn_dur = 50 + rand() % 100;
    break;

  case WPN_GLASS:
    player->range = 5;
    player->damage = 50;
    game->wpn_dur = 1 + rand() % 10;
    break;

  case WPN_SPEAR:
    player->range = 6;
    player->damage = 6;
    game->wpn_dur = 60 + rand() % 60;
    break;

  case WPN_AXE:
    player->range = 5;
    player->damage = 9;
    game->wpn_dur = 80 + rand() % 20;
    break;

  case WPN_FLAIL:
    player->attack_frames = 2;
    player->range = 7;
    player->damage = 11;
    game->wpn_dur = 50 + rand() % 50;
    break;

  case WPN_BOW:
    player->range = 3;
    player->damage = 3;
    game->wpn_dur = 50 + rand() % 50;
    break;

  case WPN_BLASTER:
    player->range = 3;
    player->damage = 3;
    game->wpn_dur = 50 + rand() % 50;
    break;

  case WPN_FREEZE_RAY:
    player->range = 3;
    player->damage = 3;
    game->wpn_dur = 50 + rand() % 50;
    break;

  case WPN_RUNESWORD:
    player->range = 5;
    player->damage = 15;
    game->wpn_dur = 500 + rand() % 500;
    break;

  case WPN_UNARMED:
  default:
    player->range = 3;
    break;
  }

  return;
}



int has_ranged_weapon()
{
  return is_ranged_weapon(game->weapon);
}


int is_ranged_weapon(int wpn)
{
  if (wpn == WPN_BOW)
    return true;

  return false;
}


/*
 */
void find_random_weapon(char * msg)
{
  char line[DEFLEN];
  int new_type;
  char * none = "";

  if (msg == NULL)
    msg = none;

  if (!has_ranged_weapon() && rand() % 3 == 0)
  {
    new_type = WPN_BOW;
  }
  else
  {
    new_type = WPN_DAGGER + rand() % 4;
    
    if (game->current_floor >= 9)
      new_type += 1 + rand() % 2;
    
    if (game->current_floor >= 16)
      new_type += 1 + rand() % 3;
    
    if (new_type == game->weapon)
      new_type++;
    
    if (new_type >= WPN_LAST)
      new_type = WPN_DAGGER;
  }

  if (game->weapon)
  {
    snprintf(line, DEFLEN,
	     "%s"
	     "YOU FIND A %s\n"
	     "REPLACE YOUR %s?\n"
	     "\n"
	     "<- NO#YES ->",
	     msg,
	     weapon_name[new_type],
	     weapon_name[game->weapon]);
    
    if (psel(line) == 1)
    {
      if (is_ranged_weapon(new_type) && player->shd_type != SHD_NONE)
      {
	draw_board();
	
	snprintf(line, DEFLEN,
		 "DISCARD YOUR %s?\n"
		 "\n"
		 "<- NO#YES ->",
		 armor_name[player->shd_type]);

	if (psel(line) == 1)
	{
	  player->shd_type = SHD_NONE;
	  give_weapon(new_type);
	}
      }
      else
      {
	give_weapon(new_type);
      }
    }
  }
  else if (is_ranged_weapon(new_type) && player->shd_type != SHD_NONE)
  {
    snprintf(line, DEFLEN,
	     "%s"
	     "YOU FIND A %s\n"
	     "DISCARD YOUR %s?\n"
	     "\n"
	     "<- NO#YES ->",
	     msg,
	     weapon_name[new_type],
	     armor_name[player->shd_type]);
    
    if (psel(line) == 1)
    {
      player->shd_type = SHD_NONE;
      give_weapon(new_type);
    }
  }
  else
  {
    snprintf(line, DEFLEN,
	     "%s"
	     "YOU FIND A %s",
	     msg,
	     weapon_name[new_type]);

    pwait(line);
    give_weapon(new_type);
  }

  return;
}



/*
  Removes AMOUNT points of durability from the players weapon,
  destroys it if depleted. Returns true if the weapon broke.
*/
bool damage_weapon(int amount)
{
  char line[DEFLEN];

  game->wpn_dur -= amount;  

  if (game->wpn_dur <= 0)
  {
    snprintf(line, DEFLEN,
	     "YOUR %s BREAKS!",
	     weapon_name[game->weapon]);

    pwait(line);
    
    give_weapon(WPN_UNARMED);
    
    draw_board();

    return true;
  }
  
  return false;
}
