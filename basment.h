/*
  BASMENT DWELLERS
  Copyright (c) 2013-2015 Ulf Åström
  ulf.astrom@gmail.com / happyponyland.net

  See README.TXT and LICENSE.TXT for more information.
*/

#ifndef _BASMENT_H_
#define _BASMENT_H_

#define BD_VERSION "0.8"

#ifdef _WIN32
#include <curses.h>
#define PORTABLE_DOT '.'
#else
#include <ncurses.h>
#define PORTABLE_DOT ACS_BULLET
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

extern jmp_buf restart_game;

/* Board (viewport), map and level constants */

#define BOARD_H 14             // Height of viewport
#define BOARD_W 61             // Width of viewport
#define BOARD_T 4              // Position from top
#define FLOOR_H (BOARD_H)      // Each floor is the size of a viewport
#define CEILING_Y 3            // Offset of the ceiling from the top
#define FLOOR_Y (BOARD_H - 4)  // Offset of floor from the top
#define FEET_Y (FLOOR_Y - 1)   // Layer directly above the floor

#define CELL_TO_TILES 9
#define CELLS_W       60
#define MAX_FLOORS    24          // How deep we want the dungeon to be

#define MAP_W (CELL_TO_TILES * CELLS_W)   // Width of each floor
#define MAP_H ((MAX_FLOORS + 1) * FLOOR_H)  // Total height needed

#include "mob.h"
#include "map.h"
#include "rules.h"

// Message buffer size
#define DEFLEN 400

/*
  Internal color definitions; these do not
  directly correspond to ncurses COLOR_*
*/
#define PAIR_BLACK   1
#define PAIR_WHITE   2
#define PAIR_MAGENTA 3
#define PAIR_GREEN   4
#define PAIR_RED     5
#define PAIR_BLUE    6
#define PAIR_BROWN   7
#define PAIR_CYAN    8
#define PAIR_RED_ON_GREEN 9
#define PAIR_BLACK_ON_RED 10
#define PAIR_CYAN_ON_BLUE 11
#define PAIR_BROWN_ON_RED 12
#define PAIR_RED_ON_BROWN 13
#define PAIR_GREEN_ON_RED 14
#define PAIR_LIGHTNING    15
#define PAIR_BLUE_ON_GREEN    16
#define PAIR_BROWN_ON_MAGENTA 17
#define PAIR_CYAN_ON_GREEN    18
#define PAIR_RED_ON_BLUE      19
#define PAIR_BLACK_ON_GREEN   20
#define PAIR_GREEN_ON_MAGENTA 21
#define PAIR_RED_ON_WHITE    22
#define PAIR_BLACK_ON_BLUE   23
#define PAIR_WHITE_ON_BLUE   24
#define PAIR_BLACK_ON_CYAN   25
#define PAIR_WHITE_ON_CYAN   26
#define PAIR_LAST         26

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// How long enemy health bars should remain on screen
#define BAR_TIMEOUT 6

// basment.c
extern int key_left;
extern int key_right;
extern int key_up;
extern int key_down;
extern bool cheat_mode;
extern bool forcenameprompt;

void init_ui(void);
void quit_game(void);
void new_game(void);

// stuff.c
int keep_in_range(int a, int b, int c);
int rnd_dir(void);

// title.c
extern int title_running;

void title_screen(void);
void title_anim(void);

// combat.c
#define MIS_ARROW    0
#define MIS_FIREBALL 1
#define MIS_DISINT   2

bool melee(mob_t * attacker, int speed);
int shoot_missile(int mi, int dir);
int damage(mob_t * attacker, mob_t * target);
void kill_enemy(mob_t * target);
void rogue_escape(mob_t * m);

// doors.c
void open_door(int dir);

// pause.c
void spause(void);
void lpause(void);
void opause(void);
void delay(long);
void flush_input(void);

// gfx.c
#define GA(a, b, c)  g_add(y + (a), x + (flip ? (b) * -1 : (b)), c)
//#define GU(a, b, s, c)  g_uadd(y + (a), x + (flip ? (b) * -1 : (b)), s, c)
#define GA_UL  (!flip ? ACS_ULCORNER : ACS_URCORNER)
#define GA_UR  (!flip ? ACS_URCORNER : ACS_ULCORNER)
#define GA_LL  (!flip ? ACS_LLCORNER : ACS_LRCORNER)
#define GA_LR  (!flip ? ACS_LRCORNER : ACS_LLCORNER)
#define GA_LT  (!flip ? ACS_LTEE : ACS_RTEE)
#define GA_RT  (!flip ? ACS_RTEE : ACS_LTEE)
#define GA_BT  (ACS_BTEE)
#define GA_TT  (ACS_TTEE)
#define GA_VL  (ACS_VLINE)
#define GA_HL  (ACS_HLINE)
#define GA_FS  (!flip ? '/'  : '\\')
#define GA_BS  (!flip ? '\\' : '/')
#define GA_AL  (!flip ? '<' : '>')
#define GA_AR  (!flip ? '>' : '<')
#define GA_PL  (!flip ? '(' : ')')
#define GA_PR  (!flip ? ')' : '(')
#define GA_BL  (!flip ? '[' : ']')
#define GA_BR  (!flip ? ']' : '[')

