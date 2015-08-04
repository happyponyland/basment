
#include "basment.h"


void shop_chef()
{
  int sel;
  char line[DEFLEN];
  int leave;

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  snprintf(line, DEFLEN,
	   "CHEF:\n"
	   "WOULD YOU LIKE SOMETHING TO EAT?\n\n"
	   "  MAGGOT PUDDING  (%d)\n"
	   "  GNOBLIN STEW    (%d)\n"
	   "  MOLD SOUP       (%d)",
	   COST_MAGGOT_PUDDING,
	   COST_GNOBLIN_STEW,
	   COST_MOLD_SOUP);
  
  sel = pchoose(line, 3, 3, leave);
  
  draw_board();
  
  if (sel >= 0)
  {
    int cost;
    
    if (sel == 0)
      cost = COST_MAGGOT_PUDDING;
    else if (sel == 1)
      cost = COST_GNOBLIN_STEW;
    else if (sel == 2)
      cost = COST_MOLD_SOUP;
    
    if (spend_gold(cost) == false)
    {
      pwait("CHEF:\nHEY! CASH UP FRONT!!");
    }
    else
    {
      // Update gold
      draw_stats();
      
      if (sel == 0)
      {
	pwait("THE MAGGOT PUDDING SITS\n"
	      "UNEASILY IN YOUR STOMACH");
	change_pl_st(+1);
	draw_stats();
	refill_hp(MAGGOT_PUDDING_HEAL);
      }
      else if (sel == 1)
      {
	pwait("THE GNOBLIN STEW IS DELICIOUS!");
	refill_hp(GNOBLIN_STEW_HEAL);
      }
      else if (sel == 2)
      {
	game->hallucination = 50 + rand() % 250;
	draw_board();
	pwait("WAIT ... THIS IS ... ???");
      }
      
    }
    
    return;
  }
  
  return;
}




