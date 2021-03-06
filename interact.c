#include "basment.h"



/*
  Returns if TILE is a point of interest that can be interacted with
*/
int interesting(int tile)
{
  switch (tile)
  {
  case TL_P_CHEST:
  case TL_P_CORPSE:
  case TL_P_SKELETON:
  case TL_P_ALTAR:
  case TL_P_FOUNTAIN:
  case TL_P_BLOOD_FOUNTAIN:
  case TL_P_IDOL:
  case TL_P_NPC1:
  case TL_P_NPC3:
  case TL_P_NPC4:
  case TL_P_NPC_ARMOR:
  case TL_P_NPC_WEAPONS:
  case TL_P_NPC_RANGED:
  case TL_P_NPC_CLOSED:
  case TL_P_NPC_BAR:
  case TL_P_NPC_SCUBA:
  case TL_P_NPC_SUSHI:
  case TL_P_CAMP:
  case TL_P_COFFIN:
  case TL_P_PORTAL:
  case TL_P_BOOKSHELF:
  case TL_P_ORB:
  case TL_P_SWSTONE:
  case TL_P_TABLET:
  case TL_P_UWCHEST:
  case TL_P_MUSHROOMS:
  case TL_P_DISCO:
    return true;

  default:
    return false;
  }
}


/*
  Displays a message below the viewport how to access the point of
  interest TILE
*/
void feet_instruction(int tile)
{
  switch (tile)
  {
  case TL_P_CHEST:
  case TL_P_UWCHEST:
    setlowmsg("PRESS <UP> TO LOOT CHEST");
    break;

  case TL_P_SKELETON:
    setlowmsg("PRESS <UP> TO LOOT SKELETON");
    break;

  case TL_P_CORPSE:
    setlowmsg("PRESS <UP> TO LOOT CORPSE");
    break;

  case TL_P_ALTAR:
    setlowmsg("PRESS <UP> TO APPROACH ALTAR");
    break;

  case TL_P_IDOL:
    setlowmsg("PRESS <UP> TO APPROACH IDOL");
    break;

  case TL_P_FOUNTAIN:
    setlowmsg("PRESS <UP> TO DRINK FROM FOUNTAIN");
    break;

  case TL_P_BLOOD_FOUNTAIN:
    setlowmsg("PRESS <UP> TO DRINK FROM BLOOD FOUNTAIN");
    break;

  case TL_P_COFFIN:
    setlowmsg("PRESS <UP> TO LOOT COFFIN");
    break;

  case TL_P_PORTAL:
    setlowmsg("PRESS <UP> TO ENTER PORTAL");
    break;

  case TL_P_BOOKSHELF:
    setlowmsg("PRESS <UP> TO SEARCH BOOKSHELF");
    break;

  case TL_P_ORB:
    setlowmsg("PRESS <UP> TO GAZE INTO ORB");
    break;

  case TL_P_TABLET:
    setlowmsg("PRESS <UP> TO STUDY TABLET");
    break;

  case TL_P_CAMP:
    setlowmsg("PRESS <UP> TO REST");
    break;

  case TL_P_DISCO:
    setlowmsg("PRESS <UP> TO DANCE");
    break;

  case TL_P_SWSTONE:
    setlowmsg("PRESS <UP> TO DRAW SWORD");
    break;

  case TL_P_MUSHROOMS:
    setlowmsg("PRESS <UP> TO SAMPLE MUSHROOMS");
    break;

  case TL_P_NPC1:
  case TL_P_NPC3:
  case TL_P_NPC4:
  case TL_P_NPC_ARMOR:
  case TL_P_NPC_WEAPONS:
  case TL_P_NPC_RANGED:
  case TL_P_NPC_CLOSED:
  case TL_P_NPC_SCUBA:
    setlowmsg("PRESS <UP> TO TALK TO SHOPKEEP");
    break;

  case TL_P_NPC_BAR:
    setlowmsg("PRESS <UP> TO TALK TO BARTENDER");
    break;

  case TL_P_NPC_SUSHI:
    setlowmsg("PRESS <UP> TO TALK TO ITAMAE");
    break;
  }

  // Only redraw if there is something to display
  if (lowmsg[0] != '\0')
    draw_lowmsg();

  return;
}