extern int gfx_map[TL_LAST];

extern int enemy_bar;
extern int enemy_bar_time;

void init_gfx_map(void);
void draw_bars(void);
void make_bar(char * title, int amount, int c1, int c2, int c3, int c4);
void draw_board(void);
void draw_frames(void);
void draw_stats(void);
void draw_lowmsg(void);
void board_attr(chtype a, chtype c);
void g_add(int y, int x, chtype c);
void g_uadd(int y, int x, char * s, chtype a);
void draw_imp(int y, int x, int type, bool flip, uint32_t flags);
void draw_thing(mob_t * mob, int y, int x, int type, bool flip, uint32_t flags);
void draw_human(int y, int x, int type, bool flip, uint32_t flags);
void draw_demon(int y, int x, int type, bool flip, uint32_t flags);
void draw_archdemon(int y, int x, int type, bool flip, uint32_t flags);
void draw_spider(int y, int x, int type, bool flip, uint32_t flags);
void draw_snake(int y, int x, int type, bool flip, uint32_t flags);
void draw_fish(int y, int x, int type, bool flip, uint32_t flags);
void draw_crab(int y, int x, int type, bool flip, uint32_t flags);
void draw_ghoul(int y, int x, int type, bool flip, uint32_t flags);
void draw_giant(int y, int x, int type, bool flip, uint32_t flags);
void draw_lich(int y, int x, int type, bool flip, uint32_t flags);
void draw_dknight(int y, int x, int type, bool flip, uint32_t flags);
void draw_scaal(int y, int x, int type, bool flip, uint32_t flags);
void draw_blurk(int y, int x, int type, bool flip, uint32_t flags);
void draw_mimic(int y, int x, int type, bool flip, uint32_t flags);
void draw_eye(int y, int x, int type, bool flip, uint32_t flags);
void draw_moth(int y, int x, int type, bool flip, uint32_t flags);
void draw_nose(int y, int x, int type, bool flip, uint32_t flags);
void draw_eviltree(int y, int x, int type, bool flip, uint32_t flags);
void draw_shrubbery(int y, int x, int type, bool flip, uint32_t flags);
void draw_skeleton(int y, int x, int type, bool flip, uint32_t flags);
void draw_sauceror(int y, int x, int type, bool flip, uint32_t flags);
void draw_elemental(int y, int x, int type, bool flip, uint32_t flags);
void draw_gorzoth(int y, int x, int type, bool flip, uint32_t flags);
void draw_bigspider(int y, int x, int type, bool flip, uint32_t flags);
void draw_brickwall(int y, int x, int type, bool flip, uint32_t flags);
void explosion(int y, int x);
void lightning(int y, int x);
void mob_text(mob_t * mob, char * msg);

/* popup.c */
void popup(char * msg, int hlight, int flags);
void pwait(char * msg);
int psel(char * msg);
int pchoose(char * msg, int start_row, int items, int options);

#define POPUP_ELLIPSIS    (1<<0)
#define POPUP_LEAVE_LEFT  (1<<1)
#define POPUP_LEAVE_RIGHT (1<<1)

/* map.c */
void fix_walls(void);
void decorate_walls(void);
int gtile(int y, int x);
int stile(int y, int x, int n);
int branch_at_tile(int y, int x);

/* monster.c */
#define ART_NONE 0
#define ART_THE  1
#define ART_A    2
#define ART_AN   3

extern char * article[];

int make_monster(int y, int x, int type);
int free_mob(void);
bool on_board(mob_t * mob);
void mob_walk(int mi, int dist);
mob_t * find_enemy(mob_t * mob, int y, int x);
void frustration(mob_t * mob);
void move_towards_player(mob_t * mob);
int random_monster(int floor, int branch);
void add_another_monster(int floor);
void knave_logic(mob_t * mob);
bool eviltree_logic(mob_t * mob);
void knave_shield(mob_t * mob, bool up);
bool summon_minions(mob_t * mob);

/* game.c */
void play(void);
void enemy_turn(int mi);

