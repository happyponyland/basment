#include "basment.h"
#include "map.h"

int enemy_bar = -1;
int enemy_bar_time = 0;



int gfx_map[TL_LAST];



void init_gfx_map()
{
  gfx_map[TL_DESK]        = ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_GR_UR]       = ACS_URCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_UL]       = ACS_ULCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_LR]       = ACS_LRCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_LL]       = ACS_LLCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_LTEE]     = ACS_LTEE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_BTEE]     = ACS_BTEE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_NPC_LLEG]    = '/' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_NPC_RLEG]    = '\\' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_NPC_TORSO]   = ACS_CKBOARD | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_NPC_HEAD]    = 'o' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_STAIR_BTEE]  = ACS_BTEE | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_STAIR_UL]    = ACS_ULCORNER | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_STAIR_UR]    = ACS_URCORNER | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_STAIR_HL]    = ACS_HLINE | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_SKY]         = ' ' | COLOR_PAIR(PAIR_CYAN) | A_BOLD | A_REVERSE;
  gfx_map[TL_ENTR_DOOR]   = ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN) | A_REVERSE;
  gfx_map[TL_GR_TTEE]     = ACS_TTEE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_RTEE]     = ACS_RTEE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_BR_UL]       = ACS_ULCORNER | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_BR_UR]       = ACS_URCORNER | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_BR_VL]       = ACS_VLINE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_BR_HL]       = ACS_HLINE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_BL_TTEE]     = ACS_TTEE | COLOR_PAIR(PAIR_BLUE);
  gfx_map[TL_BL_UR]       = ACS_URCORNER | COLOR_PAIR(PAIR_BLUE);
  gfx_map[TL_BL_UL]       = ACS_ULCORNER | COLOR_PAIR(PAIR_BLUE);
  gfx_map[TL_BL_VL]       = ACS_VLINE | COLOR_PAIR(PAIR_BLUE);
  gfx_map[TL_FOUNT_BASE]  =
    gfx_map[TL_P_FOUNTAIN]   = ACS_CKBOARD | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_GR_HL]       =
    gfx_map[TL_P_ALTAR]      = ACS_HLINE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_GR_VL]       = ACS_VLINE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_WH_VL]       = ACS_VLINE | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_WH_LL]       = ACS_LLCORNER | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_WH_LR]       = ACS_LRCORNER | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_WH_PLUS]     = ACS_PLUS | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_YDOT]        = PORTABLE_DOT | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_SPIKE]       = '^' | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_BONE1]       = '/' | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_BONE3]       = 'o' | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_P_SKELETON]  =
    gfx_map[TL_BONE2]       = '#' | COLOR_PAIR(PAIR_WHITE);

  gfx_map[TL_ORB_CU]     = ACS_VLINE | COLOR_PAIR(PAIR_CYAN);
  gfx_map[TL_ORB_LU]     = '_' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORB_RU]     = '_' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORB_LIT]    = 'o' | COLOR_PAIR(PAIR_GREEN) | A_BOLD;
  gfx_map[TL_ORB_DARK]   = 'o' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_ORB_L]      = ACS_ULCORNER | COLOR_PAIR(PAIR_CYAN) | A_REVERSE;
  gfx_map[TL_ORB_R]      = ACS_URCORNER | COLOR_PAIR(PAIR_CYAN) | A_REVERSE;
  gfx_map[TL_P_ORB]      =
    gfx_map[TL_ORB_C]    = ACS_HLINE | COLOR_PAIR(PAIR_CYAN) | A_REVERSE;

  gfx_map[TL_CORPSE1]     = 'o' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CORPSE2]     = '/'| COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_P_CORPSE]    =
    gfx_map[TL_CORPSE3]     = 'T'| COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CORPSE4]     = '\\'| COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CORPSE5]     = '_'| COLOR_PAIR(PAIR_GREEN);

  gfx_map[TL_WOOD]        =
    gfx_map[TL_P_CHEST]     = ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_LOCK]        = 'X' | COLOR_PAIR(PAIR_BROWN) | A_BOLD | A_REVERSE;
  gfx_map[TL_BOULDER]     = 'o' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_REDSPIKE]    = '^' | COLOR_PAIR(PAIR_RED);

  gfx_map[TL_FLOOR]       = ACS_HLINE | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;

  gfx_map[TL_STOP]        = ' ';
  
  gfx_map[TL_T_POISON]  =
    gfx_map[TL_T_GORZOTH_L] =
    gfx_map[TL_T_GORZOTH_R] =
    gfx_map[TL_T_CAVEIN]  = ' ';

  gfx_map[TL_P_CAMP] =
    gfx_map[TL_CAMP_FIRE] = ',' | COLOR_PAIR(PAIR_RED) | A_BOLD;
  gfx_map[TL_CAMP_SPENT] = '_' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_CAMP_STAND_T] = 'Y' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_CAMP_STAND_B] = '|' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_CAMP_SPIT1] = ACS_URCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CAMP_SPIT2] = ACS_LLCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CAMP_SPIT3] = ACS_HLINE | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_CAMP_MEAT1] = '>' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_CAMP_MEAT2] = '*' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_CAMP_MEAT3] = '<' | COLOR_PAIR(PAIR_BROWN);

  gfx_map[TL_DIRT]       = ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_CRYPTF]     = ACS_PLUS | A_REVERSE | COLOR_PAIR(PAIR_BLUE);

  gfx_map[TL_ORG11] = 'O' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG12] = 'O' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORG13] = '&' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORG14] = '"' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG21] = 'O' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG22] = '0' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORG23] = 'V' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG24] = '_' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG31] = 'o' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG32] = 'o' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_ORG33] = '\'' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_ORG34] = '\'' | COLOR_PAIR(PAIR_RED);

  gfx_map[TL_STALACTITE1] = 'V' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_STALACTITE2] = '\'' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_STALACTITE3] = ACS_VLINE | COLOR_PAIR(PAIR_BROWN);

  gfx_map[TL_ROOTS1] = '\\' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_ROOTS2] = '/' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_ROOTS3] = '(' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_ROOTS4] = ')' | COLOR_PAIR(PAIR_BROWN);

  gfx_map[TL_WETROCKS1] = 'O' | COLOR_PAIR(PAIR_BLUE);
  gfx_map[TL_WETROCKS2] = '0' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_WETROCKS3] = 'O' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_WETROCKS4] = 'o' | COLOR_PAIR(PAIR_GREEN);

  gfx_map[TL_DOOR] = //ACS_VLINE | COLOR_PAIR(PAIR_RED_ON_BROWN);
  gfx_map[TL_DOOR_SIDE] = ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN_ON_RED);
  gfx_map[TL_DOOR_HL] = '(';
  gfx_map[TL_DOOR_HR] = ')';
  gfx_map[TL_DOOR_HF] = 'O';

  gfx_map[TL_DOOR_BLOCK] = //'X';
    gfx_map[TL_DOOR_L] =
    gfx_map[TL_DOOR_R] = ' ';

  gfx_map[TL_TRAPDOOR_M]  =
    gfx_map[TL_TRAPDOOR_S]  = ACS_CKBOARD | COLOR_PAIR(PAIR_RED) | A_REVERSE;

  gfx_map[TL_POISON_L1]   = '(' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_POISON_L2]   = '<' | COLOR_PAIR(PAIR_BLACK_ON_GREEN);
  gfx_map[TL_T_POISON_REV] =  // revealed poison trap
    gfx_map[TL_POISON_L3]   = ACS_CKBOARD | COLOR_PAIR(PAIR_BLACK_ON_GREEN);
  gfx_map[TL_POISON_R3]   = ACS_CKBOARD | COLOR_PAIR(PAIR_BLACK_ON_GREEN);
  gfx_map[TL_POISON_R2]   = '>' | COLOR_PAIR(PAIR_BLACK_ON_GREEN);
  gfx_map[TL_POISON_R1]   = ')' | COLOR_PAIR(PAIR_GREEN);

  gfx_map[TL_WALL]        = ACS_VLINE | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_CORNER_UR]   = ACS_URCORNER | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_CORNER_UL]   = ACS_ULCORNER | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_CORNER_LR]   = ACS_LRCORNER | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_CORNER_LL]   = ACS_LLCORNER | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_WALL_BT]     = ACS_BTEE | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_WALL_TT]     = ACS_TTEE | COLOR_PAIR(PAIR_WHITE) | A_REVERSE;
  gfx_map[TL_LADDER_M]    = ACS_HLINE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_LADDER_L]    = ACS_LTEE  | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_LADDER_R]    = ACS_RTEE  | COLOR_PAIR(PAIR_BROWN);

  gfx_map[TL_W_CORNER_UR]   = ACS_URCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_CORNER_UL]   = ACS_ULCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_CORNER_LR]   = ACS_LRCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_CORNER_LL]   = ACS_LLCORNER | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_LEFT]        = ACS_LTEE     | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_RIGHT]       = ACS_RTEE     | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_BOTTOM]      = ACS_TTEE     | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_TOP]         = ACS_BTEE     | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_VFLAT]       = ACS_VLINE    | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_W_HFLAT]       = ACS_HLINE    | COLOR_PAIR(PAIR_GREEN);
 
  gfx_map[TL_WEB_UL]      = ACS_ULCORNER  | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_UR]      = ACS_URCORNER  | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_LR]      = ACS_LRCORNER  | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_LL]      = ACS_LLCORNER  | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_TTEE]    = ACS_TTEE      | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_RTEE]    = ACS_RTEE      | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_LTEE]    = ACS_LTEE      | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_BTEE]    = ACS_BTEE      | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_VL]      = ACS_VLINE     | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_HL]      = ACS_HLINE     | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_FS]      = '/'           | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_BS]      = '\\'          | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_WEB_BURN1]   = '*'           | COLOR_PAIR(PAIR_BROWN) | A_BOLD | A_REVERSE;
  gfx_map[TL_WEB_BURN2]   = '*'           | COLOR_PAIR(PAIR_RED)   | A_BOLD | A_REVERSE;
/*  gfx_map[TL_WEB_WEIGHT]  = '\'';
  gfx_map[TL_WEB_FLOAT]   = '_';
  gfx_map[TL_WEB_SLASH]   = 'X';*/

  gfx_map[TL_UWNET_CROSS]   = ACS_PLUS;

  gfx_map[TL_VOID] =
    gfx_map[TL_BWALL] =
    gfx_map[TL_CHASM] =
    gfx_map[TL_IWALL] =
    gfx_map[TL_P_NPC1] =
    gfx_map[TL_P_NPC2] =
    gfx_map[TL_P_NPC3] =
    gfx_map[TL_P_NPC4] =
    gfx_map[TL_P_NPC5] =
    gfx_map[TL_P_NPC_SCUBA] =
    gfx_map[TL_P_NPC_SUSHI] = ' ';

  gfx_map[TL_L_A] = 'A';
  gfx_map[TL_L_B] = 'B';
  gfx_map[TL_L_C] = 'C';
  gfx_map[TL_L_D] = 'D';
  gfx_map[TL_L_E] = 'E';
  gfx_map[TL_L_F] = 'F';
  gfx_map[TL_L_G] = 'G';
  gfx_map[TL_L_H] = 'H';
  gfx_map[TL_L_I] = 'I';
  gfx_map[TL_L_J] = 'J';
  gfx_map[TL_L_K] = 'K';
  gfx_map[TL_L_L] = 'L';
  gfx_map[TL_L_M] = 'M';
  gfx_map[TL_L_N] = 'N';
  gfx_map[TL_L_O] = 'O';
  gfx_map[TL_L_P] = 'P';
  gfx_map[TL_L_Q] = 'Q';
  gfx_map[TL_L_R] = 'R';
  gfx_map[TL_L_S] = 'S';
  gfx_map[TL_L_T] = 'T';
  gfx_map[TL_L_U] = 'U';
  gfx_map[TL_L_V] = 'V';
  gfx_map[TL_L_W] = 'W';
  gfx_map[TL_L_X] = 'X';
  gfx_map[TL_L_Y] = 'Y';
  gfx_map[TL_L_Z] = 'Z';

  gfx_map[TL_IDOL_LARM] = ACS_LLCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_IDOL_RARM] = ACS_LRCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_IDOL_HEAD] = 'o' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_IDOL_HEAD_LIT] = 'o' | COLOR_PAIR(PAIR_RED) | A_BOLD;
  gfx_map[TL_IDOL_BODY] = ACS_CKBOARD | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_IDOL_BASE] = ' ';
  gfx_map[TL_P_IDOL] = ' ';
  gfx_map[TL_IDOL_STAND_UL] = ACS_ULCORNER | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_IDOL_STAND_UR] = ACS_URCORNER | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_IDOL_STAND_HL] = ACS_HLINE | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_IDOL_STAND_VL] = ACS_VLINE | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_IDOL_DEBRIS_1] = '.' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_IDOL_DEBRIS_2] = '/' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;

  gfx_map[TL_P_COFFIN]   =
    gfx_map[TL_COFFIN_HL]     = ACS_HLINE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_VL]     = ACS_VLINE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_FILL]   = ACS_CKBOARD | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_TTEE]   = ACS_TTEE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_LTEE]   = ACS_LTEE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_RTEE]   = ACS_RTEE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_BTEE]   = ACS_BTEE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_UR]     = ACS_URCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_UL]     = ACS_ULCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_CROSS1] = ACS_TTEE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_CROSS2] = ACS_PLUS | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_LID_R]  = '\\' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_COFFIN_LID_L]  = '/' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;

  gfx_map[TL_P_BOOKSHELF] =
    gfx_map[TL_SHELF_HL]    = ACS_HLINE | COLOR_PAIR(PAIR_BROWN);

  gfx_map[TL_SHELF_VL]    = ACS_VLINE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_RTEE]  = ACS_RTEE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_LTEE]  = ACS_LTEE | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_UL]    = ACS_ULCORNER | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_UR]    = ACS_URCORNER | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_BOOK1] = '\\' | COLOR_PAIR(PAIR_CYAN);
  gfx_map[TL_SHELF_BOOK2] = '=' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_SHELF_BOOK3] = '|' | COLOR_PAIR(PAIR_WHITE);
  gfx_map[TL_SHELF_BOOK4] = 'l' | COLOR_PAIR(PAIR_GREEN);
  gfx_map[TL_SHELF_BOOK5] = '/' | COLOR_PAIR(PAIR_RED);
  gfx_map[TL_SHELF_BOOK6] = '1' | COLOR_PAIR(PAIR_BROWN);
  gfx_map[TL_SHELF_BOOK7] = '_' | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_SHELF_BOOK8] = '/' | COLOR_PAIR(PAIR_GREEN);

  gfx_map[TL_PORTAL_S_B] =
    gfx_map[TL_P_PORTAL] = ACS_HLINE;
  gfx_map[TL_PORTAL_S_L] = ACS_ULCORNER;
  gfx_map[TL_PORTAL_S_R] = ACS_URCORNER;

  gfx_map[TL_PORTAL_R] = ')' | COLOR_PAIR(PAIR_BLUE) | A_BOLD;
  gfx_map[TL_PORTAL_L] = '(' | COLOR_PAIR(PAIR_BLUE) | A_BOLD;
  gfx_map[TL_PORTAL_T] = '~' | COLOR_PAIR(PAIR_BLUE) | A_BOLD | A_REVERSE;
  gfx_map[TL_PORTAL_M] = ' ' | COLOR_PAIR(PAIR_BLUE) | A_BOLD | A_REVERSE;

  gfx_map[TL_P_SWSTONE] = ' ';
  gfx_map[TL_SWSTONE_UL] = ACS_ULCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_SWSTONE_UR] = ACS_URCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_SWSTONE_LR] = ACS_LRCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_SWSTONE_LL] = ACS_LLCORNER | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_SWSTONE_1] = ACS_VLINE | COLOR_PAIR(PAIR_MAGENTA);
  gfx_map[TL_SWSTONE_2] = ACS_PLUS | COLOR_PAIR(PAIR_MAGENTA);

  gfx_map[TL_P_TABLET] = ' ';
  gfx_map[TL_TAB_LEG] = ACS_VLINE | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_TAB_L] = '\\' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_TAB_R] = '/' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_TAB_T] = '_' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;
  gfx_map[TL_TAB_C] = '=' | COLOR_PAIR(PAIR_BLACK) | A_BOLD;

  gfx_map[TL_SURFACE] = '~' | COLOR_PAIR(PAIR_WHITE_ON_CYAN);
  gfx_map[TL_WATER]   = ' ' | COLOR_PAIR(PAIR_BLACK_ON_CYAN);

  /* Underwater */
  gfx_map[TL_UWWOOD]        =
    gfx_map[TL_P_UWCHEST]   = ACS_CKBOARD  | COLOR_PAIR(PAIR_BLACK_ON_CYAN);
  gfx_map[TL_UWLOCK]        = 'X'          | COLOR_PAIR(PAIR_BLACK_ON_CYAN) | A_REVERSE;
  gfx_map[TL_UW_UL]         = ACS_ULCORNER | COLOR_PAIR(PAIR_BLACK_ON_CYAN);
  gfx_map[TL_UW_UR]         = ACS_URCORNER | COLOR_PAIR(PAIR_BLACK_ON_CYAN);
  gfx_map[TL_UW_VL]         = ACS_VLINE    | COLOR_PAIR(PAIR_BLACK_ON_CYAN);
  gfx_map[TL_UW_HL]         = ACS_HLINE    | COLOR_PAIR(PAIR_BLACK_ON_CYAN);

  return;
}




