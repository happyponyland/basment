#include "basment.h"



bool is_trap(int tile)
{
  if (tile == TL_T_CAVEIN     ||
      tile == TL_T_POISON     ||
      tile == TL_T_POISON_REV ||
      tile == TL_T_GORZOTH_L  ||
      tile == TL_T_GORZOTH_R  ||
      tile == TL_T_WEB        ||
      tile == TL_T_FLASH      ||
      tile == TL_T_UWNET      || 0)
  {
    return true;
  }

  return false;
}




void flash_trap()
{
  stile(player->y, player->x, TL_VOID);
  
  if (game->blinded)
    return;
  
  board_flash();

  if (has_eq(EQ_SHADES))
  {
    draw_board_norefresh();
    pwait("YOU TRIGGER A FLASH TRAP!\n\nFORTUNATELY, YOU ARE WEARING SHADES");
  }
  else
  {
    game->blinded = 10;
    draw_board_norefresh();
    pwait("YOU TRIGGER A FLASH TRAP!\n\nYOU ARE BLINDED BY THE FLASH!");
  }

  draw_board();
  
  return;
}



void board_flash()
{
  int sc_y;
  int sc_x;
  int c;
  int a;
  
  draw_board_norefresh();

  for (sc_y = 0; sc_y < BOARD_H; sc_y++)
  {
    for (sc_x = 0; sc_x <= BOARD_W; sc_x++)
    {
      c = mvwinch(board, sc_y, sc_x) & (A_CHARTEXT);
      a = mvwinch(board, sc_y, sc_x) & ((1<<22) | (1<<18));
      waddch(board, c | a | COLOR_PAIR(PAIR_WHITE) | A_REVERSE);
    }
  }

  wrefresh(board);

  lpause();

  return;
}



/*
  Drop some boulders on someone
*/
void cavein(mob_t * mob)
{
  char line[DEFLEN];
  int trap_y;
  int trap_x;
  int sc_y;
  int sc_x;
  int x;
  int y;

  game->traps_triggered++;

  trap_y = mob->y;
  trap_x = mob->x;

  // Remove trap trigger
  stile(trap_y, trap_x, TL_VOID);

  recenter(false);
  
  draw_board();

  pwait("CAVE-IN!");

  tremor(5);

  draw_board();

//  stile(player->y - 9, player->x - 1, TL_VOID);
//  stile(player->y - 9, player->x + 0, TL_VOID);
//  stile(player->y - 9, player->x + 1, TL_VOID);
  stile(trap_y - 8, trap_x - 1, TL_VOID);
  stile(trap_y - 8, trap_x + 0, TL_VOID);
  stile(trap_y - 8, trap_x + 1, TL_VOID);
  stile(trap_y - 7, trap_x - 1, TL_VOID);
  stile(trap_y - 7, trap_x + 0, TL_VOID);
  stile(trap_y - 7, trap_x + 1, TL_VOID);
  stile(trap_y - 6, trap_x - 1, TL_VOID);
  stile(trap_y - 6, trap_x + 0, TL_VOID);
  stile(trap_y - 6, trap_x + 1, TL_VOID);

  // Catch stalactites as well
  stile(trap_y - 5, trap_x - 1, TL_VOID);
  stile(trap_y - 5, trap_x + 0, TL_VOID);
  stile(trap_y - 5, trap_x + 1, TL_VOID);

  sc_y = 1;
  sc_x = trap_x - view_x;

  for (x = 0; x < 3; x++)
  {
    for (y = 0; y < 3; y++)
    {
      wmove(board, sc_y + y, sc_x - 1 + x);
      waddch(board, 'o' | COLOR_PAIR(PAIR_BROWN));
    }
  }

  lpause();

  for (x = 0; x < 3; x++)
  {
    for (y = x % 2; y < 9; y += 2)
    {
      wmove(board, sc_y + (y % 3), sc_x - 1 + x);
      waddch(board, ' ');

      wmove(board, sc_y + y, sc_x - 1 + x);
      waddch(board, 'o' | COLOR_PAIR(PAIR_BROWN));
      wrefresh(board);
      spause();
    }
  }

  stile(trap_y, trap_x - 2, TL_BOULDER);
  stile(trap_y, trap_x - 1, TL_BOULDER);
  stile(trap_y, trap_x + 0, TL_BOULDER);
  stile(trap_y, trap_x + 1, TL_BOULDER);
  stile(trap_y, trap_x + 2, TL_BOULDER);

  stile(trap_y - 1, trap_x - 1, TL_BOULDER);
  stile(trap_y - 1, trap_x + 1, TL_BOULDER);
  
  draw_board();

  if (mob == player && rand() % player->speed > 8)
  {
    pwait("YOU AVOID THE FALLING ROCKS!");
    return;
  }

  int dam;
  dam = CAVEIN_DAMAGE_ROLL;

  if (mob != player)
    dam *= 3;

  mob->hp -= dam;
  draw_bars();

  if (mob == player)
  {
    if (mob->hp <= 0)
    {
      player->type = MOB_GORE;
      draw_board();
      game_over("YOU WERE CRUSHED\n"
		"BY FALLING ROCKS", false);
    }
    else
    {
      pwait("YOU ARE HIT BY\n"
	    "FALLING ROCKS!");
    }
  }
  else
  {
    mob->flags = GFX_HURT;
    draw_board();
    lpause();
    mob->flags = 0;
   
    if (mob->hp <= 0)
    {
      snprintf(line, DEFLEN, "%s%s WAS CRUSHED\nBY FALLING ROCKS!",
	       article[mob->article], mob_name[mob->type]);
      mob->type = MOB_NONE;
      draw_board();
      pwait(line);
    }
  }

  return;
}



