#include "basment.h"



bool is_trap(int tile)
{
  if (tile == TL_T_CAVEIN ||
      tile == TL_T_POISON ||
      tile == TL_T_GORZOTH_L ||
      tile == TL_T_GORZOTH_R ||
      tile == TL_T_POISON_REV)
  {
    return true;
  }

  return false;
}


/*
  Drop some boulders on the player
*/
void cavein(void)
{
  int sc_x;
  int sc_y;
  int x;
  int y;

  game->traps_triggered++;

  stile(player->y, player->x, TL_VOID);

  recenter(false);
  
  draw_board();

  pwait("CAVE-IN!");

  tremor(5);

  stile(player->y - 6, player->x - 1, TL_VOID);
  stile(player->y - 6, player->x + 0, TL_VOID);
  stile(player->y - 6, player->x + 1, TL_VOID);

  // Catch stalactites as well
  stile(player->y - 5, player->x - 1, TL_VOID);
  stile(player->y - 5, player->x + 0, TL_VOID);
  stile(player->y - 5, player->x + 1, TL_VOID);

  draw_board();

  sc_y = 1;
  sc_x = player->x - view_x;

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

  stile(player->y, player->x - 2, TL_BOULDER);
  stile(player->y, player->x - 1, TL_BOULDER);
  stile(player->y, player->x + 0, TL_BOULDER);
  stile(player->y, player->x + 1, TL_BOULDER);
  stile(player->y, player->x + 2, TL_BOULDER);

  stile(player->y - 1, player->x - 1, TL_BOULDER);
  stile(player->y - 1, player->x + 1, TL_BOULDER);
  
  draw_board();

  if (rand() % player->speed > 8)
  {
    pwait("YOU AVOID THE FALLING ROCKS!");
    return;
  }

  int dam;
  dam = CAVEIN_DAMAGE_ROLL;
  player->hp -= dam;
  draw_bars();

  if (player->hp <= 0)
  {
    player->type = MOB_GORE;
    draw_board();
    game_over("YOU WERE SMASHED\n"
	      "BY FALLING ROCKS", false);
  }
  else
  {
    pwait("YOU ARE HIT BY\n"
	  "FALLING ROCKS!");
  }

  return;
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
    spause(); spause();
    spause(); spause();
  }

  // Reset view but do not redraw
  view_y = old_view_y;
  view_x = old_view_x;

//  draw_board();

  return;
}