void draw_board()
{
  int y;
  int x;
  int i;
  int t;

  wbkgdset(board, COLOR_PAIR(PAIR_RED) | A_REVERSE);
  werase(board);
  wbkgdset(board, 0);

  for (y = 0; y < BOARD_H; y++)
  {
    for (x = 0; x < BOARD_W + 1; x++)
    {
      wmove(board, y, x);

      if (game->hallucination)
      {
	// Flip view up-side-down
	t = gtile(view_y + BOARD_H - 1 - y, view_x + x);
      }
      else
      {
	t = gtile(view_y + y, view_x + x);
      }

/*      game->branch[y / FLOOR_H][x / CELL_TO_TILES])*/

      waddch(board, gfx_map[t]);
    }
  }

  mob_t * mob;

  int sc_x;
  int sc_y;

  for (i = 0; i < MAX_MOBS; i++)
  {
    mob = &game->mob[i];

    if (mob->type != MOB_NONE)
    {
      sc_y = mob->y - view_y;
      sc_x = mob->x - view_x;

      if (!on_board(mob)) // && mob->type != MOB_SPIDER && mob->type != MOB_SNAKE)
	continue;

      if (game->hallucination && mob->type >= MOB_FIRSTRND)
      {
	// When hallucinating randomly cycle enemy appearances
	int new_type;

	new_type =
	  MOB_FIRSTRND +
	  ((mob->type - MOB_FIRSTRND + game->hallucination + mob->hp) %
	   (MOB_LASTRND - MOB_FIRSTRND));
	
	draw_thing(mob,
		   sc_y, sc_x,
		   new_type,
		   mob->flip,
		   mob->flags);
      }
      else
      {
	// Draw them normally
	draw_thing(mob,
		   sc_y, sc_x,
		   mob->type, mob->flip,
		   mob->flags);
      }
    }
  }

  // Make another pass of the tiles to change water
  for (y = 0; y < BOARD_H; y++)
  {
    for (x = 0; x < BOARD_W + 1; x++)
    {
      wmove(board, y, x);

      if (game->hallucination)
      {
	// Flip view up-side-down
	t = gtile(view_y + BOARD_H - 1 - y, view_x + x);
      }
      else
      {
	t = gtile(view_y + y, view_x + x);
      }

      if (t == TL_SURFACE)
	waddch(board, gfx_map[TL_SURFACE]);
      else if (t > TL_UNDERWATER && t < TL_LASTUNDERWATER)
      {
	int in;
	int ch;
	int attr;

	in = mvwinch(board, y, x);
	ch = in & A_CHARTEXT;
	attr = in & ((1<<22) | (1<<18));

	waddch(board, ch | attr | COLOR_PAIR(PAIR_BLACK_ON_CYAN));
      }
    }
  }

  // When hallucinating shift colors so everything looks like shit

  if (game->hallucination)
  {
    int in;
    int ch;
    int attr;
    int color;

    for (sc_y = 0; sc_y < BOARD_H; sc_y++)
    {
      for (sc_x = 0; sc_x <= BOARD_W; sc_x++)
      {
	in = mvwinch(board, sc_y, sc_x);
	ch = in & A_CHARTEXT;
	attr = in & ((1<<22) | (1<<18));
	color = PAIR_NUMBER(in & A_COLOR);

	color = MIN(PAIR_LAST, color + 3);

	waddch(board, ch | attr | COLOR_PAIR(color));
      }
    }
  }
  else if (game->scrying)
  {
    int c;
    int a;
    
    for (sc_y = 0; sc_y < BOARD_H; sc_y++)
    {
      for (sc_x = 0; sc_x <= BOARD_W; sc_x++)
      {
	c = mvwinch(board, sc_y, sc_x) & (A_CHARTEXT);
	a = mvwinch(board, sc_y, sc_x) & ((1<<22) | (1<<18));
	waddch(board, c | a | COLOR_PAIR(PAIR_WHITE) | A_BOLD);
      }
    }
  }

  wrefresh(board);

  return;
}






/*
  Prints C at Y, X on the board, unless the coordinates are outside
  the window.
*/
void g_add(int y, int x, chtype c)
{
  if (x < 0 || x > BOARD_W || y < 0 || y > BOARD_H)
    return;

  mvwaddch(board, y, x, c);
  
  return;
}



void board_attr(chtype a, chtype c)
{
  int y;
  
  for (y = 0; y < FLOOR_H; y++)
    mvwchgat(board, y, 0, -1, a, c, NULL);

  return;
}



/*
  Prints C at Y, X on the board, unless the coordinates are outside
  the window.
*/
void g_uadd(int y, int x, char * s, chtype a)
{
  if (x < 0 || x > BOARD_W || y < 0 || y > BOARD_H)
    return;

  wattrset(board, a);
  mvwaddstr(board, y, x, s);
  wattrset(board, 0);
  
  return;
}



void draw_thing(mob_t * mob, int y, int x, int type, bool flip, uint32_t flags)
{
  if (!title_running)
  {
    if (mob->webbed)
    {
      y--;
    }
    else if (!mob->flying)
    {
      if (gtile(mob->y + 1, mob->x)     == TL_SURFACE &&
	  gtile(mob->y + 1, mob->x - 1) == TL_SURFACE &&
	  gtile(mob->y + 1, mob->x + 1) == TL_SURFACE)
      {
	y++;
      }
    }
  }
  
  switch (type)
  {
  case MOB_PLAYER:
    switch(game->weapon)
    {
    case WPN_DAGGER:     flags |= GFX_HUMAN_DAGGER;   break;
    case WPN_SWORD:      flags |= GFX_HUMAN_SWORD;    break;
    case WPN_MACE:       flags |= GFX_HUMAN_MACE;     break;
    case WPN_AXE:        flags |= GFX_HUMAN_AXE;      break;
    case WPN_SPEAR:      flags |= GFX_HUMAN_SPEAR;    break;
    case WPN_FLAIL:      flags |= GFX_HUMAN_FLAIL;    break;
    case WPN_DIAMOND:    flags |= GFX_HUMAN_MACE | GFX_HUMAN_MWPN;   break;
    case WPN_GLASS:      flags |= GFX_HUMAN_SWORD | GFX_HUMAN_MWPN;  break;
    case WPN_DRAIN:      flags |= GFX_HUMAN_DAGGER | GFX_HUMAN_MWPN; break;
    case WPN_BOW:        flags |= GFX_HUMAN_BOW; break;
    case WPN_RUNESWORD:  flags |= GFX_HUMAN_SWORD | GFX_HUMAN_MWPN2;  break;
    default: break;
    }

    if (player->shd_type == 3)
      flags |= GFX_HUMAN_SHIELD1 | GFX_HUMAN_SHIELD2;
    else if (player->shd_type == 2)
      flags |= GFX_HUMAN_SHIELD2;
    else if (player->shd_type == 1)
      flags |= GFX_HUMAN_SHIELD1;

    if (player->armor_type == ARMOR_DRAGON)
      flags |= GFX_HUMAN_ARMOR3 | GFX_HUMAN_ARMOR1;
    else if (player->armor_type == ARMOR_MAGIC)
      flags |= GFX_HUMAN_ARMOR3;
    else if (player->armor_type == ARMOR_PLATE)
      flags |= GFX_HUMAN_ARMOR1 | GFX_HUMAN_ARMOR2;
    else if (player->armor_type == ARMOR_SCALE)
      flags |= GFX_HUMAN_ARMOR2;
    else if (player->armor_type == ARMOR_LEATHER)
      flags |= GFX_HUMAN_ARMOR1;

    if (player->shd_up)
      flags |= GFX_HUMAN_SHIELD_UP;
    
    flags |= GFX_HUMAN_PLAYER;

    draw_human(y, x, type, flip, flags);
    break;

  case MOB_GNOBLIN:
    draw_human(y, x, type, flip,
	       flags | GFX_HUMAN_GNOBLIN | GFX_HUMAN_BOW | GFX_HUMAN_ARMOR2);
    break;

  case MOB_ROGUE:
    draw_human(y, x, type, flip,
	       flags | GFX_HUMAN_DAGGER | GFX_HUMAN_ARMOR1);
    break;

  case MOB_KNAVE:
    draw_human(y, x, type, flip,
	       flags | GFX_HUMAN_SWORD | GFX_HUMAN_ARMOR2 | GFX_HUMAN_SHIELD2);
    break;

  case MOB_GORE:
    wmove(board, y, x - 1);
    waddch(board, '/' | COLOR_PAIR(PAIR_RED));
    waddch(board, 'T' | COLOR_PAIR(PAIR_RED));
    waddch(board, '@' | COLOR_PAIR(PAIR_RED));
    break;

  case MOB_SPIDER:
    draw_spider(y, x, type, flip, flags);
    break;

  case MOB_BRICKWALL:
    draw_brickwall(y, x, type, flip, flags);
    break;

  case MOB_MOTH:
    draw_moth(y, x, type, flip, flags);
    break;

  case MOB_GORZOTH:
    draw_gorzoth(y, x, type, flip, flags);
    break;

  case MOB_BIGSPIDER:
    if (mob->hp < 8) flags |= GFX_BIGSPIDER_HURT1;
    if (mob->hp < 7) flags |= GFX_BIGSPIDER_HURT2;
    if (mob->hp < 6) flags |= GFX_BIGSPIDER_HURT3;
    if (mob->hp < 5) flags |= GFX_BIGSPIDER_HURT4;
    if (mob->hp < 4) flags |= GFX_BIGSPIDER_HURT5;
    if (mob->hp < 3) flags |= GFX_BIGSPIDER_HURT6;
    if (mob->hp < 2) flags |= GFX_BIGSPIDER_HURT7;

    draw_bigspider(y, x, type, flip, flags);
    break;

  case MOB_MIMIC:
    draw_mimic(y, x, type, flip, flags);
    break;

  case MOB_SCAAL:
    draw_scaal(y, x, type, flip, flags);
    break;

  case MOB_BLURK:
    draw_blurk(y, x, type, flip, flags);
    break;

  case MOB_NOSE:
    draw_nose(y, x, type, flip, flags);
    break;

  case MOB_IMP:
    draw_imp(y, x, type, flip, flags);
    break;

  case MOB_EYE:
    draw_eye(y, x, type, flip, flags);
    break;

  case MOB_ELEMENTAL:
    draw_elemental(y, x, type, flip, flags);
    break;

  case MOB_EVILTREE:
    draw_eviltree(y, x, type, flip, flags);
    break;

  case MOB_SHRUBBERY:
    draw_shrubbery(y, x, type, flip, flags);
    break;

  case MOB_DKNIGHT:
    draw_dknight(y, x, type, flip, flags);
    break;

  case MOB_SKELETON:
    draw_skeleton(y, x, type, flip, flags);
    break;

  case MOB_ARCHDEMON:
    draw_archdemon(y, x, type, flip, flags);
    break;

  case MOB_DEMON:
    draw_demon(y, x, type, flip, flags);
    break;

  case MOB_GHOUL:
    draw_ghoul(y, x, type, flip, flags);
    break;

  case MOB_LICH:
    draw_lich(y, x, type, flip, flags);
    break;

  case MOB_GIANT:
    draw_giant(y, x, type, flip, flags);
    break;

  case MOB_SNAKE:
    draw_snake(y, x, type, flip, flags);
    break;

  case MOB_FISH:
    draw_fish(y, x, type, flip, flags);
    break;

  case MOB_CRAB:
    draw_crab(y, x, type, flip, flags);
    break;

  default:
    break;
  }

  return;
}



