#include <time.h>
#include <ctype.h>

#ifndef _WIN32
#include <pwd.h>
#include <unistd.h> /* for getlogin() */
#endif

#include "basment.h"
#include "map.h"


/*
  Sets up a new player structure
*/
void new_player()
{
  player = &game->mob[0];
  player->type = MOB_PLAYER;
  player->w = 1;
  player->counter = 0;
  player->speed = 10;
  player->hp = 40;
  player->steps = 5;

  player->strength = 1;

  player->shd_type = SHD_NONE;
  player->armor_type = SHD_NONE;
  give_weapon(WPN_DAGGER);

  //give_weapon(WPN_GLASS);
  //give_armor(ARMOR_DRAGON);
  
  game->player_gold = 0;
  game->player_level = 1;
  game->player_exp = 0;
  game->player_tnl = 100;
  game->piety = 0;
  game->sacrifice = 0;
  game->has_map = false;

  game->max_floor = 1;
  game->game_started = time(NULL);
  game->turns = 0;
  
  game->hallucination = 0;
  game->scrying = false;

  game->skill_lockpick = false;
  game->skill_detect_traps = false;

  shuffle_books();

  return;
}


/* Player control */
void player_turn()
{
  int input;
  int tile_below;
  int tile_feet;

  game->turns++;

  if (game->hallucination)
  {
    game->hallucination--;

    if (game->hallucination == 0)
    {
      draw_board();

      pwait("THE HALLUCINATION ENDS\n\n"
	    "WELL, THAT WAS INTERESTING");

      give_exp((rand() % 5) * 100);
    }
  }

  /*
    If we haven't fought anything for a few turns, the enemy health
    bar will disappear.
  */
  if (enemy_bar_time == 0)
  {
    enemy_bar = -1;
    draw_bars();
  }
  else
    enemy_bar_time--;

retry:

  /* Refresh viewport and get player input. */
  draw_board();
  input = getch();
  
  /* lowmsg should only remain for one turn */
  lowmsg[0] = '\0';
  draw_lowmsg();
 
  /* What is below the player? */
  tile_below = gtile(player->y + 1, player->x);
  tile_feet = gtile(player->y, player->x);
  
  if (input == 'Q')
  {
    game_over(NULL, false);
  }
  else if ((input == KEY_DOWN || input == key_down) &&
	   tile_below == TL_LADDER_M)
  {
    climb_ladder(+1);
  }
  else if ((input == KEY_UP || input == key_up) &&
	   tile_feet == TL_LADDER_M)
  {
    climb_ladder(-1);
  }
  else if ((input == KEY_DOWN || input == key_down) &&
	   !player->webbed &&
	   (water_join(tile_below) ||
	    tile_below == TL_SURFACE/* ||
				       tile_feet == TL_UW_BELOW_BRIDGE*/))
  {
    climb_ladder(+1);
  }
  else if ((input == KEY_UP || input == key_up) &&
	   !player->webbed &&
	   water_join(tile_feet) &&
	   !interesting(tile_feet))
  {
    climb_ladder(-1);
  }
  else if (input == 'm' || input == 'M')
  {
  redraw_cellmap:
    draw_cellmap();

    input = getch();
    
    if (cheat_mode &&
	(input == 'f' || input == 'F'))
    {
      flip_automap();
      goto redraw_cellmap;
    }
    
    clear();
    draw_frames();
    draw_bars();
    draw_stats();
    draw_board();
    
    goto retry;
  }
  else if (input == 'X' && cheat_mode)
  {
    learn_detect_traps();
    game->has_torch = true;
//    game->has_scuba = true;
    player->hp += 30;
    player->speed += 3;
    player->strength += 3;
    give_weapon(WPN_SWORD);
    give_armor(SHD_MAGIC);
    give_armor(ARMOR_MAGIC);
    fill_automap(2);
    game->player_gold += 500;
    draw_stats();
    draw_bars();
    goto retry;
  }
  else if (input == 'T' && cheat_mode)
  {
    debug_teleport();
    clear();
    draw_frames();
    draw_bars();
    draw_stats();
    draw_board();
  }
  else if ((input == KEY_UP || input == key_up) &&
	   interesting(tile_feet))
  {
    if (interact() == false)
      goto retry;
  }
  else if (input == KEY_RIGHT || input == key_right)
  {
    if (ladder_flip(+1))
      goto retry;

    player->flip = false;
    try_to_breathe();
    player_move(1);
  }
  else if (input == KEY_LEFT || input == key_left)
  {
    if (ladder_flip(-1))
      goto retry;
    
    player->flip = true;
    try_to_breathe();
    player_move(-1);
  }
  else if (input == 's' && cheat_mode)
  {
    char line[200];
    sprintf(line, "YOU'RE SCORE: %d", calculate_score());
    pwait(line);
    draw_board();
  }
  else if (input == '?' || input == KEY_F(1) || input == KEY_HELP)
  {
    mob_text(player, "HELP!");
    goto retry;
  }
  else if (input == ' ')
  {
    // If the player has a shield, raise it for a few turns.

    try_to_breathe();

    if (game->weapon == WPN_BOW)
    {
      if (game->player_gold <= 0)
      {
	pwait("YOUR BROKE");
      }
      else if (damage_weapon(1)) // Might break
      {
      }
      else
      {
	game->player_gold--;
	draw_stats();

	snprintf(lowmsg, DEFLEN, "YOU SHOOT");
	draw_lowmsg();
	
	shoot_missile(0, (player->flip ? -1 : +1));
      }
    }
    else if (player->shd_type)
    {
      snprintf(lowmsg, DEFLEN, "YOU DEFEND");
      player->shd_up = 5;
      draw_board();
    }
    else
      snprintf(lowmsg, DEFLEN, "YOU WAIT");

    draw_lowmsg();
  }
  else
  {
    /* Invalid input! */
    goto retry;
  }

  return;
}



