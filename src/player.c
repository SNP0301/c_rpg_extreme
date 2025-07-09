#include <stdio.h>
#include <string.h>
#include "player.h"

Player player;

void init_player(int sx, int sy) {
    player.x = sx;
    player.y = sy;
    player.hp = 20;
    player.max_hp = 20;
    player.base_att = 2;
    player.base_def = 2;
    player.weapon = 0;
    player.armor = 0;
    player.level = 1;
    player.exp = 0;
    player.alive = 1;
    player.re_used = 0;
    player.accessory_count = 0;
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
    p->exp = 0;
}

void add_accessory(Player *p, const char *code) {
    if (p->accessory_count >= MAX_ACCESSORIES) return;
    if (has_accessory(p, code)) return;
    if (strlen(code) != 2) return; // 장신구 코드 길이 확인
    printf("Adding accessory: %s\n", code);
printf("Current count: %d\n", p->accessory_count);


    strncpy(p->accessories[p->accessory_count], code,3);  // 안전하게 복사
    p->accessories[p->accessory_count][3] = '\0';
    p->accessory_count++;

    printf("Accessory added: %s\n", code);  // 디버깅용 출력

    if (strcmp(code, "RE") == 0) {
        p->re_used = 0;
    }
}

void equip_weapon(Player *p, int power) {
    p->weapon = power;
}

void equip_armor(Player *p, int power) {
    p->armor = power;
}
