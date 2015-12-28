#ifndef _RULES_H_
#define _RULES_H_

#define CONF_PATH "/etc/basment.conf"

#define UNDERWATER_STEPS 3

#define FOUNTAIN_HEAL 10
#define CAMP_HEAL 12
#define LEVEL_UP_HP_BOOST 10
#define HEALING_POTION       18
#define HEALING_POTION_COST  100

#define NPC_MIN_FLOOR  2

#define COST_GNOBLIN_STEW   200
#define GNOBLIN_STEW_HEAL   20
#define COST_MOLD_SOUP      60
#define COST_MAGGOT_PUDDING 100
#define MAGGOT_PUDDING_HEAL 5

#define WEBBED_TURNS 7
#define FLASH_BLIND_TURNS (5 + rand() % 20)

#define COST_11PCS  150
#define NIGIRI_HEAL +10
#define COST_13PCS  200
#define COST_ROLL   100
#define COST_EEL    250
#define COST_TOFU   150
#define TOFU_SPEED  +1
#define COST_BENTO  100
#define BENTO_HEAL  +20

#define CHEST_GOLD   55
#define UWCHEST_GOLD 95
#define COFFIN_GOLD  45

#define BREATH_NORMAL 40
#define BREATH_SCUBA  80

#define SCUBA_COST 100

#define ALTAR_LOOT_PENALTY  400
#define ALTAR_PRAYER_PIETY  200
#define ALTAR_RESTORE_FAITH_PIETY 500
#define ALTAR_LOOT_GOLD     150
#define ALTAR_HEAL_PIETY    700
#define ALTAR_WISDOM_PIETY  800
#define ALTAR_EMBRACE_HEAL  25

#define IDOL_SMASH_PIETY     300
#define IDOL_SACRIFICE_PEN   5
#define IDOL_SACRIFICE_GAIN  4
#define IDOL_SACRIFICE_LIMIT 6
#define IDOL_HP_REFILL       26

#define DISCO_EXP 1000

// In percent
#define SHD_WOODEN_BLOCK 75
#define SHD_METAL_BLOCK 85
#define SHD_MAGIC_BLOCK 95

#define TRAINING_COST 100

#define MAP_COST 100

// The relative difficulty of monsters spawned when the player leaves a level
#define ANOTHER_MONSTER_ADJUSTMENT (+2)

// How many levels at the top that should be free of traps
#define TRAP_FREE_LEVELS 2

// 
#define CAVEIN_DAMAGE_ROLL (3 + rand() % 5)

// Strength required to draw the sword in stone
#define SWORD_IN_STONE_STR 15

// How much gold the player needs to have for a rogue to bother to steal any
#define ROGUE_STEAL_GOLD    50

// Chance in % that a rogue will try to steal gold
#define ROGUE_STEAL_CHANCE  20

// How many steps stone tablets have (incremented for each success)
#define TABLET_START_DIFF 7

// How many characters (excluding null byte) names can be in the highscore table
#define PLNAME_LEN 10


#define HIGHSCORE_TITLE     "  DE BESTE BASMENT DWELLERS  "
#define HIGHSCORE_ANY_KEY   "  PRESS ANY KEY TO GET OUTTA HERE !!  "

#define HIGHSCORE_TOP_ENTRIES 10


#define SCORE_LEVELS        100
#define SCORE_SKILLS        400
#define SCORE_TOOLS         400
#define SCORE_HP_MULT       10
#define SCORE_GOLD_MULT     10
#define SCORE_WEAPON        500
#define SCORE_ARMOR_MULT    200
#define SCORE_MAX_DEPTH     100
#define SCORE_WIN_BONUS     10000
#define SCORE_WIN_STREAK    1000

#define SCORE_MONSTER_PEN   -10
#define SCORE_TRAP_PEN      -50
#define SCORE_TURN_PEN      (-1)

#endif