/**
   Checks if player is standing at the top or bottom of a ladder and
   tries to change direction. This will only make them flip and remain
   in place, then return true.
*/
int ladder_flip(int dir)
{
  if (gtile(player->y,     player->x) == TL_LADDER_M ||
      gtile(player->y + 1, player->x) == TL_LADDER_M)
  {
    if ((player->flip == true  && dir == +1) ||
	(player->flip == false && dir == -1))
    {
      player->flip = !player->flip;
      return true;
    }
  }

  return false;
}




void debug_teleport(void)
{
  int i;

  int x;
  int y;

  x = player->x / CELL_TO_TILES;
  y = player->y / FLOOR_H;

  if (y >= 24)
    automap_view_y = 24;
  else
    automap_view_y = 0;

  while (1)
  {
    draw_cellmap();
    mvaddch(y - automap_view_y, x, 'X' | A_BOLD);
    refresh();

    i = getch();

    if (i == ' ')
    {
      return;
    }
    else if (i == '\n')
    {
      player->x = ((float)x + 0.5f) * CELL_TO_TILES;
      player->y = y * FLOOR_H + FLOOR_Y - 1;
      view_y = y * FLOOR_H;
      recenter(false);
      return;
    }
    else if (i == KEY_DOWN || i == key_down)
    {
      if (y == 23)
	flip_automap();

      if (y < MAX_FLOORS - 1)
	y++;
    }
    else if (i == KEY_UP || i == key_up)
    {
      if (y == 24)
	flip_automap();

      if (y > 0)
	y--;
    }
    else if (i == KEY_RIGHT || i == key_right)
    {
      if (x < CELLS_W)
	x++;
    }
    else if (i == KEY_LEFT || i == key_left)
    {
      if (x > 0)
	x--;
    }
  }
  
  return;
}



