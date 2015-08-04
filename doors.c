#include "basment.h"



void open_door(int dir)
{
  int i;
  int c_x;
  int y;

  y = player->y;

  c_x = player->x + dir * 5;

  // Remove handle
  stile(y - 1, c_x - dir, TL_VOID);

  stile(y - 0, c_x, TL_DOOR_SIDE);
  stile(y - 1, c_x, TL_DOOR_SIDE);
  stile(y - 2, c_x, TL_DOOR_SIDE);
  stile(y - 3, c_x, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir, TL_DOOR);
//  stile(y - 1, c_x + dir, TL_DOOR);
  stile(y - 1, c_x + dir, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir, TL_DOOR);
  stile(y - 3, c_x + dir, TL_DOOR);

  draw_board();
  lpause();

  stile(y - 1, c_x, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir, TL_DOOR_SIDE);
  stile(y - 2, c_x + dir, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 2, TL_DOOR);
//  stile(y - 1, c_x + dir * 2, TL_DOOR);
  stile(y - 1, c_x + dir * 2, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir * 2, TL_DOOR);
  stile(y - 3, c_x + dir * 2, TL_DOOR);

  draw_board();
  lpause();

  stile(y - 1, c_x + dir, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 2, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir * 2, TL_DOOR_SIDE);

  stile(y - 0, c_x + dir * 3, TL_DOOR_SIDE);
//  stile(y - 1, c_x + dir * 2, TL_DOOR_SIDE);
  stile(y - 1, c_x + dir * 3, TL_DOOR_HF);
  stile(y - 2, c_x + dir * 3, TL_DOOR_SIDE);
  stile(y - 3, c_x + dir * 3, TL_DOOR_SIDE);


  draw_board();
  lpause();

  for (i = 0; i < 10; i++)
  {
    player->x += dir;
    draw_board();
    lpause();
  }

  stile(y - 0, c_x + dir * 3, TL_VOID);
  stile(y - 1, c_x + dir * 3, TL_VOID);
  stile(y - 2, c_x + dir * 3, TL_VOID);
  stile(y - 3, c_x + dir * 3, TL_VOID);

  stile(y - 0, c_x + dir * 2, TL_DOOR);
  stile(y - 1, c_x + dir * 2, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir * 2, TL_DOOR);
  stile(y - 3, c_x + dir * 2, TL_DOOR);

  draw_board();
  lpause();

  stile(y - 0, c_x + dir * 2, TL_VOID);
  stile(y - 1, c_x + dir * 2, TL_VOID);
  stile(y - 2, c_x + dir * 2, TL_VOID);
  stile(y - 3, c_x + dir * 2, TL_VOID);

  stile(y - 0, c_x + dir, TL_DOOR);
  stile(y - 1, c_x + dir, (dir > 0 ? TL_DOOR_HF : TL_DOOR_HF));
  stile(y - 2, c_x + dir, TL_DOOR);
  stile(y - 3, c_x + dir, TL_DOOR);

  draw_board();
  lpause();

  stile(y - 0, c_x, TL_DOOR);
  stile(y - 1, c_x, TL_DOOR);
//  stile(y - 1, c_x + dir, (dir > 0 ? TL_DOOR_HL : TL_DOOR_HR));
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

  draw_board();
//  opause();

  return;
}