void draw_skeleton(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype bone;
  chtype armor;
  chtype eyes;
  chtype sword;

  eyes = COLOR_PAIR(PAIR_RED);
  sword = COLOR_PAIR(PAIR_CYAN);
  armor = COLOR_PAIR(PAIR_GREEN);

  if (flags & GFX_HURT)
  {
    bone = COLOR_PAIR(PAIR_BROWN) | A_BOLD;
  }
  else
  {
    bone = COLOR_PAIR(PAIR_WHITE);
  }

  GA(0, -2, GA_BS | bone);
  GA(0, +2, GA_FS | bone);

  GA(-1, -2, GA_FS | bone);
  GA(-1, +2, GA_BS | bone);

  GA(-2, -1, GA_UL   | bone);
  GA(-2, +0, GA_BT   | bone);
  GA(-2, +1, GA_UR   | bone);

//  GA(-3, -3, GA_FS | bone);
//  GA(-3, -2, '^' | bone);

  GA(-4, -1, GA_BL | armor);
  GA(-4, +0, '"' | eyes);
  GA(-4, +1, GA_BR | armor);

  GA(-5, -1, GA_PL | armor);
//  GA(-5, +0, '_' | armor);
  GA(-5, +1, GA_PR | armor);


  if (flags & GFX_ATTACK2)
  {
    GA(-4, +1, GA_FS | bone);
//    GA(-3, +0, '_' | bone);
//    GA(-4, +1, '_' | bone);
//    GA(-4, +2, '_' | bone);
    GA(-4, +2, GA_AR | bone);
    GA(-3, +0, 'V' | bone);

//    GA(-5, +2, ACS_PLUS | sword);
//    GA(-5, +1, GA_HL | sword);
//    GA(-5, +0, GA_HL | sword);
//    GA(-5, -1, GA_HL | sword);
//    GA(-5, -2, GA_HL | sword);
//    GA(-5, -3, GA_HL | sword);

//    GA(-5, +2, '_' | sword);
//    GA(-5, +1, GA_HL | sword);
    GA(-5, +0, '_' | sword);
//    GA(-5, -1, GA_HL | sword);
    GA(-5, -2, '_' | sword);
    GA(-5, -3, '_' | sword);
  }
  else if (flags & GFX_ATTACK)
  {
    GA(-3, -1, GA_BS | bone);
    GA(-3, +0, '_' | bone);
    GA(-3, +1, '_' | bone);
    GA(-3, +2, GA_BS | bone);
    GA(-3, +3, ACS_PLUS | sword);
    GA(-3, +4, GA_HL | sword);
    GA(-3, +5, GA_HL | sword);
    GA(-3, +6, GA_HL | sword);
  }
  else
  {
    GA(-3, +1, GA_FS | bone);
    GA(-3, +0, '_' | bone);
    GA(-3, -1, '_' | bone);
    GA(-3, -2, GA_FS | bone);
    GA(-3, -3, ACS_PLUS | sword);
    GA(-4, -3, GA_VL | sword);
    GA(-5, -3, GA_VL | sword);
  }
  

  return;
}



void draw_mimic(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype c;

  if (flags & GFX_HURT)
    c = COLOR_PAIR(PAIR_RED);
  else
    c = COLOR_PAIR(PAIR_BROWN);

  if (flags & GFX_MIMIC_IDLE)
  {
    GA(0, -2, ACS_CKBOARD | c);
    GA(0, -1, ACS_CKBOARD | c);
    GA(0, -0, ACS_CKBOARD | c);
    GA(0, +1, ACS_CKBOARD | c);
    GA(0, +2, ACS_CKBOARD | c);

    GA(-1, -2, ACS_CKBOARD | c);
    GA(-1, -1, ACS_CKBOARD | c);
    GA(-1, -0, 'X' | c | A_REVERSE);
    GA(-1, +1, ACS_CKBOARD | c);
    GA(-1, +2, ACS_CKBOARD | c);
  }
  else
  {
    GA(0, -3, GA_UL | c);
    GA(0, -2, GA_LR | c);
    GA(0, -1, ' ');
    GA(0, -0, ' ');
    GA(0, +1, ' ');
    GA(0, +2, GA_LL | c);
    GA(0, +3, GA_UR | c);

    GA(-1, -3, GA_LL | c);
    GA(-1, -2, ACS_CKBOARD | c);
    GA(-1, -1, ACS_CKBOARD | c);
    GA(-1, -0, ACS_CKBOARD | c);
    GA(-1, +1, ACS_CKBOARD | c);
    GA(-1, +2, ACS_CKBOARD | c);
    GA(-1, +3, GA_LR | c);

    GA(-2, -3, GA_UR | c);
    GA(-2, -2, GA_UL | c);
    GA(-2, -1, ACS_HLINE    | c);
    GA(-2, -0, ACS_HLINE    | c);
    GA(-2, +1, ACS_HLINE    | c);
    GA(-2, +2, GA_UR | c);
    GA(-2, +3, GA_UL | c);

    GA(-3, -1, GA_BS | COLOR_PAIR(PAIR_RED));
    GA(-3, -0, ' ');
    GA(-3, +1, GA_FS | COLOR_PAIR(PAIR_RED));
  }

  return;
}



void draw_eye(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype a;
  chtype b;

  if (flags & GFX_HURT)
  {
    a = COLOR_PAIR(PAIR_WHITE);
    b = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    a = COLOR_PAIR(PAIR_GREEN);
    b = COLOR_PAIR(PAIR_BLUE) | A_BOLD;
  }

  GA(-4, -4, GA_AR | b);
  GA(-4, -3, GA_UR | a);
  GA(-4, -2, ' ');
  GA(-4, -1, '_' | b);
  GA(-4, -0, '_' | b);
  GA(-4, +1, '_' | b);
  GA(-4, +2, ' ');
  GA(-4, +3, GA_UL | a);
  GA(-4, +4, GA_AL | b);

  GA(-3, -3, GA_LL | a);
  GA(-3, -2, GA_FS | b);
  GA(-3, -1, ' ');
  GA(-3, -0, ' ');
  GA(-3, +1, ' ');
  GA(-3, +2, GA_BS | b);
  GA(-3, +3, GA_LR | a);

  GA(-2, -2, GA_PR | b);
  GA(-2, -1, ' ');
  GA(-2, -0, ' ');
  GA(-2, +1, ' ');
  GA(-2, +2, GA_PL | b);

  if (flags & GFX_HURT)
    GA(-2, 0, 'X' | COLOR_PAIR(PAIR_RED) | A_BOLD);
  else
    GA(-2, 0, ACS_DIAMOND | COLOR_PAIR(PAIR_RED) | A_BOLD);

  GA(-1, -4, 'v' | b);
  GA(-1, -3, GA_UL | a);
  GA(-1, -2, GA_BS | b);
  GA(-1, -1, '_' | b);
  GA(-1, -0, '_' | b);
  GA(-1, +1, '_' | b);
  GA(-1, +2, GA_FS | b);
  GA(-1, +3, GA_UR | a);
  GA(-1, +4, 'v' | b);

  GA(0, -4, GA_LL | a);
  GA(0, -3, GA_LR | a);

  GA(0, +3, GA_LL | a);
  GA(0, +4, GA_LR | a);

  return;
}



void draw_gorzoth(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype skull;
  chtype horns;
  chtype eyes;
  chtype cross;
  chtype shell;
  chtype arms;
  chtype chest;
  chtype stinger;

/*  if (flags & GFX_HURT)
  {
    a = COLOR_PAIR(PAIR_WHITE);
    b = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    a = COLOR_PAIR(PAIR_GREEN);
    b = COLOR_PAIR(PAIR_BLUE) | A_BOLD;
    }*/
  horns = COLOR_PAIR(PAIR_RED);
  skull = COLOR_PAIR(PAIR_WHITE);
  cross = COLOR_PAIR(PAIR_RED) | A_BOLD;

  if (flags & GFX_HURT)
  {
    eyes = COLOR_PAIR(PAIR_WHITE);
    //shell = COLOR_PAIR(PAIR_WHITE);
    chest = COLOR_PAIR(PAIR_RED);
    shell = arms = stinger = COLOR_PAIR(PAIR_BROWN) | A_BOLD;
  }
  else
  {
    eyes = COLOR_PAIR(PAIR_RED) | A_BOLD | A_BLINK;
    shell = COLOR_PAIR(PAIR_GREEN);
    chest = COLOR_PAIR(PAIR_BLUE);
    stinger = COLOR_PAIR(PAIR_RED);
    arms = COLOR_PAIR(PAIR_GREEN);
  }

  GA(-2, +2, GA_LR | skull);
  GA(-2, +1, ACS_BTEE | skull);
  GA(-2, +0, ACS_BTEE | skull);
  GA(-2, -1, ACS_BTEE | skull);
  GA(-2, -2, GA_LL | skull);

  GA(-3, +3, GA_BS | skull);
  GA(-3, +2, GA_LT | skull);
  GA(-3, +1, ACS_PLUS | skull);
  GA(-3, +0, ACS_PLUS | skull);
  GA(-3, -1, ACS_PLUS | skull);
  GA(-3, -2, GA_RT | skull);
  GA(-3, -3, GA_FS | skull);

  GA(-4, +4, GA_BS | skull);
  GA(-4, +3, '_' | skull);
  GA(-4, +1, '\'' | skull);
  GA(-4, -1, '\'' | skull);
  GA(-4, -3, '_' | skull);
  GA(-4, -4, GA_FS | skull);

  GA(-5, +4, GA_FS | skull);
  GA(-5, -4, GA_BS | skull);

  GA(-6, +3, GA_FS | skull);
  GA(-6, -3, GA_BS | skull);

  if (flags & GFX_HURT)
  {
    GA(-5, +2, 'x'| eyes);
    GA(-5, -2, 'x' | eyes);
  }
  else
  {
    GA(-5, +2, '+' | eyes);
    GA(-5, -2, '+' | eyes);
  }

  GA(-7, +2, '_' | skull);
  GA(-7, +1, '_' | skull);
  GA(-7, -1, '_' | skull);
  GA(-7, -2, '_' | skull);

  GA(-6, +4, '_' | horns);
  GA(-6, +5, GA_FS | horns);
  GA(-7, +5, GA_BS | horns);
  GA(-8, +4, GA_PL | horns);

  GA(-6, -4, '_' | horns);
  GA(-6, -5, GA_BS | horns);
  GA(-7, -5, GA_FS | horns);
  GA(-8, -4, GA_PR | horns);

  GA(-5, -0, ACS_VLINE | cross);
  GA(-6, +2, ACS_HLINE | cross);
  GA(-6, +1, ACS_HLINE | cross);
  GA(-6, -0, ACS_PLUS | cross);
  GA(-6, -1, ACS_HLINE | cross);
  GA(-6, -2, ACS_HLINE | cross);
  GA(-7, -0, ACS_VLINE | cross);
  GA(-8, -0, ACS_VLINE | cross);
  GA(-9, -0, ACS_VLINE | cross);

  if (flags & GFX_ATTACK)
  {
    GA(-2, +3, '_' | arms);
    GA(-2, +4, '_' | arms);
    GA(-2, +5, '_' | arms);
    GA(-1, +4, '\'' | stinger);
    GA(-1, +5, '\'' | stinger);
  }
  else
  {
    GA(-1, +3, '_' | arms);
    GA(-1, +2, '_' | arms);
    GA(-1, +1, GA_FS | arms);
    GA(+0, +4, '\'' | stinger);
    GA(+0, +3, '\'' | stinger);
  }

  GA(-1, -2, '_' | arms);
  GA(-1, -3, '_' | arms);
  GA(-1, -4, GA_FS | arms);
  GA(+0, -1, '\'' | stinger);
  GA(+0, -2, '\'' | stinger);
  
  GA(-4, -5, '_' | shell);
  GA(-4, -6, '_' | shell);
//  GA(-4, +7, '_' | shell);

  // Stingers on the back
  GA(-4, -8,  GA_BS | stinger);
  GA(-1, -11, ACS_HLINE | stinger);
  GA(-1, -12, ACS_HLINE | stinger);
  GA(+3, -9,  GA_FS | stinger);
  GA(+4, -4,  '|' | stinger);

  GA(-3, -4, ACS_HLINE | chest);
//  GA(-3, +5, ACS_HLINE | chest);
  GA(-3, -5, GA_BS | shell);
  GA(-3, -6, 'o' | shell);
  GA(-3, -7, 'O' | shell);
  GA(-3, -8, 'o' | shell);

  GA(-2, -3, ACS_HLINE | chest);
  GA(-2, -4, ACS_HLINE | chest);
  GA(-2, -5, ACS_HLINE | chest);
  GA(-2, -6, ACS_HLINE | chest);
  GA(-2, -7, GA_BS | shell);
  GA(-2, -8, 'O' | shell);
  GA(-2, -9, 'o' | shell);

  GA(-1, +0, ACS_HLINE | chest);
  GA(-1, -1, ACS_HLINE | chest);
  GA(-1, -5, ACS_HLINE | chest);
  GA(-1, -6, ACS_HLINE | chest);
  GA(-1, -7, ACS_HLINE | chest);
  GA(-1, -8, GA_BS | shell);
  GA(-1, -9, 'O' | shell);
  GA(-1, -10, 'o' | shell);

  GA(-0, -3, GA_LR | chest);
  GA(-0, -4, ACS_TTEE | chest);
  GA(-0, -5, ACS_HLINE | chest);
  GA(-0, -6, ACS_HLINE | chest);
  GA(-0, -7, ACS_HLINE | chest);
  GA(-0, -8, GA_FS | shell);
  GA(-0, -9, 'O' | shell);
  GA(-0, -10, 'o' | shell);

  GA(+1, -4, GA_LR | chest);
  GA(+1, -5, ACS_TTEE | chest);
  GA(+1, -6, ACS_HLINE | chest);
  GA(+1, -7, GA_FS | shell);
  GA(+1, -8, 'O' | shell);
  GA(+1, -9, 'o' | shell);

  GA(+2, -3, GA_UR | chest);
  GA(+2, -4, ACS_HLINE | chest);
  GA(+2, -5, GA_FS | shell);
  GA(+2, -6, 'o' | shell);
  GA(+2, -7, 'O' | shell);
  GA(+2, -8, 'o' | shell);

  GA(+3, -2, GA_FS | shell);
  GA(+3, -3, 'o' | shell);
  GA(+3, -4, 'O' | shell);
  GA(+3, -5, 'o' | shell);
  GA(+3, -6, '^' | shell);

  GA(+2, +1, GA_BS | stinger);
  GA(+2, +0, GA_FS | stinger);
  GA(+2, -1, '_' | stinger);

  GA(+3, +1, GA_FS | stinger);
  GA(+3, +0, 'X' | stinger);
  GA(+3, -1, GA_FS | stinger);

  return;
}