/*
  Tries to move the player in DIR (positive for right, negative for
  left). If we bump into an enemy we will attack it.
*/
int player_move(int dir)
{
  int speed;
  int old_speed;
  int x_off;
  int i;
  int new_x;
  int moved = 0;
  int tile_below;
  int tile_feet;
  int steps;
//  int underwater = false;

  /*
    Figure out in which direction we want to move, and how far off
    the player center we want to search for obstacles.
  */
  if (dir > 0)
    speed = +1;
  else
    speed = -1;

  old_speed = speed;
  
  x_off = speed * 2;
  
  /*
    One step at a time. We stop if the player runs into an obstacle
    (blocking wall) or passes a point of interest (loot, etc).
  */

  steps = player->steps;

//  if (gtile(player->y, player->x) == TL_WATER)
  if (player_underwater())
  {
    //underwater = true;
    steps = UNDERWATER_STEPS;
  }

  if (player->webbed == 1)
    player->webbed = 0;
    
  if (player->webbed)
  {
    speed = 0;
    player->webbed--;
  }

  for (i = 0; i < steps; i++)
  {
    new_x = player->x + x_off + speed;

    if (new_x <= 0 || new_x >= MAP_W - 1)
      break;

    int n_t;

    n_t = gtile(player->y, new_x);

    // Walls
    if (n_t > TL_BLOCKING && n_t != TL_DOOR_BLOCK)
      break;

    // If there's an enemy in the way, attack it.
    if (melee(player, old_speed))
    {
      return moved;
    }

    tile_feet = gtile(player->y, player->x);

    if (tile_feet == TL_DOOR_L && speed > 0)
    {
      open_door(+1);
      steps += 10;
      //return 1;
    }
    else if (tile_feet == TL_DOOR_R && speed < 0)
    {
      open_door(-1);
      steps += 10;
      //return 1;
    }
    else if (tile_feet == TL_DOOR_OPEN_L && player->flip)
    {
      if (close_door(player->y, player->x + 5) == 0)
	return 1;
    }
    else if (tile_feet == TL_DOOR_OPEN_R && !player->flip)
    {
      if (close_door(player->y, player->x - 5) == 0)
	return 1;
    }
    
    /*
      Move (we don't use new_x since that is the edge of the player,
      we are moving the center)
    */
    player->x += speed;

    // Update viewport
    draw_board();

    update_automap();

    // Check if there is anything interesting beneath the player
    
    tile_below = gtile(player->y + 1, player->x);
    tile_feet = gtile(player->y, player->x);

    if (tile_below == TL_CHASM      ||
	tile_below == TL_TRAPDOOR_M ||
	tile_below == TL_LADDER_M   ||
	tile_feet  == TL_STOP       ||
	tile_feet  == TL_LADDER_M   ||
//	tile_feet  == TL_DOOR_L     ||
//	tile_feet  == TL_DOOR_R     ||
	is_trap(tile_feet) ||
	interesting(tile_feet))
    {
      break;
    }
    
    // There isn't; slight delay to give the feeling of animation
    spause();
  }
  
  // Recenter player if needed
  recenter(true);

  if (trap_sprung(tile_feet))
  {
  }
  else if (tile_below == TL_TRAPDOOR_M || tile_below == TL_CHASM)
  {
    bool fell_through = false;

    recenter(false);

    // Repeat this in case we land on a new trapdoor
    do
    {
      if (tile_below == TL_TRAPDOOR_M)
      {
	fell_through = trapdoor();

	if (!fell_through)
	  break;
      }
      
      player_fall();

      tile_below = gtile(player->y + 1, player->x);
    } while (tile_below == TL_TRAPDOOR_M);
  }

  if (tile_feet == TL_P_NPC1 ||
      tile_feet == TL_P_NPC2 ||
      tile_feet == TL_P_NPC3 ||
      tile_feet == TL_P_NPC4 ||
      tile_feet == TL_P_NPC5 ||
      tile_feet == TL_P_NPC_SCUBA ||
      tile_feet == TL_P_NPC_SUSHI)
  {
    interact();
  }
  else
  {
    /*
      Instruct the player how to access points of interest at its
      current location
    */
    feet_instruction(gtile(player->y, player->x));
  }

  return moved;
}


/*
  Recenters the viewport horizontally around the player. If PREEMPTIVE
  is true it will try to move the viewport so it displays more of what
  is in front of the player than behind. If PREEMPTIVE is false it
  will _always_ recenter the viewport, even if the player isn't near
  the edge. Returns true if the viewport was moved and a screen update
  is recommended.
*/
bool recenter(bool preemptive)
{
  int temp;

  if (/*!preemptive ||*/
      player->x - view_x > BOARD_W - 15 ||
      player->x - view_x <= 15)
  {
    temp = player->x - (BOARD_W / 2);

    if (preemptive)
    {
      if (player->flip)
	temp -= 16;
      else
	temp += 15;
    }

    view_x = MAX(0, MIN(temp, MAP_W - BOARD_W - 1));
  }
  
  return false;
}


/*
  Gives the player EXP experience; levels up if TNL is reached.
*/
void give_exp(int exp)
{
  char line[DEFLEN];
  int attr;

  game->player_exp += exp;

  draw_stats();

  // Chance of multiple level ups; keep doing this until we are satisfied

  while (game->player_exp >= game->player_tnl)
  {
    game->player_level++;
    game->player_tnl *= 2;

    // Show what just happened, before prompting
    draw_stats();

    attr = rand() % 4;

    switch(attr)
    {
    case 0:
      snprintf(line, DEFLEN,
	       "YOU ARE NOW LEVEL %d\n\n"
	       "YOU FEEL QUICKER",
	       game->player_level);
      break;

    case 1:
      snprintf(line, DEFLEN,
	       "YOU ARE NOW LEVEL %d\n\n"
	       "YOU FEEL STRONGER",
	       game->player_level);
      break;

    default:
      snprintf(line, DEFLEN,
	       "YOU ARE NOW LEVEL %d",
	       game->player_level);
      break;
    }

    pwait(line);

    if (attr == 0)
      change_pl_sp(1 + rand() % 3);
    else if (attr == 1)
      change_pl_st(1);

    draw_board();

    draw_stats();

    refill_hp(LEVEL_UP_HP_BOOST);
  }

  return;
}