void shop_blacksmith()
{
  int sel;
  char line[DEFLEN];

  int weapon;
  int weapon_cost;
  int armor;
  int armor_cost;
  int shield;
  int shield_cost;
  int final_cost;
  int leave;

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;
  
  if (game->current_floor < 6)
  {
    weapon = WPN_SWORD;
    weapon_cost = 100;
    armor = ARMOR_LEATHER;
    armor_cost = 100;
    shield = SHD_WOODEN;
    shield_cost = 100;
  }
  else if (game->current_floor < 12)
  {
    if (game->current_floor % 2 == 0)
      weapon = WPN_SWORD;
    else
      weapon = WPN_MACE;

    weapon_cost = 150;

    armor = ARMOR_SCALE;
    armor_cost = 150;
    shield = SHD_METAL;
    shield_cost = 150;
  }
  else if (game->current_floor < 18)
  {
    if (game->current_floor % 2 == 0)
      weapon = WPN_MACE;
    else
      weapon = WPN_SPEAR;

    weapon_cost = 200;

    armor = ARMOR_PLATE;
    armor_cost = 200;
    shield = SHD_METAL;
    shield_cost = 200;
  }
  else if (game->current_floor < 21)
  {
    if (game->current_floor % 2 == 0)
      weapon = WPN_FLAIL;
    else
      weapon = WPN_AXE;

    weapon_cost = 250;

    armor = ARMOR_MAGIC;
    armor_cost = 250;

    shield = SHD_MAGIC;
    shield_cost = 250;
  }
  else
  {
    if (game->current_floor % 3 == 0)
      weapon = WPN_DIAMOND;
    else if (game->current_floor % 3 == 1)
      weapon = WPN_GLASS;
    else
      weapon = WPN_DRAIN;

    weapon_cost = 300;

    armor = ARMOR_DRAGON;
    armor_cost = 300;

    shield = SHD_MAGIC;
    shield_cost = 300;
  }

  snprintf(line, DEFLEN,
	   "BLACKSMITH:\n"
	   "BUY SOMETHING WILL YA!!\n\n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  ",
	   weapon_name[weapon], weapon_cost,
	   armor_name[armor], shield_cost,
	   armor_name[shield], shield_cost);
  
  sel = pchoose(line, 3, 3, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  if ((sel == 0 && game->weapon == weapon) ||
      (sel == 1 && player->armor_type == armor) ||
      (sel == 2 && player->shd_type == shield))
  {
    pwait("YOU ALREADY HAVE THAT!");
    draw_board();
    return;
  }

  if (sel == 0)
    final_cost = weapon_cost;
  else if (sel == 1)
    final_cost = armor_cost;
  else if (sel == 2)
    final_cost = shield_cost;
  
  if (spend_gold(final_cost) == false)
  {
    pwait("BLACKSMITH:\n"
	  "HEY! CASH UP FRONT!!");
    return;
  }

  if (sel == 0)
  {
    give_weapon(weapon);
    snprintf(line, DEFLEN,
	     "YOU NOW HAVE A %s",
	     weapon_name[weapon]);
  }
  else if (sel == 1)
  {
    give_armor(armor);
    snprintf(line, DEFLEN,
	     "YOU NOW HAVE %s",
	     armor_name[armor]);
  }
  else if (sel == 2)
  {
    if (game->weapon == WPN_BOW)
    {
      snprintf(line, DEFLEN,
	       "DISCARD YOUR %s?\n"
	       "\n"
	       "<- NO#YES ->",
	       weapon_name[game->weapon]);

      if (psel(line) != 1)
	return;

      give_weapon(WPN_UNARMED);
    }

    give_armor(shield);
    snprintf(line, DEFLEN,
	     "YOU NOW HAVE A %s",
	     armor_name[shield]);
  }
  
  // Update gold
  draw_stats();
  
  draw_board();
  pwait(line);
  
  return;
}




void shop_train()
{
  int sel;
  char line[DEFLEN];
  int leave;
  int cost;
  
  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  cost = TRAINING_COST;

  snprintf(line, DEFLEN,
	   "TRAINER:\n"
	   "EACH SESSION IS %d GOLD\n"
	   "WHAT WOULD YOU LIKE TO TRAIN?\n\n"
	   "  STRENGTH  \n"
	   "  SPEED     \n"
	   "  STRIDE    ",
	   cost);
  
  sel = pchoose(line, 4, 3, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  if (spend_gold(cost) == false)
  {
    pwait("TRAINER:\nHEY! CASH UP FRONT!!");
    return;
  }

  // Update gold
  draw_stats();
  
  if (sel == 0)
  {
    pwait("YOU FEEL STRONGER!");
    change_pl_st(+2);
  }
  else if (sel == 1)
  {
    pwait("YOU FEEL QUICKER!");
    change_pl_sp(+2);
  }
  else if (sel == 2)
  {
    player->steps += 2;
    
    if (rand() % 10 == 0)
      pwait("YOU FEEL STRIDENT ... NO, WAIT");
    else
      pwait("YOU FEEL LIKE YOU CAN GO FAR!");
  }

  draw_stats();
  draw_board();

  return;
}



void shop_map()
{
  int sel;
  char line[DEFLEN];
  int leave;
  int cost;
  
  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  cost = MAP_COST;

  snprintf(line, DEFLEN,
	   "CARTOGRAPHER:\n"
	   "WELCOME TO YE OLDE MAPPE SHOPPE\n"
	   "WOULD YOU LIKE TO BUY A MAP\n\n"
	   "  YES (%d GOLD)\n"
	   "  NO THANKS",
	   cost);
  
  sel = pchoose(line, 4, 2, leave);
  
  draw_board();
  
  if (sel != 0)
    return;

  if (game->has_map)
  {
    pwait("CARTOGRAPHER:\nYOU ALREADY HAVE A MAP.\nIT WILL DO JUST FINE.");
    return;
  }
    
  if (spend_gold(cost) == false)
  {
    pwait("CARTOGRAPHER:\nYOU CANNOT AFFORD MY PREMIUM MAPS");
  }
  else
  {
    // Update gold
    draw_stats();

    game->has_map = true;
    fill_automap(1);
    pwait("CARTOGRAPHER:\nPRESS M TO VIEW YOUR MAP");
  }
  
  draw_board();
  
  return;
}

