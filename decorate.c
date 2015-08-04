#include "basment.h"


void decorate(int y, int x, int type)
{
  switch (type)
  {
  case DEC_TRAPDOOR:
    stile(y + 1, x - 1, TL_TRAPDOOR_S);
    stile(y + 1, x + 1, TL_TRAPDOOR_S);
    stile(y + 1, x, TL_TRAPDOOR_M);
    
    stile(y, x - 3, TL_STOP);
    stile(y, x + 3, TL_STOP);
    break;

  case DEC_BRICKS:
    stile(y + 1, x - 4, TL_WALL_BT);
    stile(y + 1, x - 2, TL_WALL_BT);
    stile(y + 1, x + 0, TL_WALL_BT);
    stile(y + 1, x + 2, TL_WALL_BT);
    stile(y + 1, x + 4, TL_WALL_BT);
    stile(y - 6, x - 4, TL_WALL_TT);
    stile(y - 6, x - 2, TL_WALL_TT);
    stile(y - 6, x + 0, TL_WALL_TT);
    stile(y - 6, x + 2, TL_WALL_TT);
    stile(y - 6, x + 4, TL_WALL_TT);
    stile(y, x - 4, TL_IWALL);
    stile(y, x + 4, TL_IWALL);
    break;

  case DEC_CAMP:
    stile(y, x - 2, TL_CAMP_STAND_B);
    stile(y, x - 1, TL_CAMP_FIRE);
    stile(y, x + 0, TL_P_CAMP);
    stile(y, x + 1, TL_CAMP_FIRE);
    stile(y, x + 2, TL_CAMP_STAND_B);

    stile(y - 1, x - 2, TL_CAMP_STAND_T);
    stile(y - 1, x - 1, TL_CAMP_MEAT1);
    stile(y - 1, x + 0, TL_CAMP_MEAT2);
    stile(y - 1, x + 1, TL_CAMP_MEAT3);
    stile(y - 1, x + 2, TL_CAMP_STAND_T);

    stile(y - 1, x + 3, TL_CAMP_SPIT1);
    stile(y, x + 3, TL_CAMP_SPIT2);
    break;

  case DEC_SPENTCAMP:
    stile(y, x - 1, TL_CAMP_SPENT);
    stile(y, x + 0, TL_CAMP_SPENT);
    stile(y, x + 1, TL_CAMP_SPENT);

    stile(y - 1, x - 1, TL_CAMP_SPIT3);
    stile(y - 1, x + 0, TL_CAMP_SPIT3);
    stile(y - 1, x + 1, TL_CAMP_SPIT3);
    break;

  case DEC_ORB:
//    stile(y, x - 2, TL_ORB_L);
    stile(y, x - 2, TL_ORB_CU);
    stile(y, x - 1, TL_ORB_L);
    stile(y, x + 0, TL_P_ORB);
    stile(y, x + 1, TL_ORB_R);
    stile(y, x + 2, TL_ORB_CU);
//    stile(y, x + 2, TL_ORB_R);

    stile(y - 1, x - 2, TL_ORB_LU);
    stile(y - 1, x - 1, TL_ORB_LU);
//    stile(y - 1, x + 0, TL_ORB_CU);
    stile(y - 1, x + 1, TL_ORB_RU);
    stile(y - 1, x + 2, TL_ORB_RU);

    stile(y - 1, x, TL_ORB_LIT);
    break;

  case DEC_DOOR:
    stile(y, x, TL_DOOR);
    stile(y - 1, x, TL_DOOR);
    stile(y - 2, x, TL_DOOR);
    stile(y - 3, x, TL_DOOR);
    
    stile(y - 1, x - 1, TL_DOOR_HL);
    stile(y - 1, x + 1, TL_DOOR_HR);

    stile(y, x - 5, TL_DOOR_L);

    stile(y, x - 2, TL_DOOR_BLOCK);
    stile(y, x + 2, TL_DOOR_BLOCK);

    stile(y - 4, x, TL_WALL);
    stile(y - 5, x, TL_WALL);
    stile(y - 4, x - 1, TL_WALL);
    stile(y - 5, x - 1, TL_WALL);
    stile(y - 4, x + 1, TL_WALL);
    stile(y - 5, x + 1, TL_WALL);

    // Try to prevent these from being changed to other types of wall
    // in branches
    stile(y - 4, x, TL_IWALL);
    stile(y - 5, x, TL_IWALL);
    break;

  case DEC_TABLET:
    stile(y,     x,     TL_P_TABLET);

//    stile(y,     x - 2, TL_TAB_R);
    stile(y,     x - 1, TL_TAB_LEG);
    stile(y,     x + 1, TL_TAB_LEG);
//    stile(y,     x + 2, TL_TAB_L);

    stile(y - 1, x - 2, TL_TAB_L);
    stile(y - 1, x - 1, TL_TAB_T);
    stile(y - 1, x,     TL_TAB_C);
    stile(y - 1, x + 1, TL_TAB_T);
    stile(y - 1, x + 2, TL_TAB_R);

    stile(y - 2, x - 2, TL_TAB_T);
    stile(y - 2, x - 1, TL_TAB_T);
    stile(y - 2, x - 0, TL_TAB_T);
    stile(y - 2, x + 1, TL_TAB_T);
    stile(y - 2, x + 2, TL_TAB_T);

    break;
    
  case DEC_SWSTONE:
    stile(y,     x,     TL_P_SWSTONE);

    stile(y,     x - 1, TL_SWSTONE_LR);
    stile(y,     x - 2, TL_SWSTONE_UL);
    stile(y - 1, x - 1, TL_SWSTONE_UL);

    stile(y,     x + 1, TL_SWSTONE_LL);
    stile(y,     x + 2, TL_SWSTONE_UR);
    stile(y - 1, x + 1, TL_SWSTONE_UR);

    stile(y - 1, x,     TL_SWSTONE_1);
    stile(y - 2, x,     TL_SWSTONE_2);
    
    break;
    
  case DEC_ALTAR:
    stile(y, x,     TL_P_ALTAR);

    //stile(y, x - 4, TL_GR_VL);
    stile(y, x - 3, TL_GR_VL);
    stile(y, x - 1, TL_GR_UL);
    stile(y, x + 1, TL_GR_UR);
    stile(y, x + 3, TL_GR_VL);
//    stile(y, x + 4, TL_GR_UR);

    stile(y - 1, x - 3, TL_GR_LTEE);
    stile(y - 1, x - 2, TL_GR_HL);
    stile(y - 1, x - 1, TL_GR_HL);
    stile(y - 1, x,     TL_GR_HL);
    stile(y - 1, x + 1, TL_GR_HL);
    stile(y - 1, x + 2, TL_GR_HL);
    stile(y - 1, x + 3, TL_GR_RTEE);

    stile(y - 2, x - 3, TL_YDOT);
    stile(y - 2, x + 3, TL_YDOT);

//    stile(y - 3, x, TL_WH_VL);
    stile(y - 2, x, TL_WH_VL);
    stile(y - 2, x + 1, TL_WH_LR);
    stile(y - 2, x - 1, TL_WH_LL);
    break;

  case DEC_FOUNTAIN:
    stile(y, x,     TL_P_FOUNTAIN);
    stile(y, x - 2, TL_FOUNT_BASE);
    stile(y, x - 1, TL_FOUNT_BASE);
    stile(y, x + 1, TL_FOUNT_BASE);
    stile(y, x + 2, TL_FOUNT_BASE);

    stile(y - 1, x,     TL_BL_VL);

    stile(y - 2, x - 1, TL_BL_UL);
    stile(y - 2, x,     TL_BL_TTEE);
    stile(y - 2, x + 1, TL_BL_UR);
    break;

  case DEC_PORTAL:
    stile(y, x,     TL_P_PORTAL);

    stile(y, x - 4, TL_PORTAL_S_L);
    stile(y, x - 3, TL_PORTAL_S_B);
    stile(y, x - 2, TL_PORTAL_S_B);
    stile(y, x - 1, TL_PORTAL_S_B);
    stile(y, x + 1, TL_PORTAL_S_B);
    stile(y, x + 2, TL_PORTAL_S_B);
    stile(y, x + 3, TL_PORTAL_S_B);
    stile(y, x + 4, TL_PORTAL_S_R);

    stile(y - 1, x - 3, TL_PORTAL_S_L);
    stile(y - 1, x - 2, TL_PORTAL_S_B);
    stile(y - 1, x - 1, TL_PORTAL_S_B);
    stile(y - 1, x - 0, TL_PORTAL_S_B);
    stile(y - 1, x + 1, TL_PORTAL_S_B);
    stile(y - 1, x + 2, TL_PORTAL_S_B);
    stile(y - 1, x + 3, TL_PORTAL_S_R);

    stile(y - 2, x - 2, TL_PORTAL_L);
    stile(y - 2, x - 1, TL_PORTAL_M);
    stile(y - 2, x - 0, TL_PORTAL_M);
    stile(y - 2, x + 1, TL_PORTAL_M);
    stile(y - 2, x + 2, TL_PORTAL_R);

    stile(y - 3, x - 2, TL_PORTAL_L);
    stile(y - 3, x - 1, TL_PORTAL_M);
    stile(y - 3, x - 0, TL_PORTAL_M);
    stile(y - 3, x + 1, TL_PORTAL_M);
    stile(y - 3, x + 2, TL_PORTAL_R);

    stile(y - 4, x - 2, TL_PORTAL_L);
    stile(y - 4, x - 1, TL_PORTAL_T);
    stile(y - 4, x - 0, TL_PORTAL_T);
    stile(y - 4, x + 1, TL_PORTAL_T);
    stile(y - 4, x + 2, TL_PORTAL_R);

    break;

  case DEC_COFFIN:
    stile(y - 0, x - 0, TL_P_COFFIN);

    stile(y - 0, x - 3, TL_COFFIN_UL);
    stile(y - 0, x - 2, TL_COFFIN_BTEE);
    stile(y - 0, x - 1, TL_COFFIN_HL);
    stile(y - 0, x + 1, TL_COFFIN_HL);
    stile(y - 0, x + 2, TL_COFFIN_BTEE);
    stile(y - 0, x + 3, TL_COFFIN_UR);

    stile(y - 1, x - 2, TL_COFFIN_UL);
    stile(y - 1, x - 1, TL_COFFIN_HL);
    stile(y - 1, x - 0, TL_COFFIN_BTEE);
    stile(y - 1, x + 1, TL_COFFIN_HL);
    stile(y - 1, x + 2, TL_COFFIN_UR);

    stile(y - 2, x - 0, TL_COFFIN_CROSS2);

    break;

  case DEC_IDOL:
    stile(y, x,     TL_P_IDOL);

    stile(y - 0, x - 1, TL_IDOL_STAND_VL);
    stile(y - 0, x + 1, TL_IDOL_STAND_VL);
    stile(y - 1, x - 1, TL_IDOL_STAND_UL);
    stile(y - 1, x - 0, TL_IDOL_STAND_HL);
    stile(y - 1, x + 1, TL_IDOL_STAND_UR);

    stile(y - 2, x + 0, TL_IDOL_BODY);
    stile(y - 2, x - 1, TL_IDOL_LARM);
    stile(y - 2, x + 1, TL_IDOL_RARM);

    stile(y - 3, x + 0, TL_IDOL_HEAD);
    break;

  case DEC_BROKEN_IDOL:
    stile(y - 3, x + 0, TL_VOID);
    stile(y - 2, x + 1, TL_VOID);
    stile(y - 2, x - 1, TL_IDOL_DEBRIS_1);
    stile(y - 2, x - 0, TL_IDOL_DEBRIS_1);
    stile(y - 0, x - 2, TL_IDOL_DEBRIS_2);
    stile(y - 0, x + 2, TL_IDOL_HEAD);
    break;

  case DEC_EMPTY_SHELF:
    stile(y - 0, x + 0, TL_SHELF_HL);

    stile(y - 1, x - 1, TL_VOID);
    stile(y - 1, x - 0, TL_VOID);
    stile(y - 1, x + 1, TL_SHELF_BOOK8);
    stile(y - 3, x - 1, TL_SHELF_BOOK1);
    stile(y - 3, x - 0, TL_VOID);
    stile(y - 3, x + 1, TL_SHELF_BOOK7);

    stile(y - 0, x - 3, TL_SHELF_BOOK5);
    break;

  case DEC_BOOKSHELF:
    stile(y - 0, x + 0, TL_P_BOOKSHELF);

    stile(y - 0, x - 2, TL_SHELF_LTEE);
    stile(y - 0, x - 1, TL_SHELF_HL);
    stile(y - 0, x + 1, TL_SHELF_HL);
    stile(y - 0, x + 2, TL_SHELF_RTEE);

    stile(y - 1, x - 2, TL_SHELF_VL);
    stile(y - 1, x - 1, TL_SHELF_BOOK1);
    stile(y - 1, x - 0, TL_SHELF_BOOK2);
    stile(y - 1, x + 1, TL_SHELF_BOOK3);
    stile(y - 1, x + 2, TL_SHELF_VL);

    stile(y - 2, x - 2, TL_SHELF_LTEE);
    stile(y - 2, x - 1, TL_SHELF_HL);
    stile(y - 2, x - 0, TL_SHELF_HL);
    stile(y - 2, x + 1, TL_SHELF_HL);
    stile(y - 2, x + 2, TL_SHELF_RTEE);

    stile(y - 3, x - 2, TL_SHELF_VL);
    stile(y - 3, x - 1, TL_SHELF_BOOK4);
    stile(y - 3, x - 0, TL_SHELF_BOOK5);
    stile(y - 3, x + 1, TL_SHELF_BOOK6);
    stile(y - 3, x + 2, TL_SHELF_VL);

    stile(y - 4, x - 2, TL_SHELF_UL);
    stile(y - 4, x - 1, TL_SHELF_HL);
    stile(y - 4, x - 0, TL_SHELF_HL);
    stile(y - 4, x + 1, TL_SHELF_HL);
    stile(y - 4, x + 2, TL_SHELF_UR);
    break;

  case DEC_CORPSE:
    stile(y, x - 2, TL_CORPSE1);
    stile(y, x - 1, TL_CORPSE2);
    stile(y, x,     TL_P_CORPSE);
    stile(y, x + 1, TL_CORPSE4);
    stile(y, x + 2, TL_CORPSE5);
    break;

  case DEC_SKELETON:
    stile(y, x + 0, TL_P_SKELETON);
    stile(y, x - 2, TL_BONE3);
    stile(y, x - 1, TL_BONE1);
    stile(y, x + 1, TL_BONE3);
    stile(y, x + 2, TL_BONE1);
    break;

  case DEC_ENTRANCE:
    stile(y, x - 4, TL_STAIR_UL);
    stile(y, x - 3, TL_STAIR_HL);
    stile(y, x - 2, TL_STAIR_HL);
    stile(y, x - 1, TL_STAIR_HL);
    stile(y, x + 0, TL_P_ENTRANCE);
    stile(y, x + 1, TL_STAIR_HL);
    stile(y, x + 2, TL_STAIR_HL);
    stile(y, x + 3, TL_STAIR_HL);
    stile(y, x + 4, TL_STAIR_UR);

    stile(y - 1, x - 3, TL_STAIR_UL);
    stile(y - 1, x - 2, TL_STAIR_HL);
    stile(y - 1, x - 1, TL_STAIR_HL);
    stile(y - 1, x + 0, TL_STAIR_HL);
    stile(y - 1, x + 1, TL_STAIR_HL);
    stile(y - 1, x + 2, TL_STAIR_HL);
    stile(y - 1, x + 3, TL_STAIR_UR);

    stile(y - 2, x - 1, TL_ENTR_DOOR);
    stile(y - 2, x + 0, TL_ENTR_DOOR);
    stile(y - 2, x + 1, TL_ENTR_DOOR);
    stile(y - 3, x - 1, TL_ENTR_DOOR);
    stile(y - 3, x + 0, TL_ENTR_DOOR);
    stile(y - 3, x + 1, TL_ENTR_DOOR);
    stile(y - 4, x - 1, TL_ENTR_DOOR);
    stile(y - 4, x + 0, TL_ENTR_DOOR);
    stile(y - 4, x + 1, TL_ENTR_DOOR);

    break;

  case DEC_CHEST:
  default:
    stile(y, x,     TL_P_CHEST);
    stile(y, x - 2, TL_WOOD);
    stile(y, x - 1, TL_WOOD);
    stile(y, x + 1, TL_WOOD);
    stile(y, x + 2, TL_WOOD);

    stile(y - 1, x - 2, TL_WOOD);
    stile(y - 1, x - 1, TL_WOOD);
    stile(y - 1, x,     TL_LOCK);
    stile(y - 1, x + 1, TL_WOOD);
    stile(y - 1, x + 2, TL_WOOD);
    break;

  case DEC_NPC:
    stile(y, x - 1, TL_NPC_LLEG);
    stile(y, x + 1, TL_NPC_RLEG);
    stile(y - 1, x - 1, TL_NPC_LLEG);
    stile(y - 1, x + 0, TL_NPC_TORSO);
    stile(y - 1, x + 1, TL_NPC_RLEG);
    stile(y - 2, x, TL_NPC_HEAD);
    break;

  case DEC_DESK:
    stile(y, x, TL_DESK);
    stile(y - 1, x, TL_DESK);
    break;

  }

  return;  
}