/*
  Makes the player climb a ladder in DIR (positive for down, negative
  for up)
 */
void climb_ladder(int dir)
{
  int off = 0;
  int old_floor;
  int swimming;
  int dist;
  int tile_feet;
  int tile_below;

  tile_feet  = gtile(player->y,     player->x);
  tile_below = gtile(player->y + 1, player->x);

  recenter(false);

  old_floor = game->current_floor;

  if (dir == -1 && water_join(tile_feet))
  {
    if (!water_join(gtile(player->y - 6, player->x)))
      return;
    
    swimming = true;
    
    if (!water_join(gtile(player->y - 6, player->x - 1)))
      player->x++;
    else if (!water_join(gtile(player->y - 6, player->x + 1)))
      player->x--;
  }
  else if (dir == +1 &&
	   ((tile_below == TL_SURFACE) ||
	    (tile_feet  == TL_UW_BELOW_BRIDGE) ||
	    water_join(tile_below)))
  {
    if (tile_below == TL_SURFACE ||
	tile_feet  == TL_UW_BELOW_BRIDGE)
    {
      take_breath(player);
      force_breath_bar(player);
    }

    if (tile_feet != TL_UW_BELOW_BRIDGE)
    {
      if (!water_join(gtile(player->y + FLOOR_H, player->x)))
	return;

      if (!water_join(gtile(player->y + 3, player->x)))
	return;
    }
    
    swimming = true;

    if (!water_join(gtile(player->y + 3, player->x - 1)))
      player->x++;
    else if (!water_join(gtile(player->y + 3, player->x + 1)))
      player->x--;
  }
  else
  {
    swimming = false;
  }

  if (swimming)
  {
    dist = FLOOR_H;
    off = 0;
    
    if (tile_feet == TL_UW_BELOW_BRIDGE)
      dist = FLOOR_H - 5;
  }
  else
  {
    // It's a regular ladder
    
    // When moving up we need to stop at the right place

    dist = 999;
    
    if (dir == -1)
      off = +1;
  }

  while (dist--)
  {
    if (!swimming && gtile(player->y + off + dir, player->x) != TL_LADDER_M)
      break;

    if (swimming &&
	dir == -1 &&
	gtile(player->y, player->x) == TL_UW_BELOW_BRIDGE)
    {
      break;
    }
    
    // Move player on map and viewport; player always remains centered
    view_y += dir;
    player->y += dir;
    
    update_automap();
    
    // Play a small animation
    if (player->y % 2)
      player->flags = GFX_HUMAN_CLIMB1;
    else 
      player->flags = GFX_HUMAN_CLIMB2;

    if (swimming && dir == +1)
      player->flags |= GFX_HUMAN_DIVE;
    
    draw_board();
    mpause();
  }

  if (swimming && dir == -1)
  {
//    if (!player_underwater())
//    {
    draw_bars();
//    }
  }
  
  // We should now be on a new floor
  calculate_floor();

  // Add a random monster on the level we just left
  // Reduced chance if we're swimming
  if (!swimming || rand() % 4 == 0)
  {
    add_another_monster(old_floor);
  }
  
  // Throw away anything entered by the player while they were climbing
  flush_input();

  // Reset animation 
  player->flags = 0;

  // Display where we ended up
  draw_stats();

  // Check for traps at the new location (usually a net trap)
  trap_sprung(gtile(player->y, player->x));
  
  return;
}


