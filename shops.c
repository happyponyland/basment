
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




void shop_armor()
{
  int sel;
  char line[DEFLEN];
  char * seller_name;

  int cost;
  int leave;
  int armor;

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

//  snprintf(shop_name, DEFLEN, "ROLF");

  seller_name = random_seller_name();
  
  snprintf(line, DEFLEN,
	   "WELCOME TO %s'S PREMIUM ARMOR\n"
	   "BUY SOMETHING WILL YA!!\n\n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  ",
	   seller_name,
	   armor_name[ARMOR_SCALE], 100,
	   armor_name[ARMOR_PLATE], 150,
	   armor_name[ARMOR_MAGIC], 200,
	   armor_name[SHD_METAL],   50);
  
  sel = pchoose(line, 3, 4, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  if (sel == 0)
  {
    armor = ARMOR_SCALE;
    cost = 100;
  }
  else if (sel == 1)
  {
    armor = ARMOR_PLATE;
    cost = 150;
  }
  else if (sel == 2)
  {
    armor = ARMOR_MAGIC;
    cost = 200;
  }
  else if (sel == 3) cost = 200;
  
  if ((sel == 3 && player->shd_type == SHD_METAL) ||
      (player->armor_type == armor))
  {
    pwait("YOU ALREADY HAVE THAT!");
    draw_board();
    return;
  }

  if (spend_gold(cost) == false)
  {
    snprintf(line, DEFLEN, "%s:\nSORRY, I DON'T GIVE CREDIT!!!", seller_name);
    pwait(line);
    return;
  }

  if (sel == 3)
  {
    if (has_ranged_weapon())
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

    give_armor(SHD_METAL);
    
    snprintf(line, DEFLEN,
	     "YOU NOW HAVE A %s",
	     armor_name[SHD_METAL]);
  }
  else
  {
    give_armor(armor);
    snprintf(line, DEFLEN, "YOU NOW HAVE %s", armor_name[armor]);
  }
  
  // Update gold
  draw_stats();
  
  draw_board();
  pwait(line);
  
  return;
}




char * seller_names[] =
{
  "ROLFE",
  "JACQUELINE",
  "HAGBARD",
  "PATRICIA",
  "TEEMU",
  "KNUT-OYVIND",
  "PER-EINAR",
  "VEGAN_SXE_1994"
};

#define SELLER_NAMES 8




char * random_seller_name()
{
  int y;
  int x;
  int i;
  int sy;
  int sx;

  i = 0;
  
  sy = player->y / FLOOR_H;
  sx = player->x / CELLS_W;


  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      if (y == sy && x == sx)
	goto finish_it;
      
      if (get_cell(y, x) == CELL_NPC_L ||
	  get_cell(y, x) == CELL_NPC_R)
      {
	i = (i + 1) % SELLER_NAMES;
      }
    }
  }
  
finish_it:
  return seller_names[i];
}