int monster_trap(mob_t * mob)
{
  int tile_feet;

  tile_feet = gtile(mob->y, mob->x);

  if (tile_feet == TL_T_CAVEIN)
  {
    cavein(mob);
    return true;
  }

  return false;
}



void poison_gas()
{
  int y;
  int x;
  int i;

  game->traps_triggered++;

  y = player->y;
  x = player->x;

  if (gtile(y, x) == TL_T_POISON)
  {
    pwait("YOU ARE ENVELOPED\n"
	  "BY POISON GAS!");

    for (i = 0; i < 6; i++)
    {
      stile(y - i, x - 3, TL_POISON_L1);
      stile(y - i, x - 2, TL_POISON_L2);
      stile(y - i, x - 1, TL_POISON_L3);
      stile(y - i, x + 0, TL_POISON_R3);
      stile(y - i, x + 1, TL_POISON_R3);
      stile(y - i, x + 2, TL_POISON_R2);
      stile(y - i, x + 3, TL_POISON_R1);
      draw_board();
      lpause();
    }

    stile(y, x, TL_T_POISON_REV);
  }
  else
  {
    pwait("YOU INHALE THE VILE FUMES!");
  }

  player->flags = GFX_HURT;
  draw_board(); lpause();
  player->flags = 0;

  player->hp -= 2 + rand() % 7;

  draw_bars();

  if (player->hp <= 0)
  {
    draw_board();
    game_over("YOU WERE GASSED TO DEATH", false);
  }

  return;
}




void summon_gorzoth(void)
{
  int y;
  int x;
  int i;
  int type;
  int dir;

  type = gtile(player->y, player->x);
  
  if (type == TL_T_GORZOTH_L)
    dir = -1;
  else if (type == TL_T_GORZOTH_R)
    dir = +1;

  stile(player->y, player->x, TL_VOID);

  recenter(false);
  tremor(5);

  // Restore board so we get the right text placement
  draw_board();
  mob_text(player, ".  "); opause();
  mob_text(player, ".. "); opause();
  mob_text(player, "..."); opause();

  x = player->x + 3 * dir;

  stile(player->y, x, TL_STOP);
  x += dir;

  for (i = 0; i <= 17; i++)
  {
    x += dir;

    tremor(1);

    for (y = player->y + 1; y <= player->y + 8; y++)
    {
      if (i > 0 && i < 17)
	stile(y, x, TL_CHASM);
      else
	stile(y, x, TL_VOID);
    }
  }

  x += dir * 2;
  stile(player->y, x, TL_STOP);

//  pwait("GORZOTH");
  draw_board();


  int mob_i;

  mob_i = make_monster(player->y + FLOOR_H, player->x + 10 * dir, MOB_GORZOTH);

  if (dir < 0)
    game->mob[mob_i].flip = false;
  else
    game->mob[mob_i].flip = true;

  for (i = 0; i < FLOOR_H; i++)
  {
    game->mob[mob_i].y--;
    tremor(1);
    //lpause();
  }

  draw_board();

  flush_input();

  return;
}