/*
  Interacts with the tile at players feet. This will usually change
  the tile to an identical-looking but functionally inert tile.
*/
int interact()
{
  int tile;
  char line[DEFLEN];

  tile = gtile(player->y, player->x);

  if (tile == TL_P_CHEST || tile == TL_P_UWCHEST)
  {
    loot_chest(player->y, player->x);
  }
  else if (tile == TL_P_NPC1)
  {
    shop_chef();
  }
  else if (tile == TL_P_NPC3)
  {
    shop_train();
  }
  else if (tile == TL_P_NPC4)
  {
    shop_map();
  }
  else if (tile == TL_P_NPC_ARMOR)
  {
    shop_armor();
  }
  else if (tile == TL_P_NPC_RANGED)
  {
    shop_weapons(1);
  }
  else if (tile == TL_P_NPC_WEAPONS)
  {
    shop_weapons(0);
  }
  else if (tile == TL_P_NPC_CLOSED)
  {
    pwait("SORRY WE ARE CLOSED FOR RENOVATION");
  }
  else if (tile == TL_P_NPC_SCUBA)
  {
    shop_scuba();
  }
  else if (tile == TL_P_NPC_BAR)
  {
    ye_olde_bar();
  }
  else if (tile == TL_P_NPC_SUSHI)
  {
    shop_sushi();
  }
  else if (tile == TL_P_COFFIN)
  {
    stile(player->y, player->x, TL_COFFIN_HL);
    stile(player->y - 1, player->x, TL_VOID);
    stile(player->y - 1, player->x - 1, TL_VOID);
    stile(player->y - 1, player->x + 1, TL_VOID);
    stile(player->y - 2, player->x, TL_VOID);

    if (player->flip)
    {
      stile(player->y, player->x + 4, TL_COFFIN_LID_R);
      stile(player->y - 1, player->x + 3, TL_COFFIN_LID_R);
      stile(player->y - 2, player->x + 2, TL_COFFIN_LID_R);
    }
    else
    {
      stile(player->y, player->x - 4, TL_COFFIN_LID_L);
      stile(player->y - 1, player->x - 3, TL_COFFIN_LID_L);
      stile(player->y - 2, player->x - 2, TL_COFFIN_LID_L);
    }

    strcpy(line, "YOU OPEN THE COFFIN\n\n");

    if (rand() % 5 == 0)
    {
      strcat(line, "A GHOUL ESCAPES!");

      if (rand() % 2 == 0)
	make_monster(player->y, player->x - 5, MOB_GHOUL);
      else
	make_monster(player->y, player->x + 5, MOB_GHOUL);

      draw_board();

      pwait(line);
    }
    else if (rand() % 5 == 0)
    {
      draw_board();
      find_random_armor(line);
    }
    else
    {
      draw_board_norefresh();
      give_item(line, 10 + rand() % COFFIN_GOLD, LOOT_NORMAL);
    }
  }
  else if (tile == TL_P_FOUNTAIN || tile == TL_P_BLOOD_FOUNTAIN)
  {
    fountain();
  }
  else if (tile == TL_P_SWSTONE)
  {
    sword_in_stone();
  }
  else if (tile == TL_P_ORB)
  {
    gaze_orb();
  }
  else if (tile == TL_P_TABLET)
  {
    stone_tablet();
  }
  else if (tile == TL_P_HELL)
  {
    stile(player->y, player->x, TL_VOID);
    pwait("YOU ARE IN HELL");
    draw_board();
  }
  else if (tile == TL_P_PORTAL)
  {
    portal_travel();
  }
  else if (tile == TL_P_IDOL)
  {
    idol();
  }
  else if (tile == TL_P_MUSHROOMS)
  {
    mushrooms();
  }
  else if (tile == TL_P_BOOKSHELF)
  {
    bookshelf();
  }
  else if (tile == TL_P_CAMP)
  {
    if (anything_near())
    {
      pwait("YOU CANNOT REST NOW!\nENEMIES ARE NEAR");
      return false;
    }

    camp();
  }
  else if (tile == TL_P_DISCO)
  {
    if (anything_near())
    {
      pwait("YOU CANNOT DANCE WHILE\nSOMEONE IS WATCHING");
      return false;
    }

    disco();
  }
  else if (tile == TL_P_ALTAR)
  {
    altar();
  }
  else if (tile == TL_P_CORPSE || tile == TL_P_SKELETON)
  {
    if (tile == TL_P_CORPSE)
    {
      stile(player->y, player->x, TL_VOID);
      strcpy(line, "YOU FIND A DECAYING CORPSE\n\n");
    }
    else
    {
      stile(player->y, player->x, TL_VOID);
      strcpy(line, "YOU FIND A LONG-DEAD SKELETON\n\n");
    }

    switch(rand() % 10)
    {
    case 0:
    case 1:
    case 2:
      find_random_armor(line);
      break;

    case 3:
    case 4:
    case 5:
      find_random_weapon(line);
      break;

    default:
      if (tile == TL_P_SKELETON)
	give_item(line, 5 + rand() % 25, LOOT_BONES);
      else
	give_item(line, 5 + rand() % 25, LOOT_NORMAL);
      break;
    }

    //pwait(line);

    return true;
  }

  return true;
}