/*
  Ends the game. If CAUSE is provided
  it will be displayed before exiting.
*/
void game_over(char * cause, bool won)
{
  char line[DEFLEN];
  char morgue[4000];
  bool any_skill;
  long score;
  score_t sheet;
  
  if (won)
  {
    game->won = true;
    game->win_streak++;
  }
  else
  {
    // Don't give any bonus if player died
    game->win_streak = 0;
  }

  make_score(&sheet);
  score = calc_score(&sheet);

  if (cause != NULL || won)
  {
    if (cause)
    {
      snprintf(line, DEFLEN,
	       "%s\n\n - GAME OVER -", cause);
      pwait(line);
    }

    if (!won)
    {
      strcpy(morgue, "REST IN PEACE, BRAVE ADVENTURER\n\n");

      // Find the end of the morgue string 
      char * t;
      for (t = morgue; *t != '\0'; t++) { }

      strcat(t, cause);
      
      // Replace newlines in death message with spaces
      char * p;
      for (p = t; *p != '\0'; p++) { if (*p == '\n') *p = ' '; }
      
      snprintf(line, DEFLEN, "\nON FLOOR %d ", game->current_floor);
      strcat(morgue, line);
      
      if (game->max_floor > game->current_floor)
      {
	snprintf(line, DEFLEN, "(MAX %d) ", game->max_floor);
	strcat(morgue, line);
      }
    }
    else
    {
      strcpy(morgue, "GLORY IS YOURS THIS DAY!!\n\nYOU DEFEATED THE ARCHDEMON ");
    }

    snprintf(line, DEFLEN, "AFTER %d TURNS\n\n", game->turns);
    strcat(morgue, line);

    snprintf(line, DEFLEN, "YOU WERE LEVEL %d WITH %d EXPERIENCE\n\n",
	     game->player_level, game->player_exp);
    strcat(morgue, line);

    if (won)
    {
      snprintf(line, DEFLEN, "YOU HAD:\n");
      strcat(morgue, line);
    }
    else
    {
      snprintf(line, DEFLEN, "WHEN YOU DIED, YOU HAD:\n");
      strcat(morgue, line);
    }

    bool anything = false;

    if (game->player_gold)
    {
      snprintf(line, DEFLEN, "  %d GOLD PIECES\n", game->player_gold);
      strcat(morgue, line);
      anything = true;
    }

    if (game->weapon)
    {
      if (game->weapon == WPN_RUNESWORD)
	snprintf(line, DEFLEN, "  THE FABLED *RUNESWORD* !!!\n");
      else
	snprintf(line, DEFLEN, "  A %s\n", weapon_name[game->weapon]);
      
      strcat(morgue, line);
      anything = true;
    }

    if (player->armor_type || player->shd_type)
    {
      if (player->armor_type && player->shd_type)
	snprintf(line, DEFLEN, "  %s AND A %s\n", armor_name[player->armor_type], armor_name[player->shd_type]);
      else if (player->armor_type)
	snprintf(line, DEFLEN, "  %s\n", armor_name[player->armor_type]);
      else if (player->shd_type)
	snprintf(line, DEFLEN, "  A %s\n", armor_name[player->shd_type]);
      
      strcat(morgue, line);
      anything = true;
    }

    if (game->has_map)
    {
      strcat(morgue, "  A MAP OF THE DUNGEON\n");
      anything = true;
    }

    if (game->has_scuba)
    {
      strcat(morgue, "  SCUBA GEAR\n");
      anything = true;
    }

    if (game->has_torch)
    {
      strcat(morgue, "  A TORCH\n");
      anything = true;
    }
    
    if (!anything)
      strcat(morgue, "  NOTHING AT ALL\n");

    strcat(morgue, "\n");

    any_skill = false;

    line[0] = '\0';

    if (game->skill_lockpick)
    {
      if (any_skill) strcat(line, ", ");
      strcat(line, "LOCKPICKING");
      any_skill = true;
    }

    if (game->skill_detect_traps)
    {
      if (any_skill) strcat(line, ", ");
      strcat(line, "DETECT TRAPS");
      any_skill = true;
    }

    if (line[0] != '\0')
    {
      strcat(morgue, "YOU HAD THE FOLLOWING SKILL(S):\n  ");
      strcat(morgue, line);
      strcat(morgue, "\n\n");
    }

    strcat(morgue, "YOU PLAYED FOR");

    long play_time;

    play_time = time(NULL) - game->game_started;

    if (play_time >= 60 * 60)
    {
      snprintf(line, DEFLEN, " %ld HOURS", play_time / 3600);
      strcat(morgue, line);
      play_time %= 3600;
    }

    if (play_time >= 60)
    {
      snprintf(line, DEFLEN, " %ld MINUTES", play_time / 60);
      strcat(morgue, line);
      play_time %= 60;
    }

    if (play_time >= 0)
    {
      snprintf(line, DEFLEN, " %ld SECONDS", play_time);
      strcat(morgue, line);
    }

//    snprintf(line, DEFLEN, "\n\nFINAL SCORE: %ld", score);
//    strcat(morgue, line);

    clear();
    mvaddstr(1, 1, morgue);

    refresh();

    opause();
    
    list_score(&sheet);

    move(20, 28);
    printw("FINAL SCORE: %ld", score);
    
    move(22, 14);
    addstr("-- THANK YOU FOR PLAYING -- PRESS ENTER TO CONTINUE --");
//    strcat(morgue, "\n\n\n");

    while (getch() != '\n') { }
  }

  int hiscore_place = 0;
  char * p;
  char plname[PLNAME_LEN + 1];
  char scause[DEFLEN];
  
  if (won || cause)
  {
    if (cheat_mode)
    {
      erase();
      mvaddstr(3, 5, "NO HIGHSCHORE WILL BE RECORDED IN CHEAT MODE!!!");
      refresh();
      getch();
      goto restart_prompt;
    }
  
    if (score > 0)
      get_player_name(plname, PLNAME_LEN);
    
    if (cause)
    {
      strcpy(scause, cause);

      p = scause;
      
      while (*p != '\0')
      {
	if (*p == '\n')
	  *p = ' ';
	
	p++;
      }

      p = scause;

      if (strncmp(p, "YOU WERE ", 9) == 0)
	p += 9;
      else if (strncmp(p, "YOU ", 4) == 0)
	p += 4;
      
      snprintf(line, DEFLEN, "%s ON FLOOR %d ", p, game->current_floor);
    }
    else
    {
      strcpy(line, "DEFEATED THE ARCH-DEMON");
    }
  }

  if (won || cause)
  {
    if (score > 0)
    {
      hiscore_place = add_highscore(score, plname, line);
    }

    show_highscore(HIGHSCORE_TOP_ENTRIES, hiscore_place, true);
  }

restart_prompt:
  if (!cause && !won)
    goto the_end;

  erase();
  mvaddstr(5, 5, "WOULD YOU LIKE TO PLAY AGAIN? (Y/N) ");
  refresh();
  
  int g;
  
  while (true)
  {
    g = getch();

    if (g == 'y' || g == 'Y' || g == '\n')
    {
      erase();
      longjmp(restart_game, 1);
    }
    else if (g == 'n' || g == 'N' || g == ' ')
    {
      goto the_end;
    }    
  }

  the_end:
  quit_game();
  exit(0);
}