void tremor(int amount)
{
  int old_view_y;
  int old_view_x;
  
  old_view_y = view_y;
  old_view_x = view_x;

  while (amount--)
  {
    view_y = keep_in_range(0, old_view_y - 1 + rand() % 3, MAP_H - BOARD_H - 1);
    view_x = keep_in_range(0, old_view_x - 1 + rand() % 3, MAP_W - BOARD_W - 1);
    draw_board();
    mpause();
    ///spause();
//    spause(); spause();
  }

  // Reset view but do not redraw
  view_y = old_view_y;
  view_x = old_view_x;

//  draw_board();

  return;
}



void web_net()
{
  char line[DEFLEN];
  int y;
  int x;
  
  game->traps_triggered++;

  y = player->y;
  x = player->x;

  player->webbed = WEBBED_TURNS + rand() % WEBBED_TURNS;

  if (gtile(y, x) == TL_T_WEB)
  {
    pwait("YOU GET STUCK IN A WEB!!!");
    decorate(y, x, DEC_WEB);
    draw_board();
      
    if (has_eq(EQ_TORCH))
    {
      pwait("FORTUNATELY, YOU ARE CARRYING A TORCH");

//      int old_y; int old_x;
      int new_y; int new_x;
      int i;

//      old_y = y - 2;
//      old_x = x;

      for (i = 0; i < 50; i++)
      {
	new_y = y - 5 + rand() % 6;
	new_x = x - 2 + rand() % 5;
	new_x += (rand() % 2 ? +1 : -1);
	stile(new_y, new_x, TL_WEB_BURN1 + rand() % 2);
	draw_board();
	spause();
//	stile(new_y, new_x, TL_VOID);
      }

      for (new_y = y - 5; new_y <= y; new_y++)
      {
	for (new_x = x - 4; new_x <= x + 4; new_x++)
	{
	  if (gtile(new_y, new_x) == TL_WEB_BURN1 ||
	      gtile(new_y, new_x) == TL_WEB_BURN2)
	    stile(new_y, new_x, TL_VOID);
	}
      }
      
      draw_board();
	  
      player->webbed = 0;
    }
    else
    {
      pwait("YOUR STRUGGLING HAS ATTRACTED\n"
	    "SOME UNDESIRED ATTENTION!!!");
	    
      make_monster(y, x - 5, MOB_SPIDER);
      make_monster(y, x + 5, MOB_SPIDER);
    }
  }
  else if (gtile(y, x) == TL_T_UWNET)
  {
    pwait("YOU GET STUCK IN A NET!!!");
    decorate(y, x, DEC_NET);
    draw_board();

    if (game->weapon == WPN_DAGGER ||
	game->weapon == WPN_DRAIN ||
	game->weapon == WPN_SWORD ||
	game->weapon == WPN_GLASS ||
	game->weapon == WPN_RUNESWORD)
    {
      if (game->weapon == WPN_RUNESWORD)
      {
	snprintf(line, DEFLEN,
		 "FORTUNATELY, YOU HAVE\n"
		 "THE FABLED *RUNESWORD*\n"
		 "TO CUT YOURSELF FREE");
      }
      else
      {
	snprintf(line, DEFLEN,
		 "FORTUNATELY, YOU HAVE A %s\n"
		 "TO CUT YOURSELF FREE",
		 weapon_name[game->weapon]);
      }
      
      pwait(line);

      player->webbed = 0;
      draw_board();
    }
  }
  

  return;
}




int trap_sprung(int tile_feet)
{
  if (tile_feet == TL_T_CAVEIN)
  {
    cavein(player);
    return true;
  }
  else if (tile_feet == TL_T_UWNET || tile_feet == TL_T_WEB)
  {
    web_net();
    return true;
  }
  else if (tile_feet == TL_T_FLASH)
  {
    flash_trap();
    return true;
  }
  else if (tile_feet == TL_T_POISON ||
	   tile_feet == TL_T_POISON_REV)
  {
    poison_gas();
    return true;
  }
  else if (tile_feet == TL_T_GORZOTH_L ||
	   tile_feet == TL_T_GORZOTH_R)
  {
    summon_gorzoth();
    return true;
  }
  else if (tile_feet == TL_P_HELL)
  {
    interact();
  }

  return false;
}