void loot_chest(int ty, int tx)
{
  char line[DEFLEN];
  int tile;
  int gold_amount;

  tile = gtile(ty, tx);

  if (!game->skill_lockpick && game->weapon == WPN_UNARMED)
  {
    pwait("YOU HAVE NOTHING TO\n"
	  "OPEN THE CHEST WITH");
    return;
  }
  
  if (game->skill_lockpick)
  {
    strcpy(line, "YOU PICK THE LOCK\n\n");
  }
  else if (game->weapon == WPN_AXE      ||
	   game->weapon == WPN_MACE     ||
	   game->weapon == WPN_DIAMOND  ||
	   game->weapon == WPN_FLAIL    ||
    	   game->weapon == WPN_BONECLUB )
  {
    strcpy(line, "YOU SMASH THE CHEST OPEN\n\n");
  }
  else
    strcpy(line, "YOU PRY THE CHEST OPEN\n\n");
  
  /*
    Weapon has a random chance of breaking, but even if it does we
    still get the loot. Don't damage weapon if we're capable of
    lockpicking.
  */
  if (!game->skill_lockpick)
    damage_weapon(rand() % 10);
  
  if (tile == TL_P_UWCHEST)
  {
    gold_amount = 10 + rand() % UWCHEST_GOLD;

    stile(player->y, player->x, TL_UWWOOD);
    stile(player->y - 1, player->x - 2, TL_UW_UL);
    stile(player->y - 1, player->x - 1, TL_UW_HL);
    stile(player->y - 1, player->x, TL_UW_HL);
    stile(player->y - 1, player->x + 1, TL_UW_HL);
    stile(player->y - 1, player->x + 2, TL_UW_UR);
  }
  else
  {
    gold_amount = 10 + rand() % CHEST_GOLD;
	
    stile(player->y, player->x, TL_WOOD);
    stile(player->y - 1, player->x - 2, TL_BR_UL);
    stile(player->y - 1, player->x - 1, TL_BR_HL);
    stile(player->y - 1, player->x, TL_BR_HL);
    stile(player->y - 1, player->x + 1, TL_BR_HL);
    stile(player->y - 1, player->x + 2, TL_BR_UR);
  }
  
  draw_board();

  give_item(line, gold_amount, LOOT_NORMAL);
  
  return;
}



void portal_travel()
{
  int start_y;
  int start_x;
  int y;
  int x;
//  int target_x;
//  int target_y;

  start_y = player->y / FLOOR_H;
  start_x = player->x / CELL_TO_TILES;

  player->y--;
  draw_board();
  lpause();

  player->y--;
  draw_board();
  lpause();

  for (y = 0; y < MAX_FLOORS; y++)
  {
    for (x = 0; x < CELLS_W; x++)
    {
      if (get_cell(y, x) == CELL_PORTAL && x != start_x && y != start_y)
      {
	player->x = x * CELL_TO_TILES + 4;
	player->y = y * FLOOR_H + FLOOR_Y - 3;
	view_y = y * FLOOR_H;
	recenter(false);
      }
    }
  }

  draw_board();
  lpause();

  player->y++;
  draw_board();
  lpause();

  player->y++;
  draw_board();

  return;
}



/**
   Give the player a random item suitable for the current floor or
   @gold if nothing useful was available.
*/
void give_item(char * msg, int gold, int type)
{
  char line[DEFLEN];

  if (game->weapon == WPN_UNARMED && rand() % 3 == 0)
  {
    give_weapon(WPN_BONECLUB);
    snprintf(line, DEFLEN, "%sYOU FIND A BONE CLUB", msg);
    goto print_msg;
  }

  switch (rand() % 20)
  {
  case 0:
    if (!has_eq(EQ_TORCH))
    {
      give_eq(EQ_TORCH);
      draw_stats();
      snprintf(line, DEFLEN, "%sYOU FIND A TORCH", msg);
      goto print_msg;
    }
    break;

  case 1:
    if (!has_eq(EQ_SHADES))
    {
      give_eq(EQ_SHADES);
      draw_stats();
      snprintf(line, DEFLEN, "%sYOU FIND SOME SHADES\n\nYOU LOOK REALLY COOL NOW", msg);
      goto print_msg;
    }
    break;

  default:
    break;
  }

  game->player_gold += gold;
  game->total_gold_earned += gold;
  draw_stats();
  snprintf(line, DEFLEN, "%sYOU FIND %d GOLD", msg, gold);

print_msg:
  pwait(line);

  return;
}



