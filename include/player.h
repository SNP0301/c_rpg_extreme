#ifndef PLAYER_H
#define PLAYER_H

#define MAX_ACCESSORIES 4

typedef struct {
    int x, y;                  
    int max_hp, hp;            
    int base_att, base_def;    
    int weapon, armor;         
    int level, exp;           

    int alive;                 
    int re_used;               

    char accessories[MAX_ACCESSORIES][3]; 
    int accessory_count;
} Player;

void init_player(Player *p, int start_x, int start_y);
int has_accessory(Player *p, const char *code);
int get_total_att(Player *p);
int get_total_def(Player *p);
void level_up(Player *p);
void add_accessory(Player *p, const char *code);
void equip_weapon(Player *p, int power);
void equip_armor(Player *p, int power);

#endif
