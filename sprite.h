#ifndef _SPRITE_H_
#define _SPRITE_H_

struct sprite_t
{
  char ch[9][7];
};

typedef struct sprite_t sprite_t;

#define MAX_SPRITES 100

extern sprite_t * sprlist[MAX_SPRITES];

#endif