void altar()
{
  char line[DEFLEN];
  int temp;
  char * p;

  stile(player->y, player->x, TL_GR_HL);

  /*
    Praying increases piety (hidden from the player); when the
    player has enough it will cause a beneficial effect. If the
    player chooses to loot the altar they will lose all piety.
  */

  if (psel("YOU APPROACH THE ALTAR\n"
	   "\n"
	   "<- LOOT IT#PRAY ->") == 0)
  {
    stile(player->y - 2, player->x - 3, TL_VOID);
    stile(player->y - 2, player->x + 3, TL_VOID);

    stile(player->y - 3, player->x, TL_VOID);
    stile(player->y - 2, player->x - 1, TL_VOID);
    stile(player->y - 2, player->x, TL_VOID);
    stile(player->y - 2, player->x + 1, TL_VOID);

    draw_board();
    give_gold("YOU LOOT THE ALTAR\n\n", 1 + rand() % ALTAR_LOOT_GOLD);

    game->piety -= ALTAR_LOOT_PENALTY + (rand() % ALTAR_LOOT_PENALTY);

    if (game->piety < -3000 && rand() % 3 == 0)
    {
      draw_board();
      pwait("A MIGHTY VOICE BOOMS OUT:\n"
	    "\"THOU HATH DEFILED MY ALTAR\n"
	    " TOO MANY TIMES, MORTAL!\"");
      
      draw_board();

      if (rand() % 2 == 0)
      {
	pwait("YOU ARE STRUCK BY LIGHTNING!");
	draw_board();
      
	lightning(player->y - view_y, player->x - view_x);

	player->hp -= 25 + rand() % 46;

	if (player->hp <= 0)
	  game_over("YOU DIED FOR YOUR SINS", false);

	draw_bars();
      }
      else
      {
	pwait("YOU FEEL WEAK!");
	player->strength = MAX(1, player->strength - 1 - rand() % 3);
	player->speed = MAX(1, player->speed - 1 - rand() % 3);
      }
    }
    else if (game->piety < -2000 && rand() % 3 == 0)
    {
      tremor(5);
      draw_board();
      pwait("YOU HEAR A RUMBLE IN THE DISTANCE");
    }
    else if (game->piety < -1000 && rand() % 3 == 0)
    {
      draw_board();
      pwait("YOU GET AN UNEASY FEELING");
    }
  }
  else
  {
    stile(player->y - 3, player->x - 1, TL_YDOT);
    stile(player->y - 3, player->x, TL_YDOT);
    stile(player->y - 3, player->x + 1, TL_YDOT);

    // Update board with lit candles
    draw_board();

    strcpy(line, "YOU PRAY AT THE ALTAR");

    if (game->piety < 0)
      game->piety += 500;

    game->piety += ALTAR_PRAYER_PIETY + (rand() % ALTAR_PRAYER_PIETY);

    if (game->piety < 0)
    {
      strcat(line,
	     "\n\nYOU ARE LEFT WITH A DISAPPROVING\n"
	     "SENSATION OF EMPTINESS");

      pwait(line);
    }
    else if (rand() % MAX(1, game->piety) > ALTAR_HEAL_PIETY)
    {
      game->piety -= ALTAR_HEAL_PIETY;

      strcat(line,
	     "\n\n YOU ARE EMBRACED BY\n"
	     "   A WARM FEELING!  ");
      pwait(line);
      draw_board();
	
      refill_hp(ALTAR_EMBRACE_HEAL);
    }
    else if (rand() % MAX(1, game->piety) > ALTAR_WISDOM_PIETY)
    {
      game->piety -= ALTAR_WISDOM_PIETY;

      temp = (1 + rand() % game->current_floor) * 100;
      temp += MAX(0, game->current_floor - 7) * 200;

      // Find end of string
      for (p = line; *p != '\0'; p++) { }

      sprintf(p,
	      "\n\nYOU HAVE BEEN ENLIGHTENED!\n\n"
	      "YOU GET %d EXP",
	      temp);
      pwait(line);

      draw_board();

      give_exp(temp);
    }
    else
    {
      pwait(line);
    }
  }

  return;
}



void fountain()
{
  char line[DEFLEN];
  char liquid[DEFLEN];
  char * insert;
  int temp;
  int blood;
  int rlen;

  blood = (gtile(player->y, player->x) == TL_P_BLOOD_FOUNTAIN);

  snprintf(liquid, DEFLEN, "%s", blood ? "BLOOD" : "WATER");

  stile(player->y, player->x, TL_FOUNT_BASE);
  stile(player->y - 1, player->x, TL_VOID);
  stile(player->y - 2, player->x, TL_VOID);
  stile(player->y - 2, player->x - 1, TL_VOID);
  stile(player->y - 2, player->x + 1, TL_VOID);

  snprintf(line, DEFLEN, "YOU DRINK FROM THE %sFOUNTAIN\n\n", (blood ? "BLOOD " : ""));

  rlen = strlen(line);
  insert = &line[rlen];
  rlen = DEFLEN - rlen;

  draw_board();

  switch (rand() % 10)
  {
  case 0:
    snprintf(insert, rlen, "THE %s TASTES FOUL!!", liquid);

    pwait(line);

    player->flags = GFX_HURT;
    draw_board(); lpause();
    player->flags = 0;

    player->hp -= 1 + rand() % 10;
    draw_bars();
     
    if (player->hp <= 0)
    {
      draw_board();

      game_over("YOU DIED FROM A\n"
		"POISONED FOUNTAIN", false);
    }
    break;

  case 1:
    snprintf(insert, rlen, "THE %s TASTES BITTER!\n\nYOU FEEL SLOWER!", liquid);

    pwait(line);

    change_pl_sp(-1);

    draw_stats();
    break;

  case 2:
  case 3:
    temp = 100 + (rand() % 5) * 100;
    temp += MAX(0, game->current_floor - 7) * 100;

    snprintf(insert, rlen,
	     "THIS IS A FOUNTAIN OF WISDOM!\n\n"
	     "YOU GET %d EXP",
	     temp);

    pwait(line);

    draw_board();

    give_exp(temp);
    break;

  case 4:
  case 5:
    snprintf(insert, rlen, "THE %s IS INVIGORATING!\n\nYOU FEEL STRONGER!", liquid);
    pwait(line);

    change_pl_st(+1);

    draw_stats();
    break;

  default:
    snprintf(insert, rlen, "THE %s IS REFRESHING!", liquid);
    pwait(line);

    refill_hp(FOUNTAIN_HEAL);
    break;
  }

  return;
}



