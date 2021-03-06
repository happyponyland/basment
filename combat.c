#include "basment.h"



bool melee(mob_t * attacker, int speed)
{
  char line[DEFLEN];
  mob_t * target;
  int att_x;
  int range;
  int i;

  range = attacker->range;

  att_x = attacker->x;

  if (speed > 0)
    att_x++;

  for (i = 0; i < range; i++)
  {
    att_x += speed;

    target = find_enemy(attacker, player->y, att_x);

    if (target == NULL)
      continue;

    if (target->type == MOB_MIMIC && target->attack_phase == 0)
    {
      pwait("WAIT! THAT IS A SMALL MIMIC!");
      target->attack_phase = 1;
      target->flags = 0;
      return true;
    }
    else if (target->type == MOB_BLURK && target->attack_phase == 0)
    {
      draw_board_norefresh();
      pwait("OH NO! AN INSIDIOUS BLURK BARS YOUR WAY!");
      target->attack_phase = 1;
      target->flags = 0;
      return true;
    }

    // Attack!

    // The attacker must always lower their shield
    attacker->shd_up = 0;

    if (attacker == player && game->weapon > WPN_UNARMED)
    {
      damage_weapon(1);
    }

    // If the target has their shield up and they are facing each other
    if (target->shd_up && target->flip != attacker->flip)
    {
      if (shield_block(target))
      {
	mob_text(target, "BLOCK");
	damage_shield(target);

	if (target->type == MOB_KNAVE)
	{
	  if (target->attack_phase == 0)
	    target->attack_phase = 1;
	  else if (target->attack_phase == 1 || target->attack_phase == 2)
	  {
	    move_towards_player(target);
	  }
	}

	return true;
      }
    }

    damage(attacker, target);
    
    if (attacker->attack_frames == 2)
    {
      attacker->flags = GFX_ATTACK2;
      draw_board(); lpause();
      attacker->flags = 0;
    }

    attacker->flags = GFX_ATTACK;
    draw_board(); lpause();
    attacker->flags = 0;

    damage_armor(target);

    // Draining dagger restores attacker HP
    if (attacker == player && game->weapon == WPN_DRAIN)
    {
      attacker->hp += 1;
    }
    
    if (target->hp > 0)
    {
      // Keep track of who we are fighting
      if (attacker == player)
      {
	enemy_bar = target->index;
	enemy_bar_time = BAR_TIMEOUT;
	draw_bars();
      }
      else if (target == player)
      {
	enemy_bar = attacker->index;
	enemy_bar_time = BAR_TIMEOUT;
	draw_bars();
      }
    }
    
    target->flags = GFX_HURT;
    draw_board(); lpause();
    target->flags = 0;

    if (target->hp <= 0)
    {
      if (target == player)
      {
	snprintf(line, DEFLEN,
		 "YOU WERE %s\n"
		 "BY %s%s",
		 attacker->killverb,
		 article[attacker->article],
		 mob_name[attacker->type]);

	draw_bars();
	game_over(line, false);
      }
      else
      {
	kill_enemy(target);
      }
    }

    if (attacker->type == MOB_ROGUE &&
	game->player_gold > ROGUE_STEAL_GOLD &&
	rand() % 100 < ROGUE_STEAL_CHANCE)
    {
      rogue_escape(attacker);
    }
    
    return true;
  }

  return false;
}




void rogue_escape(mob_t * m)
{
  int dir;
  int i;
  char line[DEFLEN];
  int stolen;

  if (game->player_gold == 0)
    return;

  if (m->x < player->x)
  {
    dir = -2;
    m->flip = true;
  }
  else
  {
    dir = +2;
    m->flip = false;
  }

  for (i = 0; i < 2; i++)
  {
    m->flags = GFX_HUMAN_FALL1;
    draw_board(); mpause();
    m->flags = GFX_HUMAN_FALL2;
    draw_board(); mpause();
  }

  m->flags = 0;

  while (m->x > view_x - 2 && m->x <= view_x + BOARD_W + 2)
  {
    m->x += dir;
    draw_board(); spause();
  }

  m->type = MOB_NONE;

  if (game->player_gold)
  {
    if (has_eq(EQ_SHADES) && rand() % 10 == 0)
    {
      game->equipment[EQ_SHADES] = false;
      snprintf(line, DEFLEN, "ROGUE STOLE YOUR SHADES AND RAN AWAY!\n\n(WHAT A JERK)");
    }
    else
    {
      stolen = 1 + rand() % ROGUE_STEAL_GOLD;
      game->player_gold -= stolen;
      snprintf(line, DEFLEN, "ROGUE STOLE %d GOLD AND RAN AWAY!", stolen);
    }

    draw_stats();
    flush_input();
    pwait(line);
  }

  return;
}