/* player.c */
char lowmsg[200];
void new_player(void);
void player_turn(void);
void game_over(char * cause, bool won);
int player_move(int);
void climb_ladder(int dir);
bool trapdoor(void);
void player_fall(void);
void calculate_floor(void);
void give_exp(int exp);
void give_gold(char * msg, int amount);
bool spend_gold(int amount);
bool recenter(bool preemptive);
void intro(void);
void refill_hp(int amount);
void learn_detect_traps(void);
void change_pl_st(int change);
void change_pl_sp(int change);
void debug_teleport(void);
void get_player_name(char * dest, int maxlen);

/* traps.c */
bool is_trap(int tile);
void cavein(void);
void poison_gas(void);
void summon_gorzoth(void);
void tremor(int amount);

/* interact.c */
bool interesting(int tile);
void interact(void);
void feet_instruction(int tile);
void altar(void);
void fountain(void);
void idol(void);
void camp(void);
void portal_travel(void);
void gaze_orb(void);
void draw_tablet(int highlight);
void stone_tablet(void);
void sword_in_stone(void);

/* shops.c */
void shop_chef(void);
void shop_train(void);
void shop_map(void);
void shop_blacksmith(void);
void shop_sushi(void);

/* weapon.c */
#define WPN_UNARMED   0
#define WPN_DAGGER    1
#define WPN_SWORD     2
#define WPN_MACE      3
#define WPN_SPEAR     4
#define WPN_AXE       5
#define WPN_FLAIL     6
#define WPN_DRAIN     7
#define WPN_DIAMOND   8
#define WPN_GLASS     9
#define WPN_BOW       10
#define WPN_RUNESWORD 11
#define WPN_LAST      12

extern char * weapon_name[WPN_LAST];

void find_random_weapon(char * msg);
void give_weapon(int type);
bool damage_weapon(int amount);

/* armor.c */
#define SHD_NONE    0
#define SHD_WOODEN  1
#define SHD_METAL   2
#define SHD_MAGIC   3
#define SHD_SHIELDS 3

#define ARMOR_NONE     0
#define ARMOR_LEATHER  4
#define ARMOR_SCALE    5
#define ARMOR_PLATE    6
#define ARMOR_MAGIC    7
#define ARMOR_DRAGON   8
#define ARMOR_SPIDER   9
#define ARMOR_LAST     10

extern char * armor_name[ARMOR_LAST];

#define ARMOR_LOOT_LEVELS 25
extern int armor_loot[ARMOR_LOOT_LEVELS];

void find_random_armor(char * msg);
void give_armor(int type);
void damage_armor(mob_t * mob);
void damage_shield(mob_t * mob);
bool shield_block(mob_t * mob);

/* books.c */
void bookshelf(void);
void shuffle_books(void);

/* conf.c */
void read_conf(void);
bool ffwd_ptr(char ** p);

/* generate.c */
bool map_demo;

#define AUTOMAP_BLANK   0
#define AUTOMAP_VISITED (1<<0)
#define AUTOMAP_KNOWN   (1<<1)

void generate_map(void);
void dig(int start_y, int x, int speed, int depth);
void corridor(int y, int start_x, int speed, bool remainder);
void add_extra_rooms(void);
void add_wide_chasms(void);
void place_single_cell(int start_y, int cell);
bool dig_wide_chasm(int start_y, int x);
bool dig_up(int start_y, int x, int carve);
void flatten_rooms(void);
bool make_branch(void);
void link_portals(void);
void clear_cellmap(void);
void add_ambushes(void);
void populate_cellmap(void);
void replace_remainders(void);
void convert_cellmap(void);
void clear_tilemap(void);
void excavate(int feet, int center, int w_l, int w_r);
void make_ladder(int start_y, int start_x, int tiles, bool chasm);
void decorate(int y, int x, int type);
void npc_room(int y, int x, int cell_type);
bool open_down(int cell);
void set_cell(int y, int x, int token);
void set_branch(int y, int x, int branch);
int get_branch(int y, int x);
void set_cell_branch(int y, int x, int token, int branch);
int get_cell(int y, int x);
int floor_loot(int cy, int cx);
bool cell_range(int t, int l, int b, int r, int type, bool write);
int cell_open(int c);

/* water.c */
int water_monster(int cy, int cx);
int water_cell(int c);
int wcorr_cell(int c);
int wopen_cell(int c);
int water_join(int t);
void make_lake(void);
void dig_lake(int start_y, int start_x, int dir);
void make_water(int cy, int cx);
int dig_lake_up(int start_y, int start_x, int dir, int rec_depth);
int air_pocket(int y, int start_x);
void put_lakes(void);
void add_shallow_lakes(void);
void add_surfaces(void);