void idol()
{
  stile(player->y, player->x, TL_IDOL_BASE);
   
  if (psel("YOU FIND THE BLOOD-STAINED IDOL\n"
	   "OF A DARK AND NAMELESS GOD\n"
	   "\n"
	   "<- SMASH IT#SACRIFICE ->") == 0)
  {
    decorate(player->y, player->x, DEC_BROKEN_IDOL);
    game->piety += IDOL_SMASH_PIETY + rand() % IDOL_SMASH_PIETY;
    game->sacrifice -= IDOL_SACRIFICE_PEN;
  }
  else
  {
    stile(player->y - 3, player->x, TL_IDOL_HEAD_LIT);
    
    player->hp--;
    draw_bars();

    draw_board();
    
    pwait("YOU DRAW A SINGLE DROP\n"
	  "OF BLOOD AS TRIBUTE");
    
    game->sacrifice += IDOL_SACRIFICE_GAIN;
    game->piety -= IDOL_SMASH_PIETY + rand() % IDOL_SMASH_PIETY;

    if (player->hp <= 0)
    {
      draw_board();
      pwait("YOU HAVE GIVEN YOUR LIFE!!!");

      draw_board();
      game_over("YOU SACRIFICED YOURSELF\n"
		"TO A DARK AND NAMELESS GOD", false);
    }
    else if (rand() % MAX(1, game->sacrifice) > IDOL_SACRIFICE_LIMIT)
    {
      draw_board();
 
      game->sacrifice -= IDOL_SACRIFICE_LIMIT;

      draw_board();

      switch(rand() % 2)
      {
      case 0:
	pwait("YOU HAVE BEEN REWARDED");
	refill_hp(IDOL_HP_REFILL);
	break;

      case 1:
	pwait("YOU HEAR A MOCKING LAUGHTER");
	refill_hp(5);
	player->strength = MAX(1, player->strength - 4 + rand() % 9);
	player->speed = MAX(1, player->speed - 4 + rand() % 9);
	break;
      }
      
    }
  }

  return;
}


int anything_near()
{
  int i;
  
  for (i = 1; i < MAX_MOBS; i++)
    if (game->mob[i].type != MOB_NONE && on_board(&game->mob[i]))
      return true;

  return false;
}



#define NOW_DANCE(a) m->flags = a; draw_board(); lpause();
#define Q_DANCE(a)   m->flags = a; draw_board(); mpause();
#define DANCE_FLIP() m->flip = !m->flip;

void disco()
{
  bool old_flip;
  mob_t * m;
  int i;

  pwait("THIS LOOKS LIKE A DANCE FLOOR!");

  stile(player->y, player->x, TL_VOID);

  m = player;
  old_flip = m->flip;

  m->flip = true;
  m->type = MOB_DANCER;

  draw_board();
  opause();

  for (i = 0; i < 9; i++)
  {
    stile(m->y - 5 + i % 2, m->x - 4 + i, TL_DISCOLIGHT1 + i);
    draw_board();
    lpause();
  }

  NOW_DANCE(0); NOW_DANCE(1); NOW_DANCE(0); NOW_DANCE(1);
  DANCE_FLIP();
  NOW_DANCE(0); NOW_DANCE(1); NOW_DANCE(0); NOW_DANCE(1);

  NOW_DANCE(0);
  
  NOW_DANCE(10);

  NOW_DANCE(11);
  NOW_DANCE(12);
  DANCE_FLIP();
  NOW_DANCE(11); 

  NOW_DANCE(10);

  NOW_DANCE(11);
  NOW_DANCE(12);
  DANCE_FLIP();
  NOW_DANCE(11);

  DANCE_FLIP();
  NOW_DANCE(20); NOW_DANCE(21); NOW_DANCE(20); NOW_DANCE(22);
  DANCE_FLIP();
  NOW_DANCE(20); NOW_DANCE(21); NOW_DANCE(20); NOW_DANCE(22);

//  DANCE_FLIP();
  m->x -= 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x += 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x += 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x -= 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x -= 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x += 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x += 1; NOW_DANCE(30);
  DANCE_FLIP();
  m->x -= 1; NOW_DANCE(30);
  
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  m->x += 1;
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  m->x += 1;
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);

  //DANCE_FLIP();
  m->x -= 1; m->y -= 1;
  NOW_DANCE(40);
  m->x -= 1;
  NOW_DANCE(40);
  m->x -= 1; m->y += 1;
  NOW_DANCE(40);

  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);

  DANCE_FLIP();
  m->x += 1; m->y -= 1;
  NOW_DANCE(40);
  m->x += 1;
  NOW_DANCE(40);
  m->x += 1; m->y += 1;
  NOW_DANCE(40);

  NOW_DANCE(50);
  m->x -= 1;
  NOW_DANCE(51);
  NOW_DANCE(50);
  m->x -= 1;
  NOW_DANCE(51);
  NOW_DANCE(50);
  m->x -= 1;
  NOW_DANCE(51);
  NOW_DANCE(50);
  m->x -= 1;
  NOW_DANCE(51);
  NOW_DANCE(50);
