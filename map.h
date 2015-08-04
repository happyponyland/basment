#ifndef _MAP_H_
#define _MAP_H_

#include "mob.h"

#define BRANCH_DUNGEON  0
#define BRANCH_CRYPT    1
#define BRANCH_CAVE     2
#define BRANCH_ORGANIC  3
#define BRANCHES 4

#define BOOKS 11

typedef struct game_t game_t;

struct game_t
{
  bool won;

  int hallucination;
  bool scrying;

  int current_floor;

  uint16_t tile[MAP_H][MAP_W];

  char cell[MAX_FLOORS][CELLS_W];
  char branch[MAX_FLOORS][CELLS_W];
  char automap[MAX_FLOORS][CELLS_W];

  mob_t mob[MAX_MOBS];

  bool has_map;

  int weapon;
  int wpn_dur;

  int shd_dur;
  int armor_dur;

  int total_gold_earned;
  int monsters_killed;
  int traps_triggered;

  int player_gold;
  int player_level;
  int player_exp;
  int player_tnl;
  int piety;
  int sacrifice;

  bool skill_lockpick;
  bool skill_detect_traps;
  bool skill_appraisal;

  long game_started;
  int turns;
  int max_floor;

  int book[BOOKS];
  int next_book;
} * game;

int view_y;
int view_x;

typedef enum tile_t tile_t;



enum tile_t
{
  TL_VOID,
  TL_LADDER_L,
  TL_LADDER_R,
  TL_LADDER_M,
  TL_TRAPDOOR_M,
  TL_TRAPDOOR_S,
  TL_CHASM,
  TL_SPIKE,
  TL_REDSPIKE,

  TL_NPC,
  TL_P_NPC1,
  TL_P_NPC2,
  TL_P_NPC3,
  TL_P_NPC4,
  TL_P_NPC5,
  TL_P_ENTRANCE,

  TL_P_CORPSE,
  TL_P_SKELETON,
  TL_P_ALTAR,
  TL_P_CHEST,
  TL_P_FOUNTAIN,
  TL_P_IDOL,
  TL_P_COFFIN,
  TL_P_BOOKSHELF,
  TL_P_PORTAL,
  TL_P_ORB,
  TL_P_CAMP,
  TL_P_SWSTONE,
  TL_P_TABLET,

  TL_WOOD,
  TL_LOCK,

  TL_PORTAL_S_B,
  TL_PORTAL_S_L,
  TL_PORTAL_S_R,
  TL_PORTAL_L,
  TL_PORTAL_R,
  TL_PORTAL_T,
  TL_PORTAL_M,

  TL_ORB_L,
  TL_ORB_C,
  TL_ORB_R,
  TL_ORB_LU,
  TL_ORB_RU,
  TL_ORB_CU,
  TL_ORB_LIT,
  TL_ORB_DARK,

  TL_COFFIN_VL,
  TL_COFFIN_HL,
  TL_COFFIN_FILL,
  TL_COFFIN_TTEE,
  TL_COFFIN_RTEE,
  TL_COFFIN_LTEE,
  TL_COFFIN_BTEE,
  TL_COFFIN_UR,
  TL_COFFIN_UL,
  TL_COFFIN_CROSS1,
  TL_COFFIN_CROSS2,
  TL_COFFIN_LID_L,
  TL_COFFIN_LID_R,

  TL_IDOL_LARM,
  TL_IDOL_RARM,
  TL_IDOL_HEAD,
  TL_IDOL_HEAD_LIT,
  TL_IDOL_BODY,
  TL_IDOL_BASE,
  TL_IDOL_STAND_UL,
  TL_IDOL_STAND_UR,
  TL_IDOL_STAND_HL,
  TL_IDOL_STAND_VL,
  TL_IDOL_DEBRIS_1,
  TL_IDOL_DEBRIS_2,

  TL_POISON_L1,
  TL_POISON_L2,
  TL_POISON_L3,
  TL_POISON_R1,
  TL_POISON_R2,
  TL_POISON_R3,

  TL_SHELF_HL,
  TL_SHELF_VL,
  TL_SHELF_RTEE,
  TL_SHELF_LTEE,
  TL_SHELF_UL,
  TL_SHELF_UR,
  TL_SHELF_BOOK1,
  TL_SHELF_BOOK2,
  TL_SHELF_BOOK3,
  TL_SHELF_BOOK4,
  TL_SHELF_BOOK5,
  TL_SHELF_BOOK6,
  TL_SHELF_BOOK7,
  TL_SHELF_BOOK8,

  TL_BONE1,
  TL_BONE2,
  TL_BONE3,

  TL_CORPSE1,
  TL_CORPSE2,
  TL_CORPSE3,
  TL_CORPSE4,
  TL_CORPSE5,

  TL_GR_UR,
  TL_GR_UL,
  TL_GR_LTEE,
  TL_GR_RTEE,
  TL_GR_HL,
  TL_WH_VL,
  TL_WH_PLUS,
  TL_YDOT,
  TL_GR_LR,
  TL_GR_LL,
  TL_GR_BTEE,
  TL_GR_TTEE,
  TL_WH_LR,
  TL_WH_LL,
  TL_GR_VL,

  TL_BL_VL,
  TL_BL_TTEE,
  TL_BL_UR,
  TL_BL_UL,
  TL_FOUNT_BASE,

  TL_BR_UL,
  TL_BR_VL,
  TL_BR_UR,
  TL_BR_HL,