void draw_bigspider(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype legs1;
  chtype legs2;
  chtype body;
  chtype eyes;

  if (flags & GFX_HURT)
  {
    eyes = COLOR_PAIR(PAIR_RED) | A_BOLD;
    legs1 = COLOR_PAIR(PAIR_WHITE);
    legs2 = COLOR_PAIR(PAIR_RED);
    body = COLOR_PAIR(PAIR_BROWN) | A_BOLD;
  }
  else
  {
    eyes = COLOR_PAIR(PAIR_RED) | A_BOLD;
    legs1 = COLOR_PAIR(PAIR_BROWN) | A_BOLD;
    legs2 = COLOR_PAIR(PAIR_BLACK) | A_BOLD;
    body = COLOR_PAIR(PAIR_GREEN) | A_BOLD;
  }

  GA(-2, -3, GA_AL | body);
  GA(-2, +3, GA_AR | body);
  GA(-3, -3, GA_AL | body);
  GA(-3, +3, GA_AR | body);
  GA(-4, -2, GA_FS | body);
  GA(-4, +2, GA_BS | body);
 
  if ((flags & GFX_BIGSPIDER_HURT1) == 0)
    GA(-4, -0, 'o' | eyes);

  if ((flags & GFX_BIGSPIDER_HURT2) == 0)
    GA(-2, -1, 'o' | eyes);

  if ((flags & GFX_BIGSPIDER_HURT3) == 0)
    GA(-3, +2, 'o' | eyes);
  
  if ((flags & GFX_BIGSPIDER_HURT4) == 0)
    GA(-4, -1, 'o' | eyes);
  
  if ((flags & GFX_BIGSPIDER_HURT5) == 0)
    GA(-2, +1, 'o' | eyes);
  
  if ((flags & GFX_BIGSPIDER_HURT6) == 0)
    GA(-4, +1, 'o' | eyes);

  if ((flags & GFX_BIGSPIDER_HURT7) == 0)
    GA(-3, -2, 'o' | eyes);
  
  if (flags & GFX_BIGSPIDER_HURT7)
    GA(-3, -0, 'o' | eyes | A_BLINK);
  else
    GA(-3, -0, 'o' | eyes);

  GA(-1, -2, GA_PL | eyes);
  GA(-1, +2, GA_PR | eyes);

//  GA(-0, -6, GA_BS | legs1);
  GA(-0, -7, GA_BS | legs1);
  GA(-1, -7, GA_FS | legs2);
  GA(-2, -6, GA_FS | legs1);
  GA(-3, -5, '_' | legs2);
  GA(-3, -4, '_' | legs1);

  GA(-0, -4, GA_BS | legs2);
  GA(-1, -4, GA_FS | legs1);

  GA(-4, -7, GA_BS | legs2);
  GA(-5, -7, '_' | legs1);
  GA(-5, -6, '_' | legs2);
  GA(-5, -5, '_' | legs1);
  GA(-5, -4, '_' | legs2);
  GA(-4, -3, GA_BS | legs1);

//  GA(-0, +6, GA_FS | legs1);
  GA(-0, +7, GA_FS | legs1);
  GA(-1, +7, GA_BS | legs2);
  GA(-2, +6, GA_BS | legs1);
  GA(-3, +5, '_' | legs2);
  GA(-3, +4, '_' | legs1);

  GA(-0, +4, GA_FS | legs2);
  GA(-1, +4, GA_BS | legs1);

  if (flags & GFX_ATTACK)
  {
    GA(-3, +8, GA_BS | legs2);
    GA(-4, +7, '_' | legs1);
    GA(-4, +6, '_' | legs2);
    GA(-4, +5, '_' | legs1);
    GA(-4, +4, '_' | legs2);
    GA(-4, +3, '_' | legs1);
  }
  else
  {
    GA(-4, +7, GA_FS | legs2);
    GA(-5, +7, '_' | legs1);
    GA(-5, +6, '_' | legs2);
    GA(-5, +5, '_' | legs1);
    GA(-5, +4, '_' | legs2);
    GA(-4, +3, GA_FS | legs1);
  }

  return;
}



void draw_shrubbery(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype trunk;
  chtype leaves;
  int ty;
  
  leaves = COLOR_PAIR(PAIR_GREEN) | A_REVERSE;

  if (flags & GFX_HURT)
  {
    trunk = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    trunk = COLOR_PAIR(PAIR_BROWN);
  }

  GA(+2, -1, GA_UL | trunk);
  GA(+2, +0, GA_BT | trunk);
  GA(+2, +1, GA_TT | trunk);
  GA(+2, +2, GA_UR | trunk);

  GA(+3, -3, GA_UL | trunk);
  GA(+3, -2, GA_HL | trunk);
  GA(+3, -1, GA_LR | trunk);
  GA(+3, +0, GA_UL | trunk);
  GA(+3, +1, GA_RT | trunk);
  GA(+3, +2, GA_LL | trunk);
  GA(+3, +3, GA_UR | trunk);

  GA(+4, +1, GA_VL | trunk);

  ty = 0;

  GA(ty, -1, GA_LL | trunk);
  GA(ty, +0, GA_TT | trunk);
  GA(ty, +1, GA_LR | trunk);
  GA(ty, +2, '*' | leaves);

  ty--;

  GA(ty, -2, '*' | leaves);
  GA(ty, -1, GA_LT | trunk);
  GA(ty, +0, GA_LR | trunk);
  GA(ty, +1, GA_LT | trunk);
  GA(ty, +2, GA_UR | trunk);

  ty--;

  GA(ty, -2, GA_UL | trunk);
  GA(ty, -1, GA_UR | trunk);
  GA(ty, +0, '*' | leaves); //GA_VL | trunk);
  GA(ty, +1, GA_HL | trunk);
  GA(ty, +2, GA_LR | trunk);

  ty--;

  GA(ty, -2, GA_LL | trunk);
  GA(ty, -1, GA_HL | trunk);
  GA(ty, +0, GA_RT | trunk);
  GA(ty, +1, ' ');
  GA(ty, +2, '*' | leaves);

  ty--;

  GA(ty, -2, '*' | leaves);
  GA(ty, -1, GA_LL | trunk);
  GA(ty, +0, GA_TT | trunk);
  GA(ty, +1, GA_LR | trunk);

  ty--;

  GA(ty, -1, '*' | leaves);
  GA(ty, +1, '*' | leaves);

  return;
}


void draw_eviltree(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype trunk;
  chtype leaves;
  chtype eyes;
  int ty;
  
  leaves = COLOR_PAIR(PAIR_GREEN) | A_REVERSE;

  if (flags & GFX_HURT)
  {
    eyes = COLOR_PAIR(PAIR_WHITE) | A_BOLD;
    trunk = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    eyes = COLOR_PAIR(PAIR_RED) | A_BOLD;
    trunk = COLOR_PAIR(PAIR_BROWN);
  }

  // roots
//  GA(+2, -3, GA_UL | trunk);
//  GA(+2, -3, GA_VL | trunk);
  GA(+2, +3, GA_LL | trunk);
  GA(+2, +4, GA_TT | trunk);
  GA(+3, +4, GA_VL | trunk);
//  GA(+4, +4, GA_VL | trunk);
  GA(+2, +5, GA_HL | trunk);
  GA(+2, +6, GA_UR | trunk);

//  GA(+2, -2, GA_BT | trunk);

  GA(+2, +1, GA_VL | trunk);
  GA(+3, +1, GA_LL | trunk);
  GA(+3, +2, GA_UR | trunk);
  GA(+4, +2, GA_VL | trunk);

  GA(+3, -1, GA_LL | trunk);
  GA(+2, -2, GA_VL | trunk);
  GA(+2, -1, GA_UR | trunk);

  GA(+2, -2, GA_BT | trunk);

  GA(+2, -3, GA_UL | trunk);
  GA(+3, -3, GA_LR | trunk);
  GA(+3, -4, GA_TT | trunk);
  GA(+4, -4, GA_VL | trunk);

  GA(+3, -5, GA_HL | trunk);
  GA(+3, -6, GA_UL | trunk);

  //base
  ty = 0;

  GA(ty, -2, GA_VL | trunk);
  GA(ty, -1, ' ');
  GA(ty, +0, ' ');
  GA(ty, +1, GA_UL | trunk);
  GA(ty, +2, GA_BT | trunk);
  GA(ty, +3, GA_UR | trunk);


  // mouth
  ty--;

  GA(ty, -2, GA_LT | trunk);
  GA(ty, -1, GA_BT | trunk);
  GA(ty, +0, GA_BT | trunk);
  GA(ty, +1, GA_BT | trunk);
  GA(ty, +2, GA_RT | trunk);

  ty--;

  GA(ty, -2, GA_VL | trunk);
  GA(ty, +2, GA_VL | trunk);
//  GA(-1, -1, GA_VL | trunk);
//  GA(-1, +1, GA_VL | trunk);

//  GA(-1, -3, GA_PL | trunk);
  GA(ty, +0, '_' | eyes);
//  GA(-1, +3, GA_PR | trunk);

  ty--;

  GA(ty, -2, GA_LT | trunk);
  GA(ty, -1, GA_TT | trunk);
  GA(ty, +0, GA_HL | trunk);
  GA(ty, +1, GA_TT | trunk);
  GA(ty, +2, GA_RT | trunk);

  // eyes
  ty--;

  GA(ty, +2, GA_VL | trunk);

  // x for hurt
  if (flags & GFX_HURT)
  {
    GA(ty, -1, 'x');
    GA(ty, +1, 'x');
  }
  else
  {
    GA(ty, -1, GA_BS | eyes);
    GA(ty, +1, GA_FS | eyes);
  }


  ty--;

  GA(ty, -4, GA_LL | trunk);
  GA(ty, -3, GA_HL | trunk);
  GA(ty, -2, GA_RT | trunk);
  GA(ty, -1, ' ');
  GA(ty, +0, ' ');
  GA(ty, +0, ' ');
  GA(ty, +2, GA_VL | trunk);

  ty--;

//  GA(ty, -7, ' ');
  GA(ty, -6, ' ');
  GA(ty, -5, GA_UL | trunk);
  GA(ty, -4, GA_RT | trunk);
  GA(ty, -3, GA_LL | trunk);
  GA(ty, -2, GA_TT | trunk);
  GA(ty, -1, GA_LR | trunk);
  GA(ty, +0, ' ');
  GA(ty, +1, GA_LL | trunk);
  GA(ty, +2, GA_TT | trunk);
  GA(ty, +3, GA_HL | trunk);
  GA(ty, +4, GA_LR | trunk);
  GA(ty, +5, ' ');
  GA(ty, +6, '*' | leaves);
  GA(ty, +7, ' ');

  ty--;

  GA(ty, -7, GA_LL | trunk);
  GA(ty, -6, '*' | leaves);
  GA(ty, -4, '*' | leaves);
  GA(ty, -3, GA_VL | trunk);
  GA(ty, -2, GA_LL | trunk);
  GA(ty, -1, GA_TT | trunk);

  GA(ty, +0, '*' | leaves);
  GA(ty, +1, GA_RT | trunk);
  GA(ty, +2, GA_LR | trunk);
  GA(ty, +3, GA_VL | trunk);
  GA(ty, +4, '*' | leaves);

  GA(ty, +5, GA_HL | trunk);
  GA(ty, +6, GA_TT | trunk);
  GA(ty, +7, GA_LR | trunk);
//  GA(ty, +3, GA_LL | trunk);

  ty--;
  GA(ty, -7, '*' | leaves);
  GA(ty, -6, GA_UL | trunk);
  GA(ty, -5, GA_BT | trunk);
  GA(ty, -4, GA_HL | trunk);
  GA(ty, -3, GA_RT | trunk);
  GA(ty, -2, '*' | leaves);
  GA(ty, -1, GA_LR | trunk);

  GA(ty, +1, '*' | leaves);
//  GA(ty, +1, GA_LL | trunk);
  GA(ty, +2, GA_VL | trunk);
  GA(ty, +3, GA_RT | trunk);
  GA(ty, +4, GA_UL | trunk);
  GA(ty, +5, GA_HL | trunk);
  GA(ty, +6, GA_LR | trunk);
  GA(ty, +7, '*' | leaves);

  ty--;

  GA(ty, -5, '*' | leaves);
  GA(ty, -3, GA_VL | trunk);
  GA(ty, -1, '*' | leaves);
  GA(ty, +2, '*' | leaves);
  GA(ty, +3, GA_LT | trunk);
  GA(ty, +4, GA_UR | trunk);
  GA(ty, +5, '*' | leaves);
  GA(ty, +6, GA_UR | trunk);


/*  y--;

  GA(ty, -5, GA_LL | trunk);
  GA(ty, -4, GA_PL | leaves | A_REVERSE);
  GA(ty, -3, ' ' | leaves | A_REVERSE);
  GA(ty, -2, GA_LT | trunk);// ACS_CKBOARD | leaves);
  GA(ty, -1, ACS_CKBOARD | leaves);
  GA(ty, +1, '^' | leaves);
  GA(ty, +2, ' ' | leaves | A_REVERSE);
  GA(ty, +3, ACS_CKBOARD | leaves);
  GA(ty, +4, GA_PR | leaves | A_REVERSE);
  
  ty--;

  GA(ty, -5, ACS_CKBOARD | leaves);
  GA(ty, -4, ' ' | leaves | A_REVERSE);
  GA(ty, -3, '*' | leaves | A_REVERSE);
  GA(ty, -2, ' ' | leaves | A_REVERSE);
  GA(ty, -1, ACS_CKBOARD | leaves);
  GA(ty, +0, '^' | leaves | A_REVERSE);
  GA(ty, +1, ' ' | leaves | A_REVERSE);
  GA(ty, +2, ACS_CKBOARD | leaves);
  GA(ty, +3, GA_TT | trunk);
  GA(ty, +4, '^' | leaves | A_REVERSE);
  GA(ty, +5, GA_PR | leaves | A_REVERSE);

  ty--;

  GA(ty, -3, ACS_CKBOARD | leaves);
  GA(ty, -2, GA_TT | trunk);
//  GA(ty, -2, ACS_CKBOARD | leaves);
  GA(ty, -1, ACS_CKBOARD | leaves);
  GA(ty, +0, ACS_CKBOARD | leaves);
  GA(ty, +1, '^' | leaves | A_REVERSE);//ACS_CKBOARD | leaves);
  GA(ty, +2, ACS_CKBOARD | leaves);
  GA(ty, +3, ACS_CKBOARD | leaves);
  GA(ty, +4, '_' | leaves);*/

  // front arm
  if (flags & GFX_ATTACK2)
  {
//    GA(-3, +3, GA_HL | trunk);
    GA(-3, +3, GA_LR | trunk);
    GA(-4, +3, GA_VL | trunk);
    GA(-5, +3, GA_LT | trunk);
    GA(-5, +4, GA_HL | trunk);
    GA(-5, +5, GA_UR | trunk);
//    GA(-2, +5, GA_HL | trunk);
  }
  else if (flags & GFX_ATTACK)
  {
    GA(-2, +3, GA_HL | trunk);
    GA(-2, +4, GA_HL | trunk);
    GA(-2, +5, GA_HL | trunk);
    GA(-2, +6, GA_HL | trunk);
    GA(-2, +7, GA_TT | trunk);
    GA(-1, +7, GA_LR | trunk);
    GA(-2, +8, GA_HL | trunk);
    GA(-2, +9, GA_UR | trunk);
    GA(-1, +9, GA_LR | trunk);
  }
  else
  {
    GA(-3, +3, GA_HL | trunk);
    GA(-3, +4, GA_LR | trunk);
    GA(-4, +4, GA_UL | trunk);
    GA(-4, +5, GA_HL | trunk);
    GA(-4, +6, GA_UR | trunk);
    GA(-3, +6, GA_RT | trunk);
    GA(-3, +5, GA_UL | trunk);
    GA(-2, +6, GA_LR | trunk);
    GA(-2, +5, GA_HL | trunk);
  }

  // back arm
  GA(-4, -2, GA_RT | trunk);
  GA(-4, -3, GA_HL | trunk);
  GA(-4, -4, GA_HL | trunk);
  GA(-4, -5, GA_UL | trunk);
  GA(-3, -5, GA_LT | trunk);
  GA(-2, -5, GA_LL | trunk);
  GA(-3, -4, GA_UR | trunk);


  return;
}