void get_player_name(char * dest, int maxlen)
{
  int pos = 0;
  int in;
  int i;

  curs_set(1);

  dest[0] = '\0';

  #ifndef _WIN32
  if (!forcenameprompt)
  {
    if (getlogin() != NULL)
      strncpy(dest, getlogin(), maxlen);
    else
    {
      struct passwd * pwd;
      
      pwd = getpwuid(getuid());
      
      if (pwd != NULL)
	if (pwd->pw_name != NULL)
	  strncpy(dest, pwd->pw_name, maxlen);
    }
  }
  #endif

  for (pos = 0; pos < maxlen; pos++)
  {
    dest[pos] = toupper(dest[pos]);

    if (dest[pos] == '\0')
      break;
  }

  clear();

  mvaddstr(3, 5, "PLEASE ENTER YOUR NAME FOR THE HIGHSCORE LIST");
  
  while (1)
  {
    move(5, 5);

    for (i = 0; i < pos; i++)
      addch(dest[i]);

    clrtoeol();

    refresh();

    in = getch();

    if (in == '\n')
    {
      if (pos == 0)
	strcpy(dest, "ANON");
      else
	dest[pos] = '\0';

      curs_set(0);
      return;
    }
    else if (in == KEY_BACKSPACE && pos > 0)
    {
      pos--;
    }
    else if (isalnum(in) && pos < maxlen)
    {
      dest[pos] = toupper(in);
      pos++;
    }
  }
}



/*
  Removes AMOUNT of players gold. If the player doesn't have enough
  gold, nothing is subtracted and false is returned. If there was
  enough, true is returned.
*/
bool spend_gold(int amount)
{
  if (game->player_gold < amount)
    return false;

  game->player_gold -= amount;

  return true;
}



/* Gives the player AMOUNT gold, displays a message */
void give_gold(char * msg, int amount)
{
  char line[DEFLEN];
  char * none = "";

  if (msg == NULL)
    msg = none;
  
  snprintf(line, DEFLEN, "%sYOU FIND %d GOLD", msg, amount);
  game->player_gold += amount;

  // For score
  game->total_gold_earned += amount;

  // Update screen before popup
  draw_stats();
  pwait(line);

  return;
}