//  NOW_DANCE(51);

  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  m->x += 1;
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);
  m->x += 1;
  DANCE_FLIP(); Q_DANCE(31);
  DANCE_FLIP(); Q_DANCE(31);

  NOW_DANCE(60);
  DANCE_FLIP();
  NOW_DANCE(60);
  m->y += 1;
  NOW_DANCE(60);

  DANCE_FLIP();
  m->y -= 1;
  NOW_DANCE(70); lpause();
  NOW_DANCE(71); lpause();
  NOW_DANCE(70); lpause();
  NOW_DANCE(71);

  opause();

  for (i = 0; i < 9; i++)
  {
    stile(m->y - 5, m->x - 4 + i, TL_VOID);
    stile(m->y - 4, m->x - 4 + i, TL_VOID);
  }

  m->type = MOB_PLAYER;
  m->flags = 0;
  m->flip = old_flip;

  draw_board();

  lpause();

  char line[DEFLEN];
  snprintf(line, DEFLEN, "YOU GET %d EXPERIENCE", DISCO_EXP);
  pwait(line);
  draw_board();
  give_exp(DISCO_EXP);
  draw_stats();
  
  return;
}



void camp()
{
  int dish;
  int meat;
  char food[100];

  strcpy(food, "YOU SPEND AN HOUR EATING\n");

  meat = rand() % 7;
  dish = rand() % 8;

  switch (dish)
  {
  case 0: strcat(food, "DEEP FRIED "); break;

  default:
    switch (rand() % 15)
    {
    case 0: strcat(food, "SALTY "); break;
    case 1: strcat(food, "SPICY "); break;
    case 2: strcat(food, "PEPPERED "); break;
    }
    
    break;
  }

  switch (meat)
  {
  case 0: strcat(food, "GNOBLIN"); break;
  case 1: strcat(food, "SPIDER"); break;
  case 2: strcat(food, "BLURK"); break;
  case 3: strcat(food, "SNAKE"); break;
  case 4: strcat(food, "MIMIC"); break;
  case 5: strcat(food, "IMP"); break;
  case 6: strcat(food, "GHOUL"); break;
  }

  switch (dish)
  {
  case 0: break;
  case 1: strcat(food, "-ON-A-STICK"); break;
  case 2: strcat(food, " RAGU"); break;
  case 3: strcat(food, " ROAST"); break;
  case 4: strcat(food, " STEW"); break;
  case 5: strcat(food, " SOUP"); break;
  case 6: strcat(food, " GUMBO"); break;
  case 7: strcat(food, " NUGGETS"); break;
  }

  switch (rand() % 20)
  {
  case 0: strcat(food, " WITH BEANS"); break;
  case 1: strcat(food, " WITH BROCCOLI"); break;
  case 2: strcat(food, " WITH CHEESE"); break;
  case 3: strcat(food, " WITH PICKLES"); break;
  case 4: strcat(food, " WITH ONION RINGS"); break;
  default: break;
  }

  strcat(food, "\n\n");

  switch (rand() % 4)
  {
  case 0: strcat(food, "IT WAS DELICIOUS!"); break;
  case 1: strcat(food, "YOU'VE HAD BETTER"); break;
  case 2: strcat(food, "YOU FEEL SLIGHTLY NAUSEOUS"); break;
  case 3: strcat(food, "THAT HIT THE SPOT!"); break;
  }

  pwait(food);

  decorate(player->y, player->x, DEC_SPENTCAMP);
  draw_board();

  refill_hp(CAMP_HEAL);  

  return;
}