int shoot_missile(mob_t * attacker, int dir)
{
  char line[DEFLEN];
  mob_t * target;
  int m_y; int m_x;
  int sc_y; int sc_x;
  int count;
  int m_type;
  int adjust_y;
  int passes;
  int pass;
  int xbow;
  chtype color;
  chtype missile;

//   attacker = &game->mob[mi];

  xbow = false;
  passes = 1;

  adjust_y = water_offset(attacker);
  m_y = attacker->y;
  sc_y = m_y - view_y - 1;

  m_x = attacker->x +
    (attacker->flip ? -attacker->pack_w + 2 : attacker->pack_w - 2) +
    dir * 2;

  if (attacker->type == MOB_EYE)
  {
    m_type = MIS_DISINT;
    sc_y -= 1;
    m_x = attacker->x;
  }
  else if (attacker->type == MOB_LICH)
  {
    m_type = MIS_FIREBALL;
    sc_y -= 1;
  }
  else if (attacker == player)
  {
    if (game->weapon == WPN_BOW)
      m_type = MIS_ARROW;
    else if (game->weapon == WPN_3XBOW)
    {
      xbow = true;
      m_type = MIS_ARROW;

      if (water_offset(attacker))
	passes = 2;
      else
	passes = 3;
    }
    else if (game->weapon == WPN_BLASTER)
    {
      m_type = MIS_BLASTER;
      adjust_y -= 1;
    }
  }
  else
  {
    m_type = MIS_ARROW;
  }

  draw_board();
  
  for (pass = 0; pass < passes; pass++)
  {
    count = 0;
    
    if (xbow)
    {
      m_x = attacker->x +
	(attacker->flip ? -attacker->pack_w + 2 : attacker->pack_w - 2) +
	dir * 2;
      
      if (pass == 0)
	adjust_y = water_offset(attacker) - 1;
      else if (pass == 1)
	adjust_y = water_offset(attacker);
      else if (pass == 2)
	adjust_y = water_offset(attacker) + 1;
    }

    while (1)
    {
      m_x += dir;
      sc_x = m_x - view_x;
      count++;

      if (sc_x < 0 || sc_x >= BOARD_W)
	goto end_pass;//break;//return 0;
      
      target = find_enemy(attacker, m_y, m_x + dir);
      
      if (target == NULL)
      {
	if (game->blinded)
	  continue;
	
	if (m_type != MIS_BLASTER && count % 2 == 1)
	  continue;
	
	// Skip the length of the barrel
	if (m_type == MIS_BLASTER && count < 4)
	  continue;
	
	missile = '?';
	color = COLOR_PAIR(PAIR_GREEN);
	
	if (m_type == MIS_ARROW)
	{
	  missile = '-';
	  color = COLOR_PAIR(PAIR_MAGENTA);
	}
	if (m_type == MIS_BLASTER)
	{
	  missile = '=';
	  color = COLOR_PAIR(PAIR_MAGENTA);
	}
	else if (m_type == MIS_FIREBALL)
	{
	  missile = '*';
	  color = COLOR_PAIR(PAIR_RED);
	}
	else if (m_type == MIS_DISINT)
	{
	  missile = (dir > 0 ? '>' : '<');
	  color = COLOR_PAIR(PAIR_RED);
	}
	
	if (water_join(gtile(m_y - 1, m_x)))
	{
	  color = COLOR_PAIR(PAIR_BLACK_ON_CYAN);
	}
	
	if (m_type == MIS_BLASTER)
	{
	  mvwaddch(board, sc_y + adjust_y, sc_x, '_' | color);
/*	if (count % 2)
	mvwaddch(board, sc_y, sc_x, (dir > 0 ? ')' : '(') | color);
	else
	mvwaddch(board, sc_y - 1, sc_x, (dir > 0 ? ')' : '(') | color);*/
	}
	else
	  mvwaddch(board, sc_y + adjust_y, sc_x, missile | color);
	
	
	wrefresh(board);
	spause();
	
	continue;
      }
      
      if (target->shd_up &&
	  ((!target->flip && dir < 0) ||
	   (target->flip && dir > 0)) )
      {
	if (target == player &&
	    m_type == MIS_DISINT &&
	    target->shd_type != SHD_NONE &&
	    target->shd_type != SHD_MAGIC)
	{
	  flush_input();
	  snprintf(line, DEFLEN,
		   "DISINTEGRATION BEAM!!\n\nYOUR %s\nCRUMBLES TO DUST!",
		   armor_name[target->shd_type]);
	  pwait(line);
	  target->shd_type = SHD_NONE;
	  target->shd_up = false;
	  goto end_pass;//return true;
	}
	
	if (m_type != MIS_BLASTER && shield_block(target))
	{
	  mob_text(target, "BLOCK");
	  damage_shield(target);
	  goto end_pass; //return true;
	}
      }
      
      if (target == player && m_type == MIS_DISINT)
      {
	if (target->armor_type != ARMOR_NONE &&
	    target->armor_type != ARMOR_MAGIC)
	{
	  flush_input();
	  snprintf(line, DEFLEN,
		   "DISINTEGRATION BEAM!!\n\nYOUR %s\nCRUMBLES TO DUST!",
		   armor_name[target->armor_type]);
	  pwait(line);
	  target->armor_type = ARMOR_NONE;
	  goto end_pass;// return true;
	}
	
	if (game->weapon != WPN_UNARMED)
	{
	  flush_input();
	  snprintf(line, DEFLEN,
		   "DISINTEGRATION BEAM!!\n\nYOUR %s\nCRUMBLES TO DUST!",
		   weapon_name[game->weapon]);
	  pwait(line);
	  give_weapon(WPN_UNARMED);
	  goto end_pass; //return true;
	}
      }
      
      damage(attacker, target);
      
      if (m_type == MIS_ARROW)
      {
	target->flags = GFX_HURT;
	draw_board(); lpause();
	target->flags = 0;
      }
      else if (m_type == MIS_BLASTER)
      {
	target->flags = GFX_HURT;
	draw_board(); lpause();
	target->flags = 0;
      }
      else if (m_type == MIS_FIREBALL)
      {
	explosion(sc_y, sc_x + dir);
      }
      
      if (target == player)
      {
	draw_bars();
      }
      
      if (target->hp <= 0)
      {
	if (target == player)
	{
	  snprintf(line, DEFLEN,
		   "YOU WERE %s\n"
		   "BY %s%s",
		   (m_type == MIS_FIREBALL ? "FRIED" :
		    (m_type == MIS_DISINT ? "DISINTEGRATED" : "SHOT")),
		   article[attacker->article],
		   mob_name[attacker->type]);
	  draw_board();
	  game_over(line, false);
	}
	else
	{
	  if (!xbow || pass == passes - 1)
	    kill_enemy(target);

	  goto end_pass;
	}
      }
      else if (target != player)
      {
	enemy_bar = target->index;
	enemy_bar_time = BAR_TIMEOUT;
	draw_bars();
	
	// update the number of eyes it has
	if (target->type == MOB_BIGSPIDER)
	  draw_board();//	  draw_board();
      }

      damage_armor(target);
      goto end_pass;
    }

  end_pass:
    continue;
  }
  
//      return 1;
//    }
    
  return 1;
}