void draw_demon(int y, int x, int type, bool flip, uint32_t flags)
{
  int a1;
  int a2;
  int a3;

  if (flags & GFX_HURT)
  {
    a1 = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    a1 = COLOR_PAIR(PAIR_MAGENTA);
  }

  a2 = COLOR_PAIR(PAIR_GREEN);
  a3 = COLOR_PAIR(PAIR_CYAN);

  // Horns
  GA(-4, -3, ACS_VLINE | a1);
  GA(-4, +3, ACS_VLINE | a1);

  // Head
  GA(-3, -3, GA_LL | a1);
  GA(-3, -2, ACS_HLINE | a1);
  GA(-3, +2, ACS_HLINE | a1);
  GA(-3, +3, GA_LR | a1);

  // Eyes
  GA(-3, -1, GA_BS | a2 | A_BOLD);
  GA(-3, -0, ' ');
  GA(-3, +1, GA_FS | a2 | A_BOLD);

  // Mouth
  GA(-2, -2, GA_AL | a3);

  if (flags & GFX_ATTACK)
  {
    GA(-2, -1, '_' | a2);
    GA(-2, -0, '_' | a2);
    GA(-2, +1, '_' | a2);
  }
  else
  {
    GA(-2, -1, '#' | a2);
    GA(-2, -0, '#' | a2);
    GA(-2, +1, '#' | a2);
  }

  GA(-2, +2, GA_AR | a3);

  // Claws

  if (flags & GFX_ATTACK)
  {
    GA(-1, -3, GA_BL | a1);
    GA(-1, -2, GA_PR | a1);
    GA(-1, -1, GA_PR | a1);
    GA(-1, -0, ' ');
    GA(-1, +1, ' ');
    GA(-1, +2, GA_PR | a1);
    GA(-1, +3, '=' | a1);
  }
  else
  {
    GA(-1, -3, GA_BL | a1);
    GA(-1, -2, '\'' | a1);
    GA(-1, -1, GA_PR | a1);
    GA(-1, -0, ' ');
    GA(-1, +1, ' ');
    GA(-1, +2, GA_PR | a1);
    GA(-1, +3, '\'' | a1);
  }

  // Tail
  GA(-1, -5, GA_LL | a3);
  GA(-1, -4, ACS_HLINE | a3);
  GA(-2, -5, ACS_PLUS | a3);

  // Feet
  GA(0, -3, '\\' | a1);
  GA(0, -2, '_' | a1);
  GA(0, -1, '_' | a1);
  GA(0, -0, ' ');
  GA(0, +1, '\\' | a1);
  GA(0, +2, '_' | a1);
  GA(0, +3, '_' | a1);

  return;
}



void draw_nose(int y, int x, int type, bool flip, uint32_t flags)
{
  int moustache;
  int nostril;
  int skin;

  if (flags & GFX_HURT)
  {
    moustache = COLOR_PAIR(PAIR_WHITE);
    nostril = COLOR_PAIR(PAIR_BROWN) | A_BOLD;
    skin = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    moustache = COLOR_PAIR(PAIR_RED);
    nostril = COLOR_PAIR(PAIR_BROWN);
    skin = COLOR_PAIR(PAIR_GREEN);
  }

  GA(0, -4, GA_PL | moustache);
  GA(0, -3, GA_PL | moustache);
  GA(0, -2, GA_PL | moustache);
  GA(0, -1, GA_PL | moustache);
  GA(0, +1, GA_PR | moustache);
  GA(0, +2, GA_PR | moustache);
  GA(0, +3, GA_PR | moustache);
  GA(0, +4, GA_PR | moustache);

  if (flags & GFX_ATTACK)
  {
    GA(-1, -2, 'O' | nostril);
    GA(-1, +2, 'O' | nostril);
  }
  else
  {
    GA(-1, -2, 'o' | nostril);
    GA(-1, +2, 'o' | nostril);
  }

  GA(-1, -4, GA_PL | skin);
  GA(-1, -3, '_' | skin);
  GA(-1, -1, '_' | skin);
  GA(-1, +0, ACS_VLINE | skin);
  GA(-1, +1, '_' | skin);
  GA(-1, +3, '_' | skin);
  GA(-1, +4, GA_PR | skin);

  GA(-2, -3, GA_FS | skin);
  GA(-2, -2, ' ' | skin);
  GA(-2, -1, ' ' | skin);
  GA(-2, +0, ACS_VLINE | skin);
  GA(-2, +1, ' ' | skin);
  GA(-2, +2, ' ' | skin);
  GA(-2, +3, GA_BS | skin);

  GA(-3, -2, GA_FS | skin);
  GA(-3, -1, ' ' | skin);
  GA(-3, +0, ACS_VLINE | skin);
  GA(-3, +1, ' ' | skin);
  GA(-3, +2, GA_BS | skin);

  GA(-4, -1, GA_FS | skin);
  GA(-4, +0, ' ' | skin);
  GA(-4, +1, GA_BS | skin);

  GA(-5, +0, '_' | skin);

  return;
}



void draw_elemental(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype cloud;
  chtype trident;
  chtype body;

  int ty;

  if (flags & GFX_HURT)
  {
    cloud = COLOR_PAIR(PAIR_RED);
    trident = COLOR_PAIR(PAIR_RED);
    body = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    cloud = COLOR_PAIR(PAIR_MAGENTA);
    trident = COLOR_PAIR(PAIR_WHITE) | A_BOLD;
    body = COLOR_PAIR(PAIR_CYAN);
  }

  ty = 0;

  GA(ty, -2, '~' | cloud);
  GA(ty, +1, '~' | cloud);
  GA(ty, +2, '~' | cloud);

  ty--;

  GA(ty, -3, GA_PL | cloud);
  GA(ty, -2, '~' | cloud);
  GA(ty, -1, GA_PL | cloud);
  GA(ty, -0, '~' | cloud);
  GA(ty, +1, '~' | cloud);
  GA(ty, +2, GA_PR | cloud);
  GA(ty, +3, GA_PR | cloud);

  ty--;

  GA(ty, -2, GA_PL | cloud);
  GA(ty, -1, '~' | cloud);
  GA(ty, -0, 'V' | body);
  GA(ty, +1, '~' | cloud);
  GA(ty, +2, GA_PR | cloud);

  ty--;

  GA(ty, -3, GA_FS | body);
  GA(ty, -2, '^' | body);
  GA(ty, -1, GA_BS | body);
  GA(ty, -0, GA_BT | body);
  GA(ty, +1, GA_FS | body);
  GA(ty, +2, '^' | body);
  GA(ty, +3, GA_BS | body);


  ty--;

  GA(ty, -2, '_' | body);
  GA(ty, -1, '_' | body);
  GA(ty, -0, 'O' | body);
  GA(ty, +1, '_' | body);
  GA(ty, +2, '_' | body);
//  GA(ty, +3, GA_FS | body);

  GA(ty + 2, +4, ACS_VLINE | trident);
  GA(ty + 1, +4, ACS_VLINE | trident);

  GA(ty - 0, +3, GA_LL | trident);
  GA(ty - 0, +4, ACS_PLUS | trident);
  GA(ty - 0, +5, GA_LR | trident);

  /*  GA(ty - 1, +3, GA_BS | trident);
  GA(ty - 0, +4, GA_BS | trident);

  GA(ty + 1, +4, '_' | trident);
  GA(ty + 1, +5, GA_BS | trident);
  GA(ty + 1, +6, '_' | trident);
  */
  return;
}




void draw_archdemon(int y, int x, int type, bool flip, uint32_t flags)
{
  int horns;
  int teeth;
  int flesh;
  int eyes;
  int tail;
  int claws;

  if (flags & GFX_HURT)
  {
    flesh = COLOR_PAIR(PAIR_RED);
    horns = COLOR_PAIR(PAIR_BROWN);
    eyes = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    flesh = COLOR_PAIR(PAIR_CYAN);
    horns = COLOR_PAIR(PAIR_GREEN) | A_BOLD;
    eyes = COLOR_PAIR(PAIR_RED) | A_BLINK;
  }

  teeth = COLOR_PAIR(PAIR_MAGENTA);
  tail = COLOR_PAIR(PAIR_BLUE) | A_BOLD;
  claws = COLOR_PAIR(PAIR_RED);

  // Horns
  GA(-7, -2, ACS_VLINE | horns);
  GA(-7, +2, ACS_VLINE | horns);

  GA(-6, -3, GA_LT | horns);
  GA(-6, -2, GA_LR | horns);
  GA(-6, -0, ACS_VLINE | horns);
  GA(-6, +2, GA_LL | horns);
  GA(-6, +3, GA_RT | horns);

  GA(-5, -4, GA_LL | horns);
  GA(-5, -3, ACS_BTEE | horns);
  GA(-5, -2, ACS_TTEE | horns);

  GA(-5, +2, ACS_TTEE | horns);
  GA(-5, +3, ACS_BTEE | horns);
  GA(-5, +4, GA_LR | horns);

  GA(-4, -2, GA_LR | horns);
  GA(-4, +2, GA_LL | horns);

  // Forehead
  GA(-5, -1, '6' | horns | A_REVERSE);
  GA(-5, -0, '6' | horns | A_REVERSE);
  GA(-5, +1, '6' | horns | A_REVERSE);

  if (flags & GFX_HURT)
  {  
    GA(-4, -1, 'x' | eyes);
    GA(-4, -0, ' ');
    GA(-4, +1, 'x' | eyes);
  }
  else
  {  
    GA(-4, -1, GA_BS | eyes);
    GA(-4, -0, ' ');
    GA(-4, +1, GA_FS | eyes);
  }

  // Mouth
  GA(-3, -3, GA_AL | flesh);
  GA(-3, +3, GA_AR | flesh);

  if (flags & GFX_ATTACK)
  {
    GA(-3, -2, '_' | teeth);
    GA(-3, -1, 'V' | teeth);
    GA(-3, -0, '_' | teeth);
    GA(-3, +1, 'V' | teeth);
    GA(-3, +2, '_' | teeth);
  }
  else
  {
    GA(-3, -2, '#' | teeth);
    GA(-3, -1, '#' | teeth);
    GA(-3, -0, '#' | teeth);
    GA(-3, +1, '#' | teeth);
    GA(-3, +2, '#' | teeth);
  }

  // Claws
  if (flags & GFX_ATTACK)
  {
    GA(-2, -4, GA_BL | flesh);
    GA(-2, -3, '_'   | flesh);
    GA(-2, -2, GA_PR | flesh);
    GA(-2, -1, '='   | flesh);
    GA(-2, -0, ' ');
    GA(-2, +1, ' ');
    GA(-2, +2, GA_PR | flesh);
    GA(-2, +3, '_'   | flesh);
    GA(-2, +4, '='   | flesh);
  }
  else
  {
    GA(-2, -4, GA_BL | flesh);
    GA(-2, -3, '_'   | flesh);
    GA(-2, -2, '\''  | flesh);
    GA(-2, -1, GA_PR | flesh);
    GA(-2, -0, ' ');
    GA(-2, +1, ' ');
    GA(-2, +2, '_'   | flesh);
    GA(-2, +3, GA_PR | flesh);
    GA(-2, +4, '\''  | flesh);
  }
    
  // Tail
  GA(-3, -8, ACS_PLUS  | tail);
  GA(-2, -8, ACS_VLINE | tail);
  GA(-2, -7, ' '       | tail);
  GA(-2, -6, GA_UL     | tail);
  GA(-2, -5, ACS_HLINE | tail);
  GA(-1, -8, GA_LL     | tail);
  GA(-1, -7, ACS_HLINE | tail);
  GA(-1, -6, GA_LR     | tail);

  // Legs
  GA(-1, -4, GA_UL | flesh);
  GA(-1, -3, GA_LR | flesh);
  GA(-1, +2, GA_LL | flesh);
  GA(-1, +3, GA_UR | flesh);

  // Claws
  GA(0, -5, GA_UL | claws);
  GA(0, -4, ACS_BTEE | flesh);
  GA(0, -3, ACS_TTEE | claws);
  GA(0, -2, GA_UR | claws);

  GA(0, +2, GA_UL | claws);
  GA(0, +3, ACS_BTEE | flesh);
  GA(0, +4, ACS_TTEE | claws);
  GA(0, +5, GA_UR | claws);

  return;
}




void draw_scaal(int y, int x, int type, bool flip, uint32_t flags)
{
}



void draw_imp(int y, int x, int type, bool flip, uint32_t flags)
{
  int skin;
  int belly;
  int claws;
  
  if (flags & GFX_HURT)
  {
    skin = COLOR_PAIR(PAIR_RED);
    belly = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    skin = COLOR_PAIR(PAIR_BROWN);
    belly = COLOR_PAIR(PAIR_GREEN);
  }

  claws = COLOR_PAIR(PAIR_CYAN);


  GA(-4, -2, '_' | skin);
  GA(-4, +2, '_' | skin);

  GA(-3, -3, GA_FS | skin);
  GA(-3, -2, '\''  | skin);
  GA(-3, -1, GA_BS | skin);
  GA(-3, -0, 'o'   | skin);
  GA(-3, +1, GA_FS | skin);
  GA(-3, +2, '\''  | skin);
  GA(-3, +3, GA_BS | skin);

  GA(-2, -1, GA_UL | skin);
  GA(-2, -0, 'V'   | belly);
  GA(-2, +1, GA_UR | skin);

  GA(-1, -1, '"' | claws);
  GA(-1, +1, '"' | claws);

  return;
}