/* hiscore.c */
char scores_file[DEFLEN];

int calculate_score(void);
int add_highscore(long score, char * name, char * reason);
void show_highscore(int top_entries, int highlight, bool fancy);
char * read_file(char * filename);

/* automap.c */

#define NOW_WORKING now_working(__func__);
extern char working_label[DEFLEN];
void now_working(const char * func);

void update_automap(void);
void draw_cellmap(void);
void fill_automap(int mode);
void automap_glyph(int celltype, chtype * glyph, chtype * attr);
void map_legend(void);

mob_t * player;

WINDOW * board;
WINDOW * stats;
WINDOW * lowwin;

#define TURN_COST 100

#define MOB_NONE     0
#define MOB_PLAYER   1
#define MOB_GORE     2


#define MOB_FIRSTRND   11
#define MOB_SPIDER     11
#define MOB_SNAKE      12
#define MOB_ROGUE      13
#define MOB_GIANT      14
#define MOB_GHOUL      15
#define MOB_GNOBLIN    16
#define MOB_IMP        17
#define MOB_SKELETON   18
#define MOB_MOTH       19
#define MOB_LICH       20
#define MOB_BLURK      21
#define MOB_DKNIGHT    22
#define MOB_NOSE       23
#define MOB_SAUCEROR   24
#define MOB_ELEMENTAL  25
#define MOB_EVILTREE   26
#define MOB_DEMON      27
#define MOB_LASTRND    28
#define MOB_SCAAL      29
#define MOB_ARCHDEMON  30
#define MOB_KNAVE      31
#define MOB_MIMIC      32
#define MOB_EYE        33
#define MOB_GORZOTH    34
#define MOB_BIGSPIDER  35
#define MOB_SHRUBBERY  36
#define MOB_BRICKWALL  37
#define MOB_FISH       38
#define MOB_CRAB       39
#define MOB_LAST       40

extern char * mob_name[MOB_LAST];


/* Generic flags */
#define GFX_ATTACK  (1<<0)
#define GFX_HURT    (1<<1)
#define GFX_ATTACK2 (1<<2)

#define GFX_HUMAN_DIVE    (1<<4)
#define GFX_HUMAN_CLIMB1  (1<<5)
#define GFX_HUMAN_CLIMB2  (1<<6)
#define GFX_HUMAN_FALL1   (1<<7)
#define GFX_HUMAN_FALL2   (1<<8)

#define GFX_HUMAN_MWPN    (1<<9)
#define GFX_HUMAN_FLAIL   (1<<10)
#define GFX_HUMAN_SWORD   (1<<11)
#define GFX_HUMAN_MACE    (1<<12)
#define GFX_HUMAN_AXE     (1<<13)
#define GFX_HUMAN_SPEAR   (1<<14)
#define GFX_HUMAN_DAGGER  (1<<15)
#define GFX_HUMAN_GNOBLIN (1<<16)
#define GFX_HUMAN_BOW     (1<<17)
#define GFX_HUMAN_PLAYER  (1<<18)
#define GFX_HUMAN_SHIELD1   (1<<19)
#define GFX_HUMAN_SHIELD2   (1<<20)
#define GFX_HUMAN_SHIELD_UP (1<<21)
#define GFX_HUMAN_ARMOR1    (1<<22)
#define GFX_HUMAN_ARMOR2    (1<<23)
#define GFX_HUMAN_ARMOR3    (1<<24)
#define GFX_HUMAN_MWPN2     (1<<25)

#define GFX_HUMAN_WEAPONS \
  (GFX_HUMAN_SWORD | GFX_HUMAN_MACE | GFX_HUMAN_AXE | GFX_HUMAN_SPEAR | GFX_HUMAN_DAGGER | GFX_HUMAN_FLAIL | GFX_HUMAN_BOW)

#define GFX_BIGSPIDER_HURT1 (1<<10)
#define GFX_BIGSPIDER_HURT2 (1<<11)
#define GFX_BIGSPIDER_HURT3 (1<<12)
#define GFX_BIGSPIDER_HURT4 (1<<13)
#define GFX_BIGSPIDER_HURT5 (1<<14)
#define GFX_BIGSPIDER_HURT6 (1<<15)
#define GFX_BIGSPIDER_HURT7 (1<<16)

#define GFX_GHOUL_DIG1 (1<<10)
#define GFX_GHOUL_DIG2 (1<<11)
#define GFX_GHOUL_DIG3 (1<<12)
#define GFX_GHOUL_DIG4 (1<<13)

#define GFX_MIMIC_IDLE  (1<<31)
#define GFX_BLURK_IDLE  (1<<31)






#endif


