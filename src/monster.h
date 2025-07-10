#ifndef MONSTER_H
#define MONSTER_H

#include "player.h" 

#define MAX_MONSTER 100

typedef struct {
    int x, y;
    char name[11];
    int att, def;
    int hp, max_hp;
    int exp;
    int alive;
} Monster;

extern Monster monsters[MAX_MONSTER];
extern int monster_count;
extern int game_over;


void add_monster(int x, int y, const char* name, int att, int def, int hp, int exp);
Monster* find_monster_at(int x, int y);
void fight_monster(Player *p, Monster *m); 

#endif