void gaze_orb(void)
{
  int turns;
  int inp;
  int y;
  int x;
  
  turns = 400;

  pwait("AS YOU GAZE INTO THE ORB, YOUR\n"
	"MIND DRIFTS INTO THE ASTRAL REALM");
  
  setlowmsg("PRESS DIRECTION TO MOVE VISION");
  draw_lowmsg();

  game->scrying = true;
  draw_board();

  while (turns > 0)
  {
    inp = getch();

    if (inp == ' ')
      break;
    else if (inp == KEY_LEFT)
    {
      view_x = MAX(0, view_x - 5);
      turns -= 2;
    }
    else if (inp == KEY_RIGHT)
    {
      view_x = MIN(MAP_W - BOARD_W - 1, view_x + 5);
      turns -= 2;
    }
    else if (inp == KEY_UP)
    {
      view_y = MAX(0, view_y - 2);
      turns -= 3;
    }
    else if (inp == KEY_DOWN)
    {
      // *2 is to prevent the player from scrying the bottom floor
      view_y = MIN(MAP_H - (FLOOR_H * 2) - BOARD_H - 1, view_y + 2);
      turns -= 3;
    }
    else
      continue;


    y = (view_y + (FLOOR_H / 2)) / FLOOR_H;
    x = (view_x + (BOARD_W / 2)) / CELL_TO_TILES;
    
    y = MAX(0, MIN(MAX_FLOORS - 1, y));
    x = MAX(1, MIN(CELLS_W - 2, x));
    
    game->automap[y][x]     |= AUTOMAP_KNOWN;
    game->automap[y][x - 2] |= AUTOMAP_KNOWN;
    game->automap[y][x - 1] |= AUTOMAP_KNOWN;
    game->automap[y][x + 1] |= AUTOMAP_KNOWN;
    game->automap[y][x + 2] |= AUTOMAP_KNOWN;

    draw_board();
  }

  stile(player->y, player->x, TL_ORB_C);
  stile(player->y - 1, player->x, TL_ORB_DARK);

  game->scrying = false;
  view_y = player->y - FLOOR_Y + 1;
  recenter(false);

  pwait("YOU ARE YANKED BACK TO YOUR BODY");

  draw_board();

  lowmsg[0] = '\0';
  draw_lowmsg();

  return;
}



void sword_in_stone()
{
  if (psel("THERE IS A SWORD SET IN STONE HERE\n"
	   "\n"
	   "<- DRAW IT#LEAVE IT ->") == 0)
  {
    if (player->strength < SWORD_IN_STONE_STR)
    {
      draw_board();
      pwait("ALAS, YOU ARE NOT STRONG ENOUGH");
    }
    else
    {
      give_weapon(WPN_RUNESWORD);

      stile(player->y, player->x, TL_VOID);
      stile(player->y - 1, player->x, TL_VOID);
      stile(player->y - 2, player->x, TL_VOID);

      draw_board();
	 
      pwait("YOU DRAW THE SWORD FROM THE STONE\n"
	    "\n"
	    "THIS IS THE FABLED *RUNESWORD* !!!");
    }
  }

  return;
}




void draw_tablet(int highlight)
{
  chtype hl;
  int y;
  int x;
  int i;

  hl = COLOR_PAIR(PAIR_GREEN) | A_BOLD;

  werase(board);

  if (highlight == 0)
    wattrset(board, hl);
  else
    wattrset(board, COLOR_PAIR(PAIR_WHITE));
  
  y = 3;
  x = BOARD_W / 2;

  mvwaddch(board, y, x, ACS_PLUS);
  mvwaddch(board, y - 1, x, ACS_VLINE);
  mvwaddch(board, y - 2, x, ACS_VLINE);
  mvwaddch(board, y - 2, x - 3, '\\');
  mvwaddch(board, y - 2, x + 3, '/');
  mvwaddstr(board, y - 3, x - 3, "_______");

  mvwaddch(board, y, x - 4, ACS_ULCORNER);
  mvwaddch(board, y, x - 3, ACS_HLINE);
  mvwaddch(board, y, x - 2, ACS_HLINE);
  mvwaddch(board, y, x - 1, ACS_HLINE);

  mvwaddch(board, y, x + 1, ACS_HLINE);
  mvwaddch(board, y, x + 2, ACS_HLINE);
  mvwaddch(board, y, x + 3, ACS_HLINE);
  mvwaddch(board, y, x + 4, ACS_URCORNER);

  mvwaddch(board, y + 1, x, ACS_VLINE);
  mvwaddch(board, y + 2, x, ACS_VLINE);
  mvwaddch(board, y + 1, x - 4, ACS_VLINE);
  mvwaddch(board, y + 2, x - 4, ACS_VLINE);
  mvwaddch(board, y + 1, x + 4, ACS_VLINE);
  mvwaddch(board, y + 2, x + 4, ACS_VLINE);

  if (highlight == 1)
    wattrset(board, hl);
  else
    wattrset(board, COLOR_PAIR(PAIR_WHITE));

  y = 7;
  x = BOARD_W * 0.75;

  mvwaddstr(board, y - 2, x - 4, "\\       /");
  mvwaddstr(board, y - 1, x - 4, " \\_____/ ");
  mvwaddstr(board, y - 0, x - 4, "  /   \\  ");
  mvwaddstr(board, y + 1, x - 4, " /     \\ ");
  mvwaddstr(board, y + 2, x - 4, "/       \\");

  if (highlight == 2)
    wattrset(board, hl);
  else
    wattrset(board, COLOR_PAIR(PAIR_WHITE));

  y = 10;
  x = BOARD_W / 2;

  mvwaddstr(board, y - 2, x - 4, " _     _ ");
  mvwaddstr(board, y - 1, x - 4, " /     \\ ");
  mvwaddstr(board, y - 0, x - 4, "/       \\");
  mvwaddstr(board, y + 1, x - 4, "\\       /");
  mvwaddstr(board, y + 2, x - 4, " \\__|__/ ");

  mvwaddch(board, y + 0, x, ACS_VLINE);
  mvwaddch(board, y + 1, x, ACS_VLINE);
//  mvwaddch(board, y + 2, x, ACS_VLINE);

  if (highlight == 3)
    wattrset(board, hl);
  else
    wattrset(board, COLOR_PAIR(PAIR_WHITE));

  y = 7;
  x = BOARD_W * 0.25;

  mvwaddch(board, y - 2, x - 4, ACS_ULCORNER);
  mvwaddch(board, y - 2, x - 3, ACS_HLINE);
  mvwaddch(board, y - 2, x - 2, ACS_TTEE);
  mvwaddch(board, y - 2, x - 1, ACS_HLINE);
  mvwaddch(board, y - 2, x + 0, ACS_HLINE);
  mvwaddch(board, y - 2, x + 1, ACS_HLINE);
  mvwaddch(board, y - 2, x + 2, ACS_TTEE);
  mvwaddch(board, y - 2, x + 3, ACS_HLINE);
  mvwaddch(board, y - 2, x + 4, ACS_URCORNER);

  mvwaddch(board, y + 2, x - 4, ACS_LLCORNER);
  mvwaddch(board, y + 2, x - 3, ACS_HLINE);
  mvwaddch(board, y + 2, x - 2, ACS_BTEE);
  mvwaddch(board, y + 2, x - 1, ACS_HLINE);
  mvwaddch(board, y + 2, x + 0, ACS_HLINE);
  mvwaddch(board, y + 2, x + 1, ACS_HLINE);
  mvwaddch(board, y + 2, x + 2, ACS_BTEE);
  mvwaddch(board, y + 2, x + 3, ACS_HLINE);
  mvwaddch(board, y + 2, x + 4, ACS_LRCORNER);

  for (i = 0; i < 3; i++)
  {
    mvwaddch(board, y - 1 + i, x - 4, ACS_VLINE);
    mvwaddch(board, y - 1 + i, x - 2, ACS_VLINE);
    mvwaddch(board, y - 1 + i, x + 2, ACS_VLINE);
    mvwaddch(board, y - 1 + i, x + 4, ACS_VLINE);
  }

  wrefresh(board);
}