void draw_moth(int y, int x, int type, bool flip, uint32_t flags)
{
  int wings;
  int eyes;
  int body;
  int antennae;
  
  if (flags & GFX_HURT)
  {
    wings = COLOR_PAIR(PAIR_WHITE);
    eyes = COLOR_PAIR(PAIR_RED);
    body = COLOR_PAIR(PAIR_RED);
    antennae = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    wings = COLOR_PAIR(PAIR_MAGENTA);
    eyes = COLOR_PAIR(PAIR_GREEN);
    body = COLOR_PAIR(PAIR_BROWN);
    antennae = COLOR_PAIR(PAIR_RED);
  }

//  GA(-2, -2, '\'' | body);
//  GA(-2, +2, '\'' | body);

  GA(-1, -3, '\'' | body);
  GA(-1, -2, GA_PL | body);
  GA(-1, +0, ACS_VLINE | body);
  GA(-1, +2, GA_PR | body);
  GA(-1, +3, '\'' | body);

  GA(-2, -3, GA_PL | wings);
  GA(-2, -2, 'o' | eyes);
  GA(-2, -1, GA_FS | wings);
  GA(-2, +0, ACS_PLUS | body); //ACS_VLINE | body);
  GA(-2, +1, GA_BS | wings);
  GA(-2, +2, 'o' | eyes);
  GA(-2, +3, GA_PR | wings);

  GA(-3, -2, GA_AR | wings);
//  GA(-3, -1, ACS_HLINE | wings);
  GA(-3, -1, GA_AR | body);
  GA(-3, +0, ACS_PLUS | body);
//  GA(-3, +1, ACS_HLINE | wings);
  GA(-3, +1, GA_AL | body);
  GA(-3, +2, GA_AL | wings);

  GA(-4, -4, GA_PL | wings);
  GA(-4, -3, 'o' | eyes);
  GA(-4, -2, GA_PR | body);
  GA(-4, -1, GA_BS | wings);
  GA(-4, +0, '\"' | antennae);
  GA(-4, +1, GA_FS | wings);
  GA(-4, +2, GA_PL | body);
  GA(-4, +3, 'o' | eyes);
  GA(-4, +4, GA_PR | wings);

  GA(-5, -3, '_' | wings);
  GA(-5, -2, GA_PL | antennae);
  GA(-5, +2, GA_PR | antennae);
  GA(-5, +3, '_' | wings);

  return;
}



void draw_blurk(int y, int x, int type, bool flip, uint32_t flags)
{
  int skin;
  int eyes;
  int claws;
  int teeth;

  if (flags & GFX_HURT)
  {
    skin = COLOR_PAIR(PAIR_WHITE);
    eyes = COLOR_PAIR(PAIR_WHITE);
    claws = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    skin = COLOR_PAIR(PAIR_BLACK) | A_BOLD;
    eyes = COLOR_PAIR(PAIR_RED);
    claws = COLOR_PAIR(PAIR_GREEN);
  }

  teeth = COLOR_PAIR(PAIR_GREEN) | A_BOLD;

  GA(0, -3, '_'  | skin);
  GA(0, +3, '_'  | skin);

  if (flags & GFX_BLURK_IDLE)
    return;

  GA(0, -2, GA_BS | skin);
  GA(0, -1,  ' ');
  GA(0, 0,  ' ');
  GA(0, +1,  ' ');
  GA(0, +2, GA_FS | skin);

  GA(-4, -1, '_'  | skin);
  GA(-4, 0,  '_'  | skin);
  GA(-4, +1, '_'  | skin);
  
  GA(-3, -2, GA_FS  | skin);
  GA(-3, -1, '_'  | eyes);
  GA(-3, 0,  ' '  | skin);
  GA(-3, +1, '_'  | eyes);
  GA(-3, +2, GA_BS  | skin);
  
  GA(-2, -3, GA_BS  | skin);
  GA(-2, -2, '_'  | skin);
  GA(-2, -1, '_'  | skin);
  GA(-2, 0,  '_'  | skin);
  GA(-2, +1, '_'  | skin);
  GA(-2, +2, '_'  | skin);
  GA(-2, +3, GA_FS  | skin);
  
  GA(-1, -2, GA_FS  | skin);
  GA(-1, +2, GA_BS | skin);
  
  GA(-1, -1, '\''  | teeth);
  GA(-1, 0,  ' ');
  GA(-1, +1, '\''  | teeth);

  if (flags & GFX_ATTACK2)
  {
    GA(-2, +4, GA_LR | claws);
    GA(-3, +4, ACS_VLINE | claws);
    GA(-4, +4, GA_UR | claws);
    GA(-4, +3, ACS_HLINE | claws);
    GA(-4, +2, GA_LL | claws);
    GA(-5, +2, GA_UR | claws);
    GA(-5, +1, ACS_HLINE | claws);
    GA(-5, +0, ACS_HLINE | claws);

/*    GA(-3, +3, ACS_VLINE | claws);
    GA(-4, +3, GA_UL | claws);
    GA(-4, +4, GA_UR | claws);
    GA(-3, +4, ACS_VLINE | claws);
    GA(-2, +4, ACS_VLINE | claws);
    GA(-1, +4, GA_LL | claws);*/
  }
  else if (flags & GFX_ATTACK)
  {
//    GA(-3, +3, GA_UL | claws);
//    GA(-3, +4, GA_UR | claws);
//    GA(-2, +4, GA_LL | claws);
    GA(-2, +4, ACS_HLINE | claws);
    GA(-2, +5, ACS_HLINE | claws);
    GA(-2, +6, ACS_HLINE | claws);
    GA(-2, +7, ACS_HLINE | claws);
    GA(-2, +8, ACS_HLINE | claws);
    GA(-2, +9, ACS_HLINE | claws);
    GA(-2, +10, ACS_HLINE | claws);
  }
  else
  {
    GA(-3, +3, GA_UL | claws);
    GA(-3, +4, GA_UR | claws);
    GA(-2, +4, ACS_VLINE | claws);
    GA(-1, +4, GA_LL | claws);
    GA(-1, +5, GA_LR | claws);
    GA(-2, +5, GA_UL | claws);
  }

  // Other tentacle
  GA(-3, -3, GA_UR | claws);
  GA(-3, -4, GA_UL | claws);
  GA(-2, -4, ACS_VLINE | claws);
  GA(-1, -4, GA_LR | claws);
  GA(-1, -5, GA_LL | claws);
  GA(-2, -5, GA_UR | claws);

  return;
}



void draw_dknight(int y, int x, int type, bool flip, uint32_t flags)
{
  int steed;
  int rider;
  int sword;
  bool attack;
  bool attack2;

  attack  = flags & GFX_ATTACK;
  attack2 = flags & GFX_ATTACK2;
  steed = COLOR_PAIR(PAIR_WHITE);
  sword = COLOR_PAIR(PAIR_BLUE) | A_BOLD;

  if (flags & GFX_HURT)
    rider = COLOR_PAIR(PAIR_RED);
  else
    rider = COLOR_PAIR(PAIR_CYAN);

  if (attack2)
  {
    // Raised sword

    GA(-5, -1, '_' | sword);
    GA(-5, -0, '_' | sword);
    GA(-5, +1, '_' | sword);
    GA(-5, +2, '_' | sword);
  }
  else if (attack)
  {
    // Extended sword arm

    GA(-3, +2, '^' | rider);
    GA(-3, +3, ACS_PLUS | sword);
    GA(-3, +4, ACS_HLINE | sword);
    GA(-3, +5, ACS_HLINE | sword);
  }
  else
  {
    // Sword held

    GA(-3, +2, '^' | rider);
    GA(-3, +3, ACS_PLUS | sword);
    GA(-4, +3, ACS_VLINE | sword);
    GA(-5, +3, ACS_VLINE | sword);
  }


  GA(-4, -3, GA_UL | steed);
  GA(-4, -2, ACS_HLINE | steed);
  GA(-4, -1, GA_UR | steed);
  GA(-4, -0, ' ');
  GA(-4, +1, 'o' | rider);
  GA(-4, +2, (attack2 ? GA_AR : ' ') | rider);

  GA(-3, -3, GA_LL | steed);
  GA(-3, -2, ' ' | steed);
  GA(-3, -1, ACS_VLINE | steed | A_REVERSE);
  GA(-3, +0, '^' | rider);
  GA(-3, +1, ACS_CKBOARD | rider);

  GA(-2, -1, GA_LT | steed | A_REVERSE);
  GA(-2, -0, GA_PL | rider);
  GA(-2, +1, ACS_HLINE | steed | A_REVERSE);
  GA(-2, +2, ACS_TTEE | steed | A_REVERSE);
  GA(-2, +3, GA_UR | steed | A_REVERSE);

  GA(-1, -2, GA_FS | steed);
  GA(-1, -1, ' ');
  GA(-1, -0, ACS_VLINE | steed);
  GA(-1, +1, ' ');
  GA(-1, +2, ACS_VLINE | steed);
  GA(-1, +3, ACS_VLINE | steed);

  GA(-0, -2, GA_BS | steed);
  GA(-0, -1, ' ');
  GA(-0, -0, ACS_VLINE | steed);
  GA(-0, +1, ' ');
  GA(-0, +2, ACS_VLINE | steed);
  GA(-0, +3, ACS_VLINE | steed);
        
  return;
}




void draw_giant(int y, int x, int type, bool flip, uint32_t flags)
{
  int c1;
  int c2;

  if (flags & GFX_HURT)
  {
    c1 = COLOR_PAIR(PAIR_RED);
    c2 = COLOR_PAIR(PAIR_WHITE);
  }
  else
  {
    c1 = COLOR_PAIR(PAIR_GREEN);
    c2 = COLOR_PAIR(PAIR_BROWN);
  }

  GA(-4, -0, 'O' | c1);

  GA(-3, -1, GA_FS | c1);
  GA(-3, -0, 'H'   | c2);

  GA(-2, -0, 'V'   | c2 | A_REVERSE);

  GA(-1, -1, GA_FS | c1);
  GA(-1, -0, ' ');
  GA(-1, +1, GA_BS | c1);

  GA(-0, -1, ACS_CKBOARD | c1);
  GA(-0, -0, ' ');
  GA(-0, +1, ACS_CKBOARD | c1);

  // Weapon
  if (flags & GFX_ATTACK2)
  {
    GA(-4, +1, GA_FS | c1);
    GA(-5, +2, GA_AR | c1);
    GA(-5, +1, '_'   | c2);
    GA(-5, -0, '_'   | c2);
    GA(-5, -1, ACS_DIAMOND | c2);
  }
  else if (flags & GFX_ATTACK)
  {
    GA(-3, +1, '^' | c1);
    GA(-3, +2, ACS_HLINE | c2);
    GA(-3, +3, ACS_DIAMOND | c2);
  }
  else
  {
    GA(-3, +1, GA_BS | c1);
    GA(-3, +2, ACS_VLINE | c2);
    GA(-4, +2, ACS_DIAMOND | c2);
  }

  return;
}



void draw_ghoul(int y, int x, int type, bool flip, uint32_t flags)
{
  int skin;

  if (flags & GFX_HURT)
    skin = COLOR_PAIR(PAIR_RED);
  else
    skin = COLOR_PAIR(PAIR_GREEN);

  if (flags & GFX_GHOUL_DIG1)
  {
  }
  else if (flags & GFX_GHOUL_DIG2)
  {
    GA(0, -1, ' ' | skin);
    GA(0, -0, '_' | skin);
    GA(0, +1, GA_FS | skin);
//    GA(0, +2, '"' | skin);
  }
  else if (flags & GFX_GHOUL_DIG3)
  {
//    GA(0, -2, '"' | skin);
    GA(0, -1, GA_BS | skin);
    GA(0, -0, 'o' | skin);
    GA(0, +1, '_' | skin);
  }
  else if (flags & GFX_GHOUL_DIG4)
  {
    GA(-1, -0, 'o' | skin);

    GA(0, -1, GA_AL | skin);
    GA(0, -0, ACS_CKBOARD | skin);
    GA(0, +1, GA_BS | skin);
  }
  else
  {
    // normal look
    GA(-2, -1, '_' | skin);
    GA(-2, -0, 'o' | skin);
    GA(-2, +1, '_' | skin);
    
    GA(-1, -2, '"' | skin);
    GA(-1, -1, ' ' | skin);
    GA(-1, -0, ACS_CKBOARD | skin);
    GA(-1, +1, ' ' | skin);
    GA(-1, +2, '"' | skin);
    
    GA(0, -1, GA_FS | skin);
    GA(0, -0, ' ');
    GA(0, +1, GA_BS | skin);
  }

  return;
}



void draw_snake(int y, int x, int type, bool flip, uint32_t flags)
{
  int c;
  int hc;

  if (flags & GFX_HURT)
  {
    c  = COLOR_PAIR(PAIR_RED);
    hc = COLOR_PAIR(PAIR_RED);
  }
  else
  {
    c  = COLOR_PAIR(PAIR_GREEN);
    hc = COLOR_PAIR(PAIR_GREEN_ON_RED);
  }

  
  GA(-1, -2, GA_UL | c);
  GA(-1, -1, GA_UR | c);
  GA(-1, -0, GA_UL | c);
  GA(-1, +1, GA_UR | c);
  GA(-1, +2, GA_BS | hc | A_REVERSE);
  GA(-1, +3, GA_FS | hc | A_REVERSE);
  
  GA(-0, -3, ACS_HLINE | c);
  GA(-0, -2, GA_LR | c);
  GA(-0, -1, GA_LL | c);
  GA(-0, -0, GA_LR | c);
  GA(-0, +1, GA_LL | c);
  GA(-0, +2, GA_LR | c);

  
/*  GU(-1, -2, "╭", c);
  GU(-1, -1, "╮", c);
  GU(-1, -0, "╭", c);
  GU(-1, +1, "╮", c);
  GA(-1, +2, GA_BS | hc | A_REVERSE);
  GA(-1, +3, GA_FS | hc | A_REVERSE);
  
  GA(-0, -3, ACS_HLINE | c);
  GU(-0, -2, "╯", c);
  GU(-0, -1, "╰", c);
  GU(-0, -0, "╯", c);
  GU(-0, +1, "╰", c);
  GU(-0, +2, "╯", c);*/
  
  return;
}



