#include <stdio.h>
#include <string.h>
#include "player.h"

void init_player(Player *p, int start_x, int start_y) {
    p->x = start_x;
    p->y = start_y;
    p->max_hp = 20;
    p->hp = 20;
    p->base_att = 2;
    p->base_def = 2;
    p->weapon = 0;
    p->armor = 0;
    p->level = 1;
    p->exp = 0;
    p->alive = 1;
    p->re_used = 0;
    p->accessory_count = 0;
}

int has_accessory(Player *p, const char *code) {
    for (int i = 0; i < p->accessory_count; i++) {
        if (strcmp(p->accessories[i], code) == 0)
            return 1;
    }
    return 0;
}

int get_total_att(Player *p) {
    return p->base_att + p->weapon;
}

int get_total_def(Player *p) {
    return p->base_def + p->armor;
}

void level_up(Player *p) {
    p->level++;
    p->max_hp += 5;
    p->base_att += 2;
    p->base_def += 2;
    p->hp = p->max_hp;
    p->exp = 0; // 남은 경험치는 버림
}

void add_accessory(Player *p, const char *code) {
    if (p->accessory_count >= MAX_ACCESSORIES) return;
    if (has_accessory(p, code)) return;

    strncpy(p->accessories[p->accessory_count], code, 2);
    p->accessories[p->accessory_count][2] = '\0'; // null-terminate
    p->accessory_count++;

    if (strcmp(code, "RE") == 0) {
        p->re_used = 0; // RE는 처음 얻을 때 사용 가능으로
    }
}

void equip_weapon(Player *p, int power) {
    p->weapon = power;
}

void equip_armor(Player *p, int power) {
    p->armor = power;
}
