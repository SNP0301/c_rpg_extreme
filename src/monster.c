#include <stdio.h>
#include <string.h>

#include "monster.h"
#include "player.h"
#include "map.h"


int game_over = 0;

extern char map[101][101];
Monster monsters[MAX_MONSTER];
int monster_count = 0;

void load_monsters() {}

void add_monster(int x, int y, const char* name, int att, int def, int hp, int exp) {
    if (monster_count >= MAX_MONSTER) return;

    Monster* m = &monsters[monster_count++];
    m->x = x;
    m->y = y;
    strncpy(m->name, name, 10);
    m->name[10] = '\0';
    m->att = att;
    m->def = def;
    m->hp = hp;
    m->max_hp = hp;
    m->exp = exp;
    m->alive = 1;
}

Monster* find_monster_at(int x, int y) {
    for (int i = 0; i < monster_count; i++) {
        if (monsters[i].alive && monsters[i].x == x && monsters[i].y == y)
            return &monsters[i];
    }
    return NULL;
}

int calc_damage(int attacker, int defender) {
    return (attacker - defender >= 1) ? (attacker - defender) : 1;
}

void fight_monster(Player *p, Monster *m) {
    int first_strike = 1;

    int player_att = get_total_att(p);
    int player_def = get_total_def(p);

    while (1) {
        int dmg = calc_damage(player_att, m->def);
        if (first_strike && has_accessory(p, "CO")) {
            if (has_accessory(p, "DX"))
                dmg = calc_damage(player_att * 3, m->def);
            else
                dmg = calc_damage(player_att * 2, m->def);
        }
        m->hp -= dmg;

        if (m->hp <= 0) {


            m->alive = 0;
            map[m->x][m->y] = '.';
            original_map[m->x][m->y] = '.';

            printf("After defeating %s, map[%d][%d] = %c\n", m->name, m->x, m->y, map[m->x][m->y]);
            fflush(stdout);
        
            int gained_exp = m->exp;
            if (has_accessory(p, "EX")) gained_exp = gained_exp * 120 / 100;
            p->exp += gained_exp;

            if (p->exp >= p->level * 5) level_up(p);

            if (has_accessory(p, "HR")) {
                p->hp += 3;
                if (p->hp > p->max_hp) p->hp = p->max_hp;
            }

            if (strcmp(m->name, "Boss") == 0) {
                game_over = 1;
            }

            return;
        }

        int counter_dmg = calc_damage(m->att, player_def);
        p->hp -= counter_dmg;

        if (p->hp <= 0) {
            if (has_accessory(p, "RE") && !p->re_used) {
                p->hp = p->max_hp;
                p->x = start_x;
                p->y = start_y;
                p->re_used = 1;
                m->hp = m->max_hp;
                return;
            } else {
                p->alive = 0;
                return;
            }
        }

        first_strike = 0;
    }
}