/*
  Returns false if the player avoided the trapdoor, true if it fell through.
*/
bool trapdoor()
{
  if (rand() % 3)
  {
    pwait("YOU NARROWLY AVOID\n"
	  "    A TRAPDOOR    ");

    return false;
  }
  
  pwait("A TRAPDOOR OPENS\n"
	"  BENEATH YOU!  ");
  
  stile(player->y + 1, player->x - 1, TL_VOID);
  draw_board(); lpause();
  
  stile(player->y + 1, player->x, TL_CHASM);
  draw_board(); lpause();

  stile(player->y + 1, player->x + 1, TL_VOID);
  draw_board(); lpause();

  return true;
}



/*
  Makes the player fall down until it makes contact with a blocking
  tile.
*/
void player_fall()
{
  int tile_below;
  int next_below;

  while (true)
  {
    tile_below = gtile(player->y + 1, player->x);
    next_below = gtile(player->y + 2, player->x);

    if (next_below == TL_SURFACE)
    {
      // Fake an additional tile
      player->y++;
      view_y++;
      player->flags = (player->y % 2 ? GFX_HUMAN_FALL1 : GFX_HUMAN_FALL2);
		       
      stile(player->y + 1, player->x, TL_FAKESURFACE);
      draw_board();
      lpause();

      // Since we don't actually change y position, just the tile type
      // (that offsets the drawing function) we need to fake an extra arm flail
      player->flags = ((player->y+1) % 2 ? GFX_HUMAN_FALL1 : GFX_HUMAN_FALL2);
      stile(player->y + 1, player->x, TL_SURFACE);
      
      draw_board_norefresh();
      mvwaddch(board, player->y - 2 - view_y, player->x - 2 - view_x, '\\' | COLOR_PAIR(PAIR_CYAN));
      mvwaddch(board, player->y - 2 - view_y, player->x + 2 - view_x, '/' | COLOR_PAIR(PAIR_CYAN));
      mvwaddch(board, player->y - 1 - view_y, player->x - 3 - view_x, '\\' | COLOR_PAIR(PAIR_CYAN));
      mvwaddch(board, player->y - 1 - view_y, player->x + 3 - view_x, '/' | COLOR_PAIR(PAIR_CYAN));
      wrefresh(board);
      opause();

      break;
    }
    else if (tile_below >= TL_BLOCKING)
      break;
    
    if (tile_below == TL_SPIKE)
    {
      stile(player->y + 1, player->x - 1, TL_REDSPIKE);
      stile(player->y + 1, player->x,     TL_REDSPIKE);
      stile(player->y + 1, player->x + 1, TL_REDSPIKE);

      player->type = MOB_GORE;

      draw_board();

      game_over("YOU WERE IMPALED\n"
		"ON SPIKES", false);
    }
      
    player->y += 1;
    view_y += 1;
    player->flags = (player->y % 2 ? GFX_HUMAN_FALL1 : GFX_HUMAN_FALL2);

    draw_board();
    
    lpause();
  }

  player->flags = 0;

  calculate_floor();
  draw_stats();
  draw_board_norefresh();

  flush_input();

  trap_sprung(gtile(player->y, player->x));

  return;
}



/*
  Figures out which floor the player is on.
*/
void calculate_floor()
{
  game->current_floor = 1 + player->y / FLOOR_H;

  if (game->current_floor > game->max_floor)
    game->max_floor = game->current_floor;

  return;
}



