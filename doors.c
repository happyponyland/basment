#include "basment.h"



int close_door(int y, int c_x)
{
  int dir = 0;

  if (gtile(y - 1, c_x - 3) == TL_DOOR_HF)
    dir = -1;
  else if (gtile(y - 1, c_x + 3) == TL_DOOR_HF)
    dir = +1;

  if (dir == 0)
    return -1;

  if (anyone_there(y, c_x - 3) > 0 ||
      anyone_there(y, c_x - 0) > 0 ||
      anyone_there(y, c_x + 3) > 0)
  {
    return 1;
  }
      
  stile(y - 0, c_x + dir * 3, TL_VOID);
  stile(y - 1, c_x + dir * 3, TL_VOID);
  stile(y - 2, c_x + dir * 3, TL_VOID);
  stile(y - 3, c_x + dir * 3, TL_VOID);

  stile(y - 0, c_x + dir * 2, TL_DOOR);
  stile(y - 1, c_x + dir * 2, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir * 2, TL_DOOR);
  stile(y - 3, c_x + dir * 2, TL_DOOR);

  draw_board(); mpause();

  stile(y - 0, c_x + dir * 2, TL_VOID);
  stile(y - 1, c_x + dir * 2, TL_VOID);
  stile(y - 2, c_x + dir * 2, TL_VOID);
  stile(y - 3, c_x + dir * 2, TL_VOID);

  stile(y - 0, c_x + dir, TL_DOOR);
  stile(y - 1, c_x + dir, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir, TL_DOOR);
  stile(y - 3, c_x + dir, TL_DOOR);

  draw_board(); mpause();

  stile(y - 0, c_x, TL_DOOR);
  stile(y - 1, c_x, TL_DOOR);
  stile(y - 2, c_x, TL_DOOR);
  stile(y - 3, c_x, TL_DOOR);

  stile(y - 0, c_x + dir, TL_VOID);
  stile(y - 1, c_x + dir, TL_VOID);
  stile(y - 2, c_x + dir, TL_VOID);
  stile(y - 3, c_x + dir, TL_VOID);

  stile(y - 1, c_x - 1, TL_DOOR_HL);
  stile(y - 1, c_x + 1, TL_DOOR_HR);

  stile(y, c_x - 2, TL_DOOR_BLOCK);
  stile(y, c_x + 2, TL_DOOR_BLOCK);

  // Re-add door open triggers
  stile(y, c_x - 5, TL_DOOR_L);
  stile(y, c_x + 5, TL_DOOR_R);

  // Re-add door stops so they block enemies
  stile(y, c_x - 2, TL_DOOR_BLOCK);
  stile(y, c_x + 2, TL_DOOR_BLOCK);

  draw_board();

  return 0;
}



void open_door(int dir)
{
  int c_x;
  int y;

  recenter(true);

  y = player->y;

  c_x = player->x + dir * 5;

  stile(y, c_x - 5, TL_DOOR_OPEN_L);
  stile(y, c_x + 5, TL_DOOR_OPEN_R);
  
  // Remove handle
  stile(y - 1, c_x - dir, TL_VOID);

  stile(y - 0, c_x, TL_DOOR_SIDE);
  stile(y - 1, c_x, TL_DOOR_SIDE);
  stile(y - 2, c_x, TL_DOOR_SIDE);
  stile(y - 3, c_x, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir, TL_DOOR);
  stile(y - 1, c_x + dir, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir, TL_DOOR);
  stile(y - 3, c_x + dir, TL_DOOR);

  draw_board(); mpause();
  
  stile(y - 1, c_x, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir, TL_DOOR_SIDE);
  stile(y - 2, c_x + dir, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 2, TL_DOOR);
  stile(y - 1, c_x + dir * 2, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir * 2, TL_DOOR);
  stile(y - 3, c_x + dir * 2, TL_DOOR);

  draw_board(); mpause();

  stile(y - 1, c_x + dir, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 2, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir * 2, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 3, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir * 3, TL_DOOR_HF);
  stile(y - 2, c_x + dir * 3, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir * 3, TL_DOOR_SIDE);

  // Remove door stop so enemies can pass through open doors
  // The other side has already been overwritten by the open door itself
  stile(y, c_x - dir * 2, TL_VOID);

  draw_board();

  return;
}