void draw_fish(int y, int x, int type, bool flip, uint32_t flags)
{
  int c;

  c = 0;
  
  if (flags & GFX_ATTACK)
  {
    GA(-0, -0, GA_BS | c);
    GA(-0, +1, '_'   | c);
    GA(-0, +2, GA_FS | c);
//    GA(-0, +3, ' '   | c);

    GA(-1, -3, GA_PL | c);
    GA(-1, -2, GA_FS | c);
    GA(-1, -1, GA_BS | c);
    GA(-1, -0, ' '   | c);
    GA(-1, +1, GA_BS | c);
    GA(-1, +2, '_'   | c);
    GA(-1, +3, ' '   | c);
    
    GA(-2, -3, GA_PL | c);
    GA(-2, -2, ' '   | c);
    GA(-2, -1, ' '   | c);
    GA(-2, -0, GA_BS | c);
  }
  else
  {
    GA(-1, -3, GA_PL | c);
    GA(-1, -2, GA_FS | c);
    GA(-1, -1, GA_BS | c);
    GA(-1, -0, '_'   | c);
    GA(-1, +1, '_'   | c);
    GA(-1, +2, '_'   | c);
    GA(-1, +3, GA_FS | c);
    
    GA(-2, -3, GA_PL | c);
    GA(-2, -2, ' '   | c);
    GA(-2, -1, ' '   | c);
    GA(-2, -0, GA_PL | c);
    GA(-2, +1, ' '   | c);
    GA(-2, +2, '_'   | c);
    GA(-2, +3, '_'   | c);
  }

  if (flags & GFX_HURT)
  {
    GA(-3, -3, GA_PL | c);
    GA(-3, -2, GA_BS | c);
    GA(-3, -1, GA_FS | c);
    GA(-3, -0, ' '   | c);
    GA(-3, +1, 'x'   | c);
    GA(-3, +2, 'x'   | c);
    GA(-3, +3, GA_BS | c);
  }
  else
  {
    GA(-3, -3, GA_PL | c);
    GA(-3, -2, GA_BS | c);
    GA(-3, -1, GA_FS | c);
    GA(-3, -0, ' '   | c);
    GA(-3, +1, ','   | c);
    GA(-3, +2, ','   | c);
    GA(-3, +3, GA_BS | c);
  }

  GA(-4, -0, '_'   | c);
  GA(-4, +1, '_'   | c);
  GA(-4, +2, '_'   | c);

  return;
}



void draw_crab(int y, int x, int type, bool flip, uint32_t flags)
{
  int c;

  c = COLOR_PAIR(PAIR_RED);

  GA(-0, -3, GA_AL | c);
  GA(-0, -2, GA_AL | c);
  GA(-0, +2, GA_AR | c);
  GA(-0, +3, GA_AR | c);

  GA(-1, -2, GA_PL | c);
  GA(-1, -1, '_'   | c);
  GA(-1, -0, '^'   | c);
  GA(-1, +1, '_'   | c);
  GA(-1, +2, GA_PR | c);

  if (flags & GFX_HURT)
  {
    GA(-2, -1, 'x'   | c);
    GA(-2, -0, ' '   | c);
    GA(-2, +1, 'x'   | c);
  }
  else
  {
    GA(-2, -1, '.'   | c);
    GA(-2, -0, ' '   | c);
    GA(-2, +1, '.'   | c);
  }

  if (flags & GFX_ATTACK2)
  {
    GA(-2, -3, '_'   | c);
    GA(-2, -4, GA_BS | c);
    GA(-3, -3, GA_AR | c);
    GA(-3, -4, ' '   | c);
    GA(-3, -5, GA_BS | c);
    GA(-4, -4, 'v'   | c);
    GA(-4, -5, GA_FS | c);

    GA(-2, +3, '_'   | c);
    GA(-2, +4, GA_FS | c);
    GA(-3, +3, GA_AL | c);
    GA(-3, +4, ' '   | c);
    GA(-3, +5, GA_FS | c);
    GA(-4, +4, 'v'   | c);
    GA(-4, +5, GA_BS | c);
  }
  else
  {
    // Inactive claw
    GA(-1, -3, GA_FS | c);
    GA(-1, -4, '_'   | c);
    GA(-1, -5, GA_BS | c);
    GA(-2, -4, GA_AR | c);
    GA(-2, -5, ' '   | c);
    GA(-2, -6, GA_BS | c);
    GA(-3, -5, 'v'   | c);
    GA(-3, -6, GA_FS | c);
    
    if (flags & GFX_ATTACK)
    {
      GA(-0, -3, GA_FS | c);
      GA(-0, -2, GA_FS | c);
      
      GA(-1, +3, GA_FS | c);
      GA(-1, +4, ' '   | c);
      GA(-1, +5, GA_BS | c);
      GA(-1, +6, 'V'   | c);
      GA(-2, +3, GA_FS | c);
      GA(-2, +4, '_'   | c);
      GA(-2, +5, '^'   | c);
      GA(-2, +6, GA_BS | c);
      GA(-2, +4, '_'   | c);
      GA(-2, +5, '_'   | c);
    }
    else
    {
      GA(-1, +3, GA_BS | c);
      GA(-1, +4, '_'   | c);
      GA(-1, +5, GA_FS | c);
      GA(-2, +4, GA_AL | c);
      GA(-2, +5, ' '   | c);
      GA(-2, +6, GA_FS | c);
      GA(-3, +5, 'v'   | c);
      GA(-3, +6, GA_BS | c);
    }
  }
    
  return;
}



void draw_spider(int y, int x, int type, bool flip, uint32_t flags)
{
  int c;

  if (flags & GFX_HURT)
    c = COLOR_PAIR(PAIR_RED);
  else if (flags & GFX_ATTACK)
    c = COLOR_PAIR(PAIR_WHITE);
  else
    c = COLOR_PAIR(PAIR_BROWN);

  GA(-2, -3, GA_UL      | c);
  GA(-2, -2, ACS_HLINE  | c);
  GA(-2, -1, GA_UR      | c);
  GA(-2, +1, GA_UL      | c);
  GA(-2, +2, ACS_HLINE  | c);
  GA(-2, +3, GA_UR      | c);

  GA(-1, -3, ACS_VLINE   | c);
  GA(-1, -2, GA_UL       | c);
  GA(-1, -1, ACS_CKBOARD | c);
  GA(-1, -0, '*'         | COLOR_PAIR(PAIR_RED));
  GA(-1, +1, ACS_CKBOARD | c);
  GA(-1, +2, GA_UR       | c);
  GA(-1, +3, ACS_VLINE   | c);

  GA(-0, -3, ACS_VLINE | c);
  GA(-0, -2, ACS_VLINE | c);
  GA(-0, -1, GA_PL     | COLOR_PAIR(PAIR_RED));
  GA(-0, +1, GA_PR     | COLOR_PAIR(PAIR_RED));
  GA(-0, +2, ACS_VLINE | c);
  GA(-0, +3, ACS_VLINE | c);

  return;
}



void draw_brickwall(int y, int x, int type, bool flip, uint32_t flags)
{
  chtype c;
  int i;
  int ty;
  
  if (flags & GFX_HURT)
    c = COLOR_PAIR(PAIR_RED_ON_WHITE);
  else
    c = COLOR_PAIR(PAIR_WHITE) | A_REVERSE;

  ty = 0;

  for (i = 0; i < 3; i++)
  {
    GA(ty, -4, GA_LT | c);
    GA(ty, -3, GA_BT | c);
    GA(ty, -2, GA_TT | c);
    GA(ty, -1, GA_BT | c);
    GA(ty, +0, GA_TT | c);
    GA(ty, +1, GA_BT | c);
    GA(ty, +2, GA_TT | c);
    GA(ty, +3, GA_BT | c);
    GA(ty, +4, GA_RT | c);

    ty--;

    GA(ty, -4, GA_LT | c);
    GA(ty, -3, GA_TT | c);
    GA(ty, -2, GA_BT | c);
    GA(ty, -1, GA_TT | c);
    GA(ty, +0, GA_BT | c);
    GA(ty, +1, GA_TT | c);
    GA(ty, +2, GA_BT | c);
    GA(ty, +3, GA_TT | c);
    GA(ty, +4, GA_RT | c);

    ty--;
  }

  return;
}



void draw_lich(int y, int x, int type, bool flip, uint32_t flags)
{
  int skin;
  int a1;
  int a2;
  int a3;
  int attack;

  attack = flags & GFX_ATTACK;

  if (flags & GFX_HURT)
  {
    skin = COLOR_PAIR(PAIR_RED);
    a1 = COLOR_PAIR(PAIR_CYAN_ON_BLUE);
    a2 = COLOR_PAIR(PAIR_RED);
    a3 = COLOR_PAIR(PAIR_BLUE);
  }
  else
  {
    skin = COLOR_PAIR(PAIR_WHITE);
    a1 = COLOR_PAIR(PAIR_CYAN_ON_BLUE);
    a2 = COLOR_PAIR(PAIR_BLUE) | A_BOLD;
    a3 = COLOR_PAIR(PAIR_BLUE);
  }

  GA(-3, -1, GA_UL | a3);
  GA(-3, -0, 'O' | skin);
  GA(-3, +1, GA_UR | a3);

  if (attack)
  {
    GA(-3, +2, GA_FS | a2);
    GA(-4, +3, ACS_PLUS | skin);
    GA(-3, +3, ACS_VLINE | skin);
    GA(-2, +3, ACS_VLINE | skin);
    GA(-1, +3, ACS_VLINE | skin);
  }
  else
  {
    GA(-3, +3, ACS_PLUS | skin);
    GA(-2, +3, ACS_VLINE | skin);
    GA(-1, +3, ACS_VLINE | skin);
    GA(-0, +3, ACS_VLINE | skin);
  }

  GA(-2, -2, GA_AL | a2);
  GA(-2, -1, GA_BS | a2);
  GA(-2, -0, GA_BS | a1);
  GA(-2, +1, GA_FS | a2);
  GA(-2, +2, (attack ? ' ' : '^') | a2);

  GA(-1, -1, GA_FS | a2);
  GA(-1, -0, '_' | a1);
  GA(-1, +1, GA_BS | a2);

  GA(0, -1, ACS_VLINE | skin);
  GA(0, 0, ' ');
  GA(0, +1, ACS_VLINE | skin);

  return;
}



void draw_human(int y, int x, int type, bool flip, uint32_t flags)
{
  bool lbicp = false;
  bool rbicp = false;
  int shd_type;
  int armor_type;
  bool shd_up = false;
  int weapon = 0;
  bool swap;
  bool attack = false;
  bool bow = false;
  uint32_t fall = 0;
  uint32_t climb = 0;
  int skin = PAIR_WHITE;
  int dive = false;

  dive = flags & GFX_HUMAN_DIVE;

  shd_type = flags & (GFX_HUMAN_SHIELD1 | GFX_HUMAN_SHIELD2);
  shd_up = flags & GFX_HUMAN_SHIELD_UP;
  armor_type = flags & (GFX_HUMAN_ARMOR1 |
			GFX_HUMAN_ARMOR2 |
			GFX_HUMAN_ARMOR3);
  weapon = flags & GFX_HUMAN_WEAPONS;
  attack = flags & GFX_ATTACK;
  bow = flags & GFX_HUMAN_BOW;

  rbicp = attack || (weapon ? true : false) || shd_up;
  lbicp = shd_type;

  climb = flags & (GFX_HUMAN_CLIMB1 | GFX_HUMAN_CLIMB2);
  fall = flags & (GFX_HUMAN_FALL1 | GFX_HUMAN_FALL2);

  if (flip)
  {
    swap = rbicp;
    rbicp = lbicp;
    lbicp = swap;
  }

  if (flags & GFX_HURT)
    skin = COLOR_PAIR(PAIR_RED);
  else if (flags & GFX_HUMAN_GNOBLIN)
    skin = COLOR_PAIR(PAIR_GREEN);
  else
    skin = COLOR_PAIR(PAIR_WHITE);

  // Torso

  if (armor_type == (GFX_HUMAN_ARMOR3 | GFX_HUMAN_ARMOR1))
    GA(-1, 0, ACS_CKBOARD | COLOR_PAIR(PAIR_MAGENTA));
  else if (armor_type == GFX_HUMAN_ARMOR3)
    GA(-1, 0, ACS_CKBOARD | COLOR_PAIR(PAIR_RED));
  else if (armor_type == (GFX_HUMAN_ARMOR1 | GFX_HUMAN_ARMOR2))
    GA(-1, 0, ACS_CKBOARD | COLOR_PAIR(PAIR_BLUE) | A_BOLD);
  else if (armor_type == GFX_HUMAN_ARMOR2)
    GA(-1, 0, ACS_CKBOARD | COLOR_PAIR(PAIR_WHITE));
  else if (armor_type == GFX_HUMAN_ARMOR1)
    GA(-1, 0, ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN));
  else
    GA(-1, 0, 'T' | skin); //GU(-1, 0, "ℿ", 0);//

  if (dive)
  {
    GA(0, 0, '@' | skin);
    
    GA((climb == GFX_HUMAN_CLIMB1 ? -1 : 0), -1, GA_AL);
    GA((climb == GFX_HUMAN_CLIMB2 ? -1 : 0), +1, GA_AR);

    GA(-2, -1, GA_BS | skin);
    GA(-2, -0, ' '   | skin);
    GA(-2, +1, GA_FS | skin);

    return;
  }
  
  // Head

  if (flags & GFX_HUMAN_PLAYER)
    GA(-2, 0, '@' | skin);
  else
    GA(-2, 0, 'o' | skin);
  
  if (fall)
  {
    GA(-2, -1, (fall == GFX_HUMAN_FALL1 ? GA_BS : '_'));
    GA(-2, +1, (fall == GFX_HUMAN_FALL2 ? GA_FS : '_'));
  }
  else if (climb)
  {
    GA((climb == GFX_HUMAN_CLIMB1 ? -1 : -2), -1, GA_AL);
    GA((climb == GFX_HUMAN_CLIMB2 ? -1 : -2), +1, GA_AR);
  }
  else if (bow && !attack)
  {
    if (type == MOB_PLAYER)
    {
      GA(-1, -1, GA_AL | skin);
      GA(-1, +1, '^'   | skin);
    }
    else
    {
      GA(-1, -1, GA_BL | skin);
      GA(-1, +1, ACS_HLINE | skin);
    }
  }
  else if (weapon == GFX_HUMAN_FLAIL && (flags & GFX_ATTACK2))
  {
    GA(-2, +1, GA_AR | skin);
  }
  else
  {
    if (flip)
    {
      GA(-1, -1, (rbicp ? '^' : '>') | skin);
      GA(-1, +1, (lbicp ? '^' : '<') | skin);
    }
    else
    {
      GA(-1, -1, (lbicp ? '^' : '<') | skin);
      GA(-1, +1, (rbicp ? '^' : '>') | skin);
    }
  }
  
  GA(0, -1, GA_FS | skin);
  GA(0, -0, ' '   | skin);
  GA(0, +1, (attack ? GA_AR : GA_BS) | skin);

  if (climb || fall)
  {
    return;
  }

  if (shd_type)
  {
    int shd_c;

    if (shd_type == (GFX_HUMAN_SHIELD1 | GFX_HUMAN_SHIELD2))
      shd_c = COLOR_PAIR(PAIR_RED);
    else if (shd_type == GFX_HUMAN_SHIELD2)
      shd_c = COLOR_PAIR(PAIR_WHITE);
    else
      shd_c = COLOR_PAIR(PAIR_BROWN);

    if (!shd_up)
    {
      GA(-1, -2, 'O' | shd_c);
    }
    else
    {
      GA(-1, +2, GA_LR | shd_c | A_REVERSE);
      GA(-2, +2, GA_UR | shd_c | A_REVERSE);

      // Don't draw a weapon if we draw a blocking shield
      return;
    }
  }
      
  int wpn_c;
  
  if (flags & GFX_HUMAN_MWPN2)
    wpn_c = COLOR_PAIR(PAIR_GREEN | A_BOLD);
  else if (flags & GFX_HUMAN_MWPN)
    wpn_c = COLOR_PAIR(PAIR_MAGENTA);
  else if (flags & GFX_HUMAN_PLAYER)
    wpn_c = COLOR_PAIR(PAIR_RED);
  else
    wpn_c = COLOR_PAIR(PAIR_CYAN);

  if (weapon == GFX_HUMAN_SWORD || weapon == GFX_HUMAN_DAGGER)
  {
    // Add an extra tip for the sword

    if (attack)
    {
      GA(-1, +2, ACS_PLUS | wpn_c);
      GA(-1, +3, ACS_HLINE | wpn_c);

      if (weapon == GFX_HUMAN_SWORD)
	GA(-1, +4, ACS_HLINE | wpn_c);
    }
    else
    {
      GA(-1, +2, ACS_PLUS | wpn_c);
      GA(-2, +2, ACS_VLINE | wpn_c);

      if (weapon == GFX_HUMAN_SWORD)
	GA(-3, +2, ACS_VLINE | wpn_c);
    }
  }
  else if (weapon == GFX_HUMAN_MACE)
  {
    if (attack)
    {
      GA(-1, +2, ACS_HLINE | wpn_c);
      GA(-1, +3, ACS_DIAMOND | wpn_c);
    }
    else
    {
      GA(-1, +2, ACS_VLINE | wpn_c);
      GA(-2, +2, ACS_DIAMOND | wpn_c);
    }
  }
  else if (bow && !attack)
  {
    GA(-2, +2, GA_PR | wpn_c);
    GA(-1, +2, GA_AR | wpn_c);
    GA(-0, +2, GA_PR | wpn_c);
  }
  else if (weapon == GFX_HUMAN_SPEAR)
  {
    if (attack)
    {
      GA(-1, +2, ACS_HLINE | wpn_c);
      GA(-1, +3, ACS_HLINE | wpn_c);
      GA(-1, +4, ACS_HLINE | wpn_c);
      GA(-1, +5, ACS_HLINE | wpn_c);
    }
    else
    {
      GA(-0, +2, ACS_VLINE | wpn_c);
      GA(-1, +2, ACS_VLINE | wpn_c);
      GA(-2, +2, ACS_VLINE | wpn_c);
      GA(-3, +2, ACS_VLINE | wpn_c);
    }
  }
  else if (weapon == GFX_HUMAN_AXE)
  {
    if (attack)
    {
      GA(-1, +2, ACS_HLINE | wpn_c);
      GA(-1, +3, ACS_HLINE | wpn_c);
//      GA(-2, +4, '^'       | wpn_c);
      GA(-1, +4, 'X'       | wpn_c);
      GA(-0, +4, 'V'       | wpn_c);
    }
    else
    {
      GA(-1, +2, ACS_VLINE | wpn_c);
      GA(-2, +2, ACS_VLINE | wpn_c);
//      GA(-3, +1, GA_AL     | wpn_c);
      GA(-3, +2, 'X'       | wpn_c);
      GA(-3, +3, GA_AR     | wpn_c);
    }
  }
  else if (weapon == GFX_HUMAN_FLAIL)
  {
    if (flags & GFX_ATTACK2)
    {
      GA(-3, -1, '_' | wpn_c);
      GA(-3, -0, '_' | wpn_c);
      GA(-3, +1, '_' | wpn_c);

      GA(-3, -2, ACS_BULLET  | wpn_c);
      GA(-2, -3, ACS_BULLET  | wpn_c);
      GA(-1, -3, ACS_DIAMOND | wpn_c);
    }
    else if (attack)
    {
      GA(-1, +2, GA_FS | wpn_c);

      GA(-2, +2, '.' | wpn_c);
      GA(-2, +3, '.' | wpn_c);
      GA(-2, +4, ACS_BULLET | wpn_c);
      GA(-2, +5, ACS_BULLET | wpn_c);
      GA(-2, +6, ACS_DIAMOND | wpn_c);
    }
    else
    {
      GA(-1, +2, ACS_VLINE    | wpn_c);
      GA(-2, +2, ACS_BULLET   | wpn_c);
      GA(-2, +3, '.'          | wpn_c);
      GA(-1, +3, ACS_DIAMOND  | wpn_c);
    }
  }
  else if (attack)
  {
    // Unarmed attack
    GA(-2, +2, '*' | COLOR_PAIR(PAIR_WHITE));
  }

