#ifndef _MOB_H_
#define _MOB_H_

#include <stdbool.h>
#include <stdint.h>

#define MAX_MOBS 300

typedef struct mob_t mob_t;

struct mob_t
{
  int index;

  int y;
  int x;
  int w;

  int article;

  bool flip;
  int type;
  int hp;

  int follow_floor;
  
  int attack_phase;

  int shd_type;
  int shd_up;

  int armor_type;

  int range;

  int speed;
  int counter;
  int steps;

  int strength;
  int damage;
  int attack_frames;

  int exp;

  bool alert;

  uint32_t flags;

  int gp;
};

#endif
