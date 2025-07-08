#include <stdio.h>
#include <string.h>
#include "item.h"
#include "player.h"
#include "map.h"

void open_item_box(Player *p, char item_type, const char *name, int value) {
    if (item_type == 'W') {
        equip_weapon(p, value);
    } else if (item_type == 'A') {
        equip_armor(p, value);
    } else if (item_type == 'O') {
        add_accessory(p, name);
    }
    // 아이템 칸을 빈 칸으로 바꾸기
    map[p->x][p->y] = '.';
}
