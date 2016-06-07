
#include "basment.h"


void ye_olde_bar()
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
	   "BARTENDER:\n"
	   "WHAT WOULD YOU LIKE?\n\n"
	   "  GRISLY BEER         (%d GOLD)\n"
	   "  ELFWEN WHINE        (%d GOLD)\n"
	   "  GNOBLIN MOONSHINE   (%d GOLD)",
	   COST_BEER, COST_WHINE, COST_MOONSHINE);
  
  sel = pchoose(line, 3, 3, leave);
  
  draw_board();

  switch (sel)
  {
  case 0:
    if (game->beer)
    {
      pwait("BARTENDER:\n"
	    "HEY! YOU HAVE ALREADY HAD ENOUGH!!");
      return;
    }

    cost = COST_BEER;
    break;
    
  case 1:
    if (game->whine)
    {
      pwait("BARTENDER:\n"
	    "HEY! YOU HAVE ALREADY HAD ENOUGH!!");
      return;
    }

    cost = COST_WHINE;
    break;
    
  case 2:
    if (game->moonshine)
    {
      pwait("BARTENDER:\n"
	    "HEY! YOU HAVE ALREADY HAD ENOUGH!!");
      return;
    }

    cost = COST_MOONSHINE;
    break;
    
  default:
    return;
  }

  if (spend_gold(cost) == false)
  {
    pwait("BARTENDER:\nHEY! CASH UP FRONT!!");
    return;
  }

  // Update gold
  draw_stats();

  switch (sel)
  {
  case 0:
    game->beer += 50 + rand() % 100;
    break;
    
  case 1:
    game->whine += 5 + rand() % 5;
    whine_now();
    break;
    
  case 2:
    game->moonshine += 10 + rand() % 40;
    game->blinded = game->moonshine;
    pwait("YOU CANNOT SEE!");
    break;
    
  default:
    break;
  }
 
  draw_board();
  
  return;
}



void whine_now()
{
  switch (rand() % 15)
  {
  case 0:  pwait("O, WOE IS ME");             break;
  case 1:  pwait("LIFE IS MISERY");           break;
  case 2:  pwait("I'M A FAILURE");            break;
  case 3:  pwait("NO ONE WILL EVER LOVE ME"); break;
  case 4:  pwait("LIFE SUCKS");               break;
  case 5:  pwait("I'M SO ALONE");             break;
  case 6:  pwait("IT'S ALL OVER NOW");        break;
  case 7:  pwait("I'M SUPER DEPRESSED");      break;
  case 8:  pwait("NOTHING MATTERS ANY MORE"); break;
  case 9:  pwait("EXISTANCE IS POINTLESS");   break;
  case 10: pwait("WHY SHOULD I GO ON?");      break;
  case 11: pwait("I WISH I WAS DEAD");        break;
  case 12: pwait("NO ONE LIKES ME");          break;
  case 13: pwait("WHY SHOULD I GO ON?");      break;
  case 14: pwait("WHY SHOULD I GO ON?");      break;
  }
  
  return;
}