  TL_ENTR_DOOR,
  TL_STAIR_UL,
  TL_STAIR_UR,
  TL_STAIR_BTEE,
  TL_STAIR_HL,
  TL_SKY,

  TL_L_A,
  TL_L_B,
  TL_L_C,
  TL_L_D,
  TL_L_E,
  TL_L_F,
  TL_L_G,
  TL_L_H,
  TL_L_I,
  TL_L_J,
  TL_L_K,
  TL_L_L,
  TL_L_M,
  TL_L_N,
  TL_L_O,
  TL_L_P,
  TL_L_Q,
  TL_L_R,
  TL_L_S,
  TL_L_T,
  TL_L_U,
  TL_L_V,
  TL_L_W,
  TL_L_X,
  TL_L_Y,
  TL_L_Z,

  TL_BOULDER,

  TL_STALACTITE1,
  TL_STALACTITE2,
  TL_STALACTITE3,

  TL_ROOTS1,
  TL_ROOTS2,
  TL_ROOTS3,
  TL_ROOTS4,

  TL_NPC_LLEG,
  TL_NPC_RLEG,
  TL_NPC_TORSO,
  TL_NPC_HEAD,

  TL_T_CAVEIN,
  TL_T_POISON,
  TL_T_POISON_REV,
  TL_T_GORZOTH_R,
  TL_T_GORZOTH_L,

  TL_CAMP_FIRE,
  TL_CAMP_SPENT,
  TL_CAMP_STAND_T,
  TL_CAMP_STAND_B,
  TL_CAMP_SPIT1,
  TL_CAMP_SPIT2,
  TL_CAMP_SPIT3,
  TL_CAMP_MEAT1,
  TL_CAMP_MEAT2,
  TL_CAMP_MEAT3,

  TL_STOP,

  TL_DOOR,
  TL_DOOR_HL,
  TL_DOOR_HR,
  TL_DOOR_HF,
  TL_DOOR_L,
  TL_DOOR_R,
  TL_DOOR_SIDE,

  TL_SWSTONE_UL,
  TL_SWSTONE_UR,
  TL_SWSTONE_LR,
  TL_SWSTONE_LL,
  TL_SWSTONE_1,
  TL_SWSTONE_2,

  TL_TAB_LEG,
  TL_TAB_L,
  TL_TAB_R,
  TL_TAB_T,
  TL_TAB_C,
  
  TL_BLOCKING,

  TL_DOOR_BLOCK,
  TL_DESK,

  TL_JOIN_WALL,

  TL_FLOOR,
  TL_WALL,
  TL_BWALL,

  TL_DIRT,
  TL_CRYPTF,
  TL_ORG11,
  TL_ORG12,
  TL_ORG13,
  TL_ORG14,
  TL_ORG21,
  TL_ORG22,
  TL_ORG23,
  TL_ORG24,
  TL_ORG31,
  TL_ORG32,
  TL_ORG33,
  TL_ORG34,

  TL_CORNER_UR,
  TL_CORNER_UL,
  TL_CORNER_LR,
  TL_CORNER_LL,
  
  TL_IWALL,

  TL_NO_MODIFY,

  TL_WALL_BT,
  TL_WALL_TT,

  TL_OOB,

  TL_LAST
};
  
  
#define DEC_FIRSTRND DEC_BOOKSHELF

enum decoration_t
{
  DEC_BOOKSHELF,
  DEC_CORPSE,
  DEC_SKELETON,
  DEC_ALTAR,
  DEC_CHEST,
  DEC_FOUNTAIN,
  DEC_COFFIN,

  // These aren't randomly generated as loot
  DEC_ORB,
  DEC_TABLET,
  DEC_SWSTONE,
  DEC_IDOL,
  DEC_CAMP,

  // Below this point stuff that isn't "interesting"
  DEC_INTERESTING,
  DEC_SPENTCAMP,
  DEC_BRICKS,
  DEC_NPC,
  DEC_TRAPDOOR,
  DEC_DESK,
  DEC_ENTRANCE,
  DEC_BROKEN_IDOL,
  DEC_EMPTY_SHELF,
  DEC_PORTAL,
  DEC_DOOR,
  DEC_,
};


  

#define CELL_ROCK     0
#define CELL_LADDER   1
#define CELL_CHASM    2
#define CELL_RESERVED 3

#define CELL_BLOCKING 9 /* <= */

#define CELL_OPEN     10 /* >= */

#define CELL_RMNDR    10
#define CELL_ROOM     11
#define CELL_LADDER_B 12
#define CELL_LADDER_T 13
#define CELL_CHASM_T  14
#define CELL_TRAPDOOR 15
#define CELL_BOSS     16
#define CELL_MONSTER  17
#define CELL_LOOT     18
#define CELL_START    19
#define CELL_TRAP     20
#define CELL_SPIKEPIT 21
#define CELL_NPC_L    22
#define CELL_NPC_R    23
#define CELL_DEADEND  24
#define CELL_TRICKY   25
#define CELL_WCHASM   26
#define CELL_BRANCH   27
#define CELL_PORTAL   28
#define CELL_COFFIN   29
#define CELL_KEEPROOM 30
#define CELL_GORZOTH_L 31
#define CELL_GORZOTH_R 32
#define CELL_DOOR     33
#define CELL_CAMP     34
#define CELL_BRICKWALL 35
#define CELL_SWSTONE   36
#define CELL_TABLET    37


#endif