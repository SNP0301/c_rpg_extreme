#ifndef MONSTER_H
#define MONSTER_H

#define MAX_MONSTER 100

#include "player.h"

typedef struct {
    char name[21];
    int att, def, hp, max_hp, exp;
    int x, y;
    int alive;
    int is_boss;
} Monster;

extern Monster monsters[MAX_MONSTER];
extern int monster_count;

void load_monsters();
Monster* find_monster_at(int x, int y);
void fight_monster(Player *p, Monster *m);

#endif