int damage(mob_t * attacker, mob_t * target)
{
  int amount;
  int base;

  base = attacker->damage;

  if (attacker == player)
  {
    switch (game->weapon)
    {
    case WPN_BOW:     base = 5; break;
    case WPN_BLASTER: base = 12; break;
    default: base = 3; break;
    }
  }
  
  amount = attacker->strength + rand() % (1 + base);
  
  if (attacker == player && game->beer)
  {
    amount *= 4;
  }

  if ((target->type == MOB_EVILTREE || target->type == MOB_SHRUBBERY) &&
      attacker == player &&
      game->weapon == WPN_AXE)
  {
    amount *= 2.5;
  }
  
  switch (target->armor_type)
  {
  case ARMOR_LEATHER:  amount -= 1;  break;
  case ARMOR_SCALE:    amount -= 2;  break;
  case ARMOR_PLATE:    amount -= 3;  break;
  case ARMOR_MAGIC:    amount -= 4;  break;
  case ARMOR_DRAGON:   amount -= 5;  break;
  case ARMOR_SPIDER:   amount = 1;   break;
    
  default: break;
  }

  amount = MAX(amount, 1);

  if (target == player &&
      player_underwater())
  {
    amount = spend_breath(player, amount);
  } 
  
  target->hp -= amount;

  return amount;
}


void kill_enemy(mob_t * target)
{
  char line[DEFLEN];
  bool boss = false;

  if (target->type == MOB_ARCHDEMON)
    boss = true;

  game->monsters_killed++;

  /*
// This shouldn't be needed anymore with monster packing
  if (target->type == MOB_BRICKWALL)
  {
    // Remove the hidden placeholders so creatures can move through the cleared area
    stile(target->y, target->x - 3, TL_VOID);
    stile(target->y, target->x + 3, TL_VOID);
  }
  */

  if (boss)
  {
    snprintf(line, DEFLEN,
	     "YOU HAVE SLAIN %s%s!!!",
	     article[target->article],
	     mob_name[target->type]);

    /* Don't remove boss */
  }
  else
  {
    snprintf(line, DEFLEN,
	     "YOU HAVE SLAIN %s%s\n"
	     "\n"
	     "YOU GET %d EXP",
	     article[target->article],
	     mob_name[target->type],
	     target->exp);

    target->type = MOB_NONE;
  }
  
  draw_board();
  
  enemy_bar = -1;
  draw_bars();
  
  pwait(line);
  
  draw_board();

  if (boss)
  {
    pwait("YOU HAVE WON!!!");

    game_over(NULL, true);
    //shutdown();
//    exit(0);
  }
  
  give_exp(target->exp);
  
  return;
}




