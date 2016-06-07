#include "basment.h"
#include "map.h"


void play()
{
  int mi;
  mob_t * mob;

  while (1)
  {
    for (mi = 0; mi < MAX_MOBS; mi++)
    {
      mob = &game->mob[mi];
      
      if (mob->type == MOB_NONE)
	continue;

      mob->counter += mob->speed;

      if (mob->counter >= TURN_COST)
      {
	mob->counter -= TURN_COST;

	if (mob->shd_up)
	{
	  mob->shd_up--;
	}

	if (mi == 0)
	  player_turn();
	else
	  enemy_turn(mi);
      }
    }
    
  }

  return;
}



void enemy_turn(int mi)
{
  mob_t * mob;
  bool ob;

  mob = &game->mob[mi];

  if (mob->y != player->y)
    return;

  ob = on_board(mob);

  if (ob)
    mob->alert = true;

  if (!mob->alert)
    return;

  if (ob && mob->type == MOB_KNAVE)
  {
    knave_logic(mob);
  }
  else if (mob->type == MOB_MIMIC && mob->attack_phase == 0)
  {
    mob->flags = GFX_MIMIC_IDLE;
  }
  else if (mob->type == MOB_BLURK && mob->attack_phase == 0)
  {
    mob->flags = GFX_BLURK_IDLE;
  }
  else if (mob->type == MOB_LICH && summon_minions(mob))
  {
    // nothing
  }
  else if (ob &&
      (mob->type == MOB_GNOBLIN ||
       (mob->type == MOB_EYE && rand() % 3 == 0) ||
       (mob->type == MOB_LICH && rand() % 4 == 0))
    )
  {
    int dist;

    dist = mob->x - player->x;

    if (dist < 0) dist *= -1;

    if (mob->type == MOB_GNOBLIN && dist < 20 && rand() % 3 == 0)
    {
      // Move away from the player
      if (player->x < mob->x)
	mob_walk(mi, mob->steps);
      else
	mob_walk(mi, mob->steps * -1);
    }
    else
    {
      if (player->x < mob->x)
      {
	mob->flip = true;
	shoot_missile(mob, -1);
      }
      else
      {
	mob->flip = false;
	shoot_missile(mob, +1);
      }
    }
  }
  else
  {
    if (ob && mob->type == MOB_EVILTREE)
    {
      eviltree_logic(mob);
    }

    move_towards_player(mob);
  }

  return;
}



