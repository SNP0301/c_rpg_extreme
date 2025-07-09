#include <stdio.h>
#include <string.h>
#include "monster.h"
#include "player.h"
#include "map.h"

Monster monsters[MAX_MONSTER];
int monster_count = 0;

void load_monsters() {
    // TODO: 실제 파일에서 몬스터 정보를 읽어오거나, 코드로 추가해도 됨
    // 예시: monsters[0] = {"Slime", 3, 1, 10, 5, 2, 3, 1, 0};
}

void add_monster(int x, int y, const char* name, int att, int def, int hp, int exp) {
    if (monster_count >= MAX_MONSTER) return;  // 최대 수 제한

    Monster* m = &monsters[monster_count++];
    m->x = x;
    m->y = y;
    strncpy(m->name, name, 10);
    m->name[10] = '\0';  // null-terminate
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

    // CO, DX 등은 아직 반영 안 했음. 나중에 장신구 효과 반영 필요
    while (1) {
        // 플레이어 공격
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
            // 경험치 획득
            int gained_exp = m->exp;
            if (has_accessory(p, "EX")) gained_exp = gained_exp * 120 / 100;
            p->exp += gained_exp;
            if (p->exp >= p->level * 5) level_up(p);
            // HR: 회복
            if (has_accessory(p, "HR")) {
                p->hp += 3;
                if (p->hp > p->max_hp) p->hp = p->max_hp;
            }
            return;
        }

        // 몬스터 반격
        int counter_dmg = calc_damage(m->att, player_def);
        p->hp -= counter_dmg;

        if (p->hp <= 0) {
            if (has_accessory(p, "RE") && !p->re_used) {
                // 부활
                p->hp = p->max_hp;
                p->x = start_x;
                p->y = start_y;
                p->re_used = 1;
                m->hp = m->max_hp; // 몬스터도 회복
                return;
            } else {
                p->alive = 0;
                return;
            }
        }

        first_strike = 0;
    }
}