void stone_tablet()
{
  char line[DEFLEN];
  int seq[15];
  int inp_seq[15];
  int i;
  int states = 7;
  int exp;

  pwait("YOU FIND A MYSTERIOUS STONE TABLET");

  stile(player->y, player->x, TL_VOID);
  stile(player->y - 1, player->x, TL_VOID);
  
  states = game->tablet_diff;
  
  draw_tablet(-1);

  pwait("REPEAT THE SEQUENCE\n"
	"USING THE DIRECTIONAL KEYS");

  draw_tablet(-1);

  for (i = 0; i < states; i++)
  {
    opause();
    seq[i] = rand() % 4;
    draw_tablet(seq[i]);
    opause();
    draw_tablet(-1);
  }

  for (i = 0; i < states; i++)
  {
    int gk;

    gk = getch();
    
    if (gk == KEY_UP)
      inp_seq[i] = 0;
    else if (gk == KEY_RIGHT)
      inp_seq[i] = 1;
    else if (gk == KEY_DOWN)
      inp_seq[i] = 2;
    else if (gk == KEY_LEFT)
      inp_seq[i] = 3;
    else
    {
      snprintf(lowmsg, DEFLEN, "INVALID INPUT");
      draw_lowmsg();
      continue;
    }

    if (inp_seq[i] != seq[i])
    {
      lpause();
      board_attr(A_REVERSE | A_BOLD, PAIR_RED);
      wrefresh(board);
      pwait("SHIT");
      draw_board();
      return;
    }
    else
    {
      draw_tablet(seq[i]);
      opause();
      draw_tablet(-1);
      flush_input();
    }
  }

  draw_board();

  switch (states)
  {
  case 7:  exp = 1000; break;
  case 8:  exp = 2000; break;
  case 9:  exp = 3000; break;
  default: exp = 1000; break;
  }
    
  snprintf(line, DEFLEN,
	   "YOU HAVE DECODED THE MYSTIC RUNES\n"
	   "\nYOU GET %d EXP",
	   exp);

  pwait(line);
  draw_board();
  
  give_exp(exp);
  draw_stats();

  // Make it harder next time
  game->tablet_diff += 1;
  
  draw_stats();
  
  return;
}




void mushrooms()
{
  stile(player->y, player->x, TL_MUSH_CLEARED);
  
  switch (rand() % 3)
  {
  case 0:
    game->beer = 20;
    draw_board_norefresh();
    pwait("@ WOW !!! @");
    break;

  case 1:
    game->hallucination = 20;
    draw_board_norefresh();
    pwait("@ WOW !!! @");
    break;

    // TODO: Teleport to subquest
    
  default:
    pwait("WOW!!!\n\nYOU FEEL MUCH STRONGER!");
    change_pl_st(+4);
    break;
  }


  return;
}