void shop_weapons(int selection)
{
  int sel;
  char line[DEFLEN];
//  char seller_name[DEFLEN];
  char * seller_name;
  char shop_name[DEFLEN];

  int leave;
  int sel_wpn;
  int final_cost;

  int wpn_type[6];
  int wpn_cost[6];

  //snprintf(seller_name, DEFLEN, "ROLF");

  seller_name = random_seller_name();
  
  if (selection == 0)
  {
    snprintf(shop_name, DEFLEN, "%s", "INSTRUMENTS OF DEATH");

    wpn_type[0] = WPN_SWORD;
    wpn_cost[0] = 100;
    wpn_type[1] = WPN_SPEAR;
    wpn_cost[1] = 150;
    wpn_type[2] = WPN_FLAIL;
    wpn_cost[2] = 250;
    wpn_type[3] = WPN_GLASS;
    wpn_cost[3] = 300;
  }
  else if (selection == 1)
  {
    snprintf(shop_name, DEFLEN, "%s", "MISSILE*MART");

    wpn_type[0] = WPN_BOW;
    wpn_cost[0] = 100;
    wpn_type[1] = WPN_3XBOW;
    wpn_cost[1] = 200;
    wpn_type[2] = WPN_BLASTER;
    wpn_cost[2] = 300;
    wpn_type[3] = WPN_FREEZE_RAY;
    wpn_cost[3] = 500;
  }

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  snprintf(line, DEFLEN,
	   "WELCOME TO %s'S %s\n"
	   "BUY SOMETHING WILL YA!!\n\n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  ",
	   seller_name, shop_name,
	   weapon_name[wpn_type[0]], wpn_cost[0],
	   weapon_name[wpn_type[1]], wpn_cost[1],
	   weapon_name[wpn_type[2]], wpn_cost[2],
	   weapon_name[wpn_type[3]], wpn_cost[3]);
  
  sel = pchoose(line, 3, 4, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  sel_wpn    = wpn_type[sel];
  final_cost = wpn_cost[sel];
  
  if (game->weapon == sel_wpn)
  {
    pwait("YOU ALREADY HAVE THAT!");
    draw_board();
    return;
  }

  if (sel_wpn == WPN_FREEZE_RAY)
  {
    snprintf(line, DEFLEN, "%s:\nSORRY, FREEZE RAY ISN'T IMPLEMENTED YET!!!", seller_name);
    pwait(line);
    return;
  }
  
  if (spend_gold(final_cost) == false)
  {
    snprintf(line, DEFLEN, "%s:\nSORRY, I DON'T GIVE CREDIT!!!", seller_name);
    pwait(line);
    return;
  }

  if (is_ranged_weapon(sel_wpn) && player->shd_type != SHD_NONE)
  {
    //draw_board_norefresh();
    
    snprintf(line, DEFLEN,
	     "DISCARD YOUR %s?\n"
	     "\n"
	     "<- NO#YES ->",
	     armor_name[player->shd_type]);

    if (psel(line) != 1)
      return;

    player->shd_type = SHD_NONE;
  }

  give_weapon(sel_wpn);
  
  // Update gold
  draw_stats();
  
  draw_board();

  snprintf(line, DEFLEN, "YOU NOW HAVE A %s", weapon_name[sel_wpn]);
  pwait(line);
  
  return;
}




/*void shop_ranged()
{
  int sel;
  char line[DEFLEN];
  char shop_name[DEFLEN];

  int cost;
  int leave;
  int wpn;

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  snprintf(shop_name, DEFLEN, "ROLF");
  
  snprintf(line, DEFLEN,
	   "WELCOME TO %s'S MISSILE*MART\n"
	   "BUY SOMETHING WILL YA!!\n\n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  \n"
	   "  %-16s(%d)  ",
	   shop_name,
	   weapon_name[WPN_BOW], 100,
	   weapon_name[WPN_BLASTER], 200,
	   weapon_name[WPN_FREEZE_RAY], 400);
  
  sel = pchoose(line, 3, 3, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  if (sel == 0)
  {
    wpn = WPN_BOW;
    cost = 100;
  }
  else if (sel == 1)
  {
    wpn = WPN_BLASTER;
    cost = 200;
  }
  else if (sel == 2)
  {
    wpn = WPN_FREEZE_RAY;
    cost = 400;
  }
  
  if (game->weapon == wpn)
  {
    pwait("YOU ALREADY HAVE THAT!");
    draw_board();
    return;
  }

  if (spend_gold(cost) == false)
  {
    snprintf(line, DEFLEN, "%s:\nSORRY, I DON'T GIVE CREDIT!!!", shop_name);
    pwait(line);
    return;
  }

  if (player->shd_type != SHD_NONE)
  {
//    draw_board_norefresh();
    
    snprintf(line, DEFLEN,
	     "DISCARD YOUR %s?\n"
	     "\n"
	     "<- NO#YES ->",
	     armor_name[player->shd_type]);

    if (psel(line) != 1)
      return;

    player->shd_type = SHD_NONE;
  }
  
  give_weapon(wpn);
  
  // Update gold
  draw_stats();
  
  draw_board();

  snprintf(line, DEFLEN, "YOU NOW HAVE A %s", weapon_name[wpn]);
  pwait(line);
  
  return;
  }*/



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




void shop_sushi()
{
  int sel;
  char line[DEFLEN];
  int leave;

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;

  snprintf(line, DEFLEN,
	   "ITAMAE:\n"
	   "HELLO WOULD YOU LIKE SOMETHING TO EAT\n\n"
	   "  11-PIECE NIGIRI (SAKE, AJI, EBI, TOFU)  (%d)  \n"
	   "  13-PIECE NIGIRI (OTORO, HAMACHI, TAKO)  (%d)  \n"
	   "  SPICY URAMAKI (TOPPED W. SESAME SEEDS)  (%d)  \n"
	   "  WAKAME & TOFU SALAD (VEGETARIAN)        (%d)  \n"
	   "  SMOKED EEL SPECIAL                      (%d)  \n"
	   "  BENTO (ONIGIRI, PICKLES, SASHIMI)       (%d)  ",
	   COST_11PCS, COST_13PCS, COST_ROLL, COST_TOFU, COST_EEL, COST_BENTO);
  
  sel = pchoose(line, 3, 6, leave);
  
  draw_board();
  
  if (sel >= 0)
  {
    int cost;
    
    if      (sel == 0) cost = COST_11PCS;
    else if (sel == 1) cost = COST_13PCS;
    else if (sel == 2) cost = COST_ROLL;
    else if (sel == 3) cost = COST_TOFU;
    else if (sel == 4) cost = COST_EEL;
    else if (sel == 5) cost = COST_BENTO;
    
    if (spend_gold(cost) == false)
    {
      pwait("ITAMAE:\nI'M SORRY YOU CANNOT AFFORD IT");
    }
    else
    {
      // Update gold
      draw_stats();

      if (sel == 0)
      {
	pwait("THE 11-PIECE NIGIRI WAS DELICIOUS");
	change_pl_st(+1);
	draw_stats();
	refill_hp(NIGIRI_HEAL);
      }
      else if (sel == 1)
      {
	pwait("THE 13-PIECE NIGIRI WAS DELICIOUS");
	refill_hp(NIGIRI_HEAL);
      }
      else if (sel == 2)
      {
	pwait("YOU ENJOY A SPICY URAMAKI");

      }
      else if (sel == 3)
      {
	pwait("THIS WAKAME & TOFU SALAD\n"
	      "MUST BE REALLY HEALTHY!!!");
	change_pl_sp(+1);
      }
      else if (sel == 4)
      {
	pwait("THE SMOKED EEL WAS INCREDIBLE!!!\n"
	      "SERIOUSLY IT WAS LIKE THE BEST EVER");
	change_pl_st(+2);
      }
      else if (sel == 5)
      {
	pwait("THE BENTO WAS A-EXCELLENTO");
	refill_hp(BENTO_HEAL);
      }
    }

    // Refresh attributes
    draw_stats();
    
    return;
  }
  
  return;
}



void shop_scuba()
{
  int leave;
  int sel;
  char line[DEFLEN];

  if (gtile(player->y - 1, player->x - 3) == TL_DESK)
    leave = POPUP_LEAVE_LEFT;
  else
    leave = POPUP_LEAVE_RIGHT;
  
  snprintf(line, DEFLEN,
	   "HELLO WOULD YOU LIKE TO BUY\n"
	   "SOME FANTASTIC SCUBA GEAR???\n\n"
	   "  YES (%d GOLD)  \n"
	   "  NO",
	   SCUBA_COST);
  
  sel = pchoose(line, 3, 2, leave);
  
  draw_board();
  
  if (sel < 0)
    return;

  if (sel == 0)
  {
    if (has_eq(EQ_SCUBA))
    {
      pwait("YOU ALREADY HAVE SCUBA GEAR");
      return;
    }
    else if (hell_floor(game->current_floor))
    {
      pwait("WHY WOULD YOU NEED SCUBA GEAR IN HELL???");
      return;
    }
  }
  else
  {
    pwait("WELL WHAT ARE YOU HERE FOR THEN???");
    return;
  }

  if (spend_gold(SCUBA_COST) == false)
  {
    pwait("YOU CANNOT AFFORD IT! THIS IS MOST UNFORTUNATE\n"
	  "I HOPE YOU DO NOT DROWN. PLEASE COME BACK LATER");
    return;
  }

  pwait("EXCELLENT! YOU NOW HAVE SCUBA GEAR");
  give_eq(EQ_SCUBA);
  draw_stats();
  
//  draw_board();
  
  return;
}