return;
}



/*
  Draws the frame aroudn the board window
*/
void draw_frames()
{
  int y;
  int x;
  int l;

  l = (COLS - BOARD_W) / 2;

  for (y = BOARD_T + 1; y < BOARD_T + BOARD_H + 1; y++)
  {
    mvwaddch(stdscr, y, l - 1,
	     ACS_VLINE | COLOR_PAIR(PAIR_CYAN));
    mvwaddch(stdscr, y, l + BOARD_W + 1,
	     ACS_VLINE | COLOR_PAIR(PAIR_MAGENTA));
  }

  for (x = l; x < l + BOARD_W + 1; x++)
  {
    mvwaddch(stdscr, BOARD_T, x,
	     ACS_HLINE | COLOR_PAIR(PAIR_CYAN));
    mvwaddch(stdscr, BOARD_T + BOARD_H + 1, x,
	     ACS_HLINE | COLOR_PAIR(PAIR_MAGENTA));
  }

  mvwaddch(stdscr, BOARD_T, l - 1,
	   ACS_ULCORNER | COLOR_PAIR(PAIR_CYAN));

  mvwaddch(stdscr, BOARD_T, l + BOARD_W + 1,
	   ACS_URCORNER | COLOR_PAIR(PAIR_CYAN));

  mvwaddch(stdscr, BOARD_T + BOARD_H + 1, l + BOARD_W + 1,
	   ACS_LRCORNER | COLOR_PAIR(PAIR_MAGENTA));

  mvwaddch(stdscr, BOARD_T + BOARD_H + 1, l - 1,
	   ACS_LLCORNER | COLOR_PAIR(PAIR_MAGENTA));

  refresh();

  return;
}



/*
  Updates the message below the board window
*/
void draw_lowmsg(void)
{
  wmove(lowwin, 0, 1);
  waddstr(lowwin, lowmsg);
  wclrtoeol(lowwin);
  wrefresh(lowwin);
}



void make_bar(WINDOW * win, int y,
	      char * title, int amount,
	      int c1, int c2, int c3, int c4)
{
  int overflow;
  int v;
  int w;
  int i;
  int bg;
  int fg;

  wmove(win, y, 0);

  wprintw(lowwin, "%12s  ", title);

  w = 40;
  v = amount / w;

/*  if (amount > 100)
    overflow = w * 2;
  else if (amount > 60)
    overflow = amount % 60;
    else
    overflow = (amount % w) * 2;*/

  if (amount >= w * 4)
    overflow = w;
  else
    overflow = (amount % w);
  
  if (v >= 3)
  {
    bg = c3;
    fg = c4;
  }
  else if (v == 2)
  {
    bg = c2;
    fg = c3;
  }
  else if (v == 1)
  {
    bg = c1;
    fg = c2;
  }
  else
  {
    bg = 0;
    fg = c1;
  }

  for (i = 0; i < w; i++)
  {
    if (i < overflow)
    {
      waddch(lowwin, ACS_CKBOARD | fg);
    }
    else if (bg)
    {
      waddch(lowwin, ACS_CKBOARD | bg);
    }
  }

  wclrtoeol(lowwin);

  if (amount >= w * 4)
  {
    wmove(win, y, 55);
    waddch(lowwin, '+');
  }

  return;
}


void breath_bar(WINDOW * win, int y, int amount)
{
  int i;

  wmove(win, y, 0);

  if (amount <= 0)
  {
    wattron(lowwin, COLOR_PAIR(PAIR_RED) | A_BLINK);
    wprintw(lowwin, "%12s  ", "BREATH");
    wattrset(lowwin, 0);
    wclrtoeol(lowwin);
  }
  else
  {
    wprintw(lowwin, "%12s  ", "BREATH");

    for (i = 0; i < MIN(40, amount); i++)
      waddch(lowwin, 'o' | COLOR_PAIR(PAIR_CYAN));

    wclrtoeol(lowwin);

    if (amount > 40)
    {
      wmove(lowwin, y, 14);
      
      for (i = 40; i < amount; i++)
	waddch(lowwin, 'O' | COLOR_PAIR(PAIR_GREEN));
    }
  }

  return;
}




void force_breath_bar(mob_t * m)
{
  breath_bar(lowwin, 2, m->breath);
  wrefresh(lowwin);
  return;
}



void draw_bars(void)
{
  make_bar(lowwin, 1,
	   "HEALTH", player->hp,
	   COLOR_PAIR(PAIR_RED),
	   COLOR_PAIR(PAIR_RED) | A_BOLD,
	   COLOR_PAIR(PAIR_BROWN) | A_BOLD,
	   COLOR_PAIR(PAIR_WHITE));

  if (water_join(gtile(player->y, player->x)))
    breath_bar(lowwin, 2, player->breath);
  else
  {
    wmove(lowwin, 2, 0);
    wclrtoeol(lowwin);
  }
  
  if (enemy_bar > 0)
  {
    int enemy;

    enemy = game->mob[enemy_bar].type;

    if (enemy > MOB_NONE)
    {
      make_bar(lowwin, 3,
	       (game->hallucination ? "???" : mob_name[enemy]),
	       game->mob[enemy_bar].hp,
	       COLOR_PAIR(PAIR_CYAN),
	       COLOR_PAIR(PAIR_BLUE) | A_BOLD,
	       COLOR_PAIR(PAIR_MAGENTA),
	       COLOR_PAIR(PAIR_BLACK) | A_BOLD);
    }
  }
  else
  {
    wmove(lowwin, 3, 0);
    wclrtoeol(lowwin);
  }

  wrefresh(lowwin);

  return;
}




void draw_stats()
{
  werase(stats);

  wmove(stats, 3, 0);
  wprintw(stats, "FLOOR %d", game->current_floor);

  wmove(stats, 1, BOARD_W - 18);
  wprintw(stats, "LEVEL %2d", game->player_level);

  wmove(stats, 2, BOARD_W - 27);
  wprintw(stats, "%6d/%6d EXP", game->player_exp, game->player_tnl);

  wmove(stats, 3, BOARD_W - 20);
  wprintw(stats, "%5d GOLD", game->player_gold);

  wmove(stats, 1, BOARD_W - 7);
  wprintw(stats, " ST %2d", player->strength);

  wmove(stats, 2, BOARD_W - 7);
  wprintw(stats, " SP %2d", player->speed);

  wmove(stats, 3, BOARD_W - 7);
  waddch(stats, (game->skill_lockpick ? 'L' : ' '));
  waddch(stats, (game->skill_detect_traps ? 'T' : ' '));

//  wattron(stats, COLOR_PAIR(PAIR_RED));
  //mvwaddstr(stats, 0, 0, "ᛅᚼᚶᚭᚨᚩᚢᛄ☭⬉⬅⬍∑∞≈≣⊂█▍▜▙↝↝↝†⁇✝✠✫Φ♥♂¶▲▼");
//  wattrset(stats, 0);

  werase(rwin);
  wattron(rwin, COLOR_PAIR(PAIR_BLACK) | A_BOLD);

  if (game->has_torch)
    waddstr(rwin, "TORCH\n");

  if (game->has_scuba)
    waddstr(rwin, "SCUBA\n");

  wrefresh(stats);
  wrefresh(rwin);

  return;
}



void mob_text(mob_t * mob, char * msg)
{
  int l;
  int offset;

  l = strlen(msg);

  // int truncation discards decimals
  offset = l / 2;

  wmove(board, mob->y - 4 - view_y, mob->x - view_x - offset);
  wattrset(board, 0);
  waddstr(board, msg);
  wrefresh(board);
  opause();

  return;
}



void lightning(int y, int x)
{
  int a;

  a = COLOR_PAIR(PAIR_LIGHTNING) | A_BOLD | A_REVERSE;

  mvwaddch(board, y - 5, x - 1, '_' | a);
  mvwaddch(board, y - 5, x - 0, '_' | a);
  mvwaddch(board, y - 5, x + 1, '/' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 4, x - 1, '\\' | a);
  mvwaddch(board, y - 4, x - 0, '_' | a);
  mvwaddch(board, y - 4, x + 1, '_' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 3, x - 1, '_' | a);
  mvwaddch(board, y - 3, x - 0, '_' | a);
  mvwaddch(board, y - 3, x + 1, '/' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 2, x - 1, '\\' | a);
  mvwaddch(board, y - 2, x - 0, '_' | a);
  mvwaddch(board, y - 2, x + 1, '_' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 1, x - 1, '_' | a);
  mvwaddch(board, y - 1, x - 0, '_' | a);
  mvwaddch(board, y - 1, x + 1, '/' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 0, x - 1, '\\' | a);
  mvwaddch(board, y - 0, x - 0, '_' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 5, x + 2, '*' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 3, x - 2, '*' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 2, x + 3, '*' | a);
  wrefresh(board); lpause();

  mvwaddch(board, y - 0, x - 3, '*' | a);
  wrefresh(board); lpause();

  return;
}



void explosion(int y, int x)
{
  wmove(board, y, x);
  waddch(board, ACS_CKBOARD | COLOR_PAIR(PAIR_BROWN_ON_RED) | A_BOLD);
  wrefresh(board);
  lpause();

  wmove(board, y - 1, x);
  waddch(board, '*' | COLOR_PAIR(PAIR_BROWN_ON_RED) | A_BOLD);
  wmove(board, y + 1, x);
  waddch(board, '*' | COLOR_PAIR(PAIR_BROWN_ON_RED) | A_BOLD);
  wrefresh(board);
  lpause();

  wmove(board, y, x - 1);
  waddch(board, '*' | COLOR_PAIR(PAIR_BROWN_ON_RED) | A_BOLD);
  wmove(board, y, x + 1);
  waddch(board, '*' | COLOR_PAIR(PAIR_BROWN_ON_RED) | A_BOLD);
  wrefresh(board);
  lpause();

  wmove(board, y - 1, x - 1);
  waddch(board, ACS_BULLET | COLOR_PAIR(PAIR_RED_ON_BROWN));
  wmove(board, y + 1, x + 1);
  waddch(board, ACS_BULLET | COLOR_PAIR(PAIR_RED_ON_BROWN));
  wrefresh(board);
  lpause();

  wmove(board, y + 1, x - 1);
  waddch(board, ACS_BULLET | COLOR_PAIR(PAIR_RED_ON_BROWN));
  wmove(board, y - 1, x + 1);
  waddch(board, ACS_BULLET | COLOR_PAIR(PAIR_RED_ON_BROWN));
  wrefresh(board);
  lpause();

  flush_input();

  return;
}