void intro()
{
  player->y -= 2;
  player->type = MOB_NONE;

  draw_board();
  opause();

  stile(player->y - 2, player->x, TL_SKY);
  stile(player->y - 1, player->x, TL_SKY);
  stile(player->y - 0, player->x, TL_SKY);
  draw_board();
  lpause();

  stile(player->y - 2, player->x - 1, TL_SKY);
  stile(player->y - 1, player->x - 1, TL_SKY);
  stile(player->y - 0, player->x - 1, TL_SKY);

  stile(player->y - 2, player->x + 1, TL_SKY);
  stile(player->y - 1, player->x + 1, TL_SKY);
  stile(player->y - 0, player->x + 1, TL_SKY);
  draw_board();

  opause();

  player->type = MOB_PLAYER;
  draw_board();
  opause();

  player->y++;
  draw_board();
  lpause();
  
  player->y++;
  draw_board();
  lpause();
  
  stile(player->y - 4, player->x - 1, TL_ENTR_DOOR);
  stile(player->y - 3, player->x - 1, TL_ENTR_DOOR);
  stile(player->y - 2, player->x - 1, TL_ENTR_DOOR);

  stile(player->y - 4, player->x + 1, TL_ENTR_DOOR);
  stile(player->y - 3, player->x + 1, TL_ENTR_DOOR);
  stile(player->y - 2, player->x + 1, TL_ENTR_DOOR);
  draw_board();
  lpause();

  stile(player->y - 4, player->x, TL_ENTR_DOOR);
  stile(player->y - 3, player->x, TL_ENTR_DOOR);
  stile(player->y - 2, player->x, TL_ENTR_DOOR);
  draw_board();
  lpause();

  stile(player->y - 4, player->x, TL_VOID);
  stile(player->y - 3, player->x, TL_VOID);
  stile(player->y - 2, player->x, TL_VOID);

  stile(player->y - 4, player->x - 1, TL_VOID);
  stile(player->y - 3, player->x - 1, TL_VOID);
  stile(player->y - 2, player->x - 1, TL_VOID);

  stile(player->y - 4, player->x + 1, TL_VOID);
  stile(player->y - 3, player->x + 1, TL_VOID);
  stile(player->y - 2, player->x + 1, TL_VOID);
  draw_board();
  lpause();

  stile(player->y - 1, player->x - 3, TL_VOID);
  stile(player->y - 1, player->x - 2, TL_VOID);
  stile(player->y - 1, player->x - 1, TL_VOID);
  stile(player->y - 1, player->x + 0, TL_VOID);
  stile(player->y - 1, player->x + 1, TL_VOID);
  stile(player->y - 1, player->x + 2, TL_VOID);
  stile(player->y - 1, player->x + 3, TL_VOID);
  draw_board();
  lpause();

  stile(player->y, player->x - 4, TL_VOID);
  stile(player->y, player->x - 3, TL_VOID);
  stile(player->y, player->x - 2, TL_VOID);
  stile(player->y, player->x - 1, TL_VOID);
  stile(player->y, player->x + 0, TL_VOID);
  stile(player->y, player->x + 1, TL_VOID);
  stile(player->y, player->x + 2, TL_VOID);
  stile(player->y, player->x + 3, TL_VOID);
  stile(player->y, player->x + 4, TL_VOID);

  flush_input();

  return;
}



/*
  Adds AMOUNT to player HP and animates the health bar filling up.
*/
void refill_hp(int amount)
{
  while (amount)
  {
    if (player->hp >= 100)
    {
      // No point in animating if the bar is full anyway 
      player->hp += amount;
      return;
    }

    amount--;
    player->hp++;

    draw_bars();

    // Don't pause if we have filled the last drop
    if (amount)
      spause();
  }

  return;
}



void learn_detect_traps()
{
  game->skill_detect_traps = true;
  
  gfx_map[TL_T_CAVEIN] = '^' | COLOR_PAIR(PAIR_RED) | A_REVERSE;
  gfx_map[TL_T_POISON] = '^' | COLOR_PAIR(PAIR_RED) | A_REVERSE;
  gfx_map[TL_T_UWNET]  = '^' | COLOR_PAIR(PAIR_RED) | A_REVERSE;
  gfx_map[TL_T_WEB]    = '^' | COLOR_PAIR(PAIR_RED) | A_REVERSE;

  return;
}



void change_pl_st(int change)
{
  if (change == 0)
    return;
  else if (change < 0)
    wattrset(stats, COLOR_PAIR(PAIR_RED) | A_BOLD | A_REVERSE);
  else
    wattrset(stats, COLOR_PAIR(PAIR_BROWN) | A_BOLD | A_REVERSE);

  player->strength = MAX(1, player->strength + change);

  wmove(stats, 1, BOARD_W - 7);
  wprintw(stats, " ST %2d", player->strength);

  wattrset(stats, 0);

  wrefresh(stats);

  lpause();
  
  return;
}



void change_pl_sp(int change)
{

  if (change == 0)
    return;
  else if (change < 0)
    wattrset(stats, COLOR_PAIR(PAIR_RED) | A_BOLD | A_REVERSE);
  else
    wattrset(stats, COLOR_PAIR(PAIR_BROWN) | A_BOLD | A_REVERSE);

  player->speed = MAX(1, player->speed + change);

  wmove(stats, 2, BOARD_W - 7);
  wprintw(stats, " SP %2d", player->speed);

  wattrset(stats, 0);

  wrefresh(stats);

  lpause();
  
  return;
}
