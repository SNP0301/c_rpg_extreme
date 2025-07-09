#include <string.h>
#include <stdio.h>
#include "item.h"
#include "player.h"
#include "map.h"

Item items[MAX_ITEM];
int item_count = 0;

void add_item(int x, int y, char type, const char* name, int value) {
    // 아이템이 최대 개수를 초과하지 않도록 체크
    printf("Load Item: (%d, %d) type=%c name=%s val=%d\n", x, y, type, name, value);
    if (item_count >= MAX_ITEM) return;
    Item* item = &items[item_count++];
    item->x = x;
    item->y = y;
    item->type = type;
    strncpy(item->name, name, 3);
    item->name[3] = '\0';
    item->value = value;
}

void remove_item_at(int index) {
    if (index < 0 || index >= item_count) return;
    // 뒤쪽 아이템을 앞으로 한 칸씩 당기기
    for (int i = index; i < item_count - 1; i++) {
        items[i] = items[i + 1];
    }
    item_count--;
}

void open_item_box(int x, int y) {
    for (int i = 0; i < item_count; i++) {
        if (items[i].x == x && items[i].y == y) {
            Item* item = &items[i];
            if (item->type == 'W') {
                equip_weapon(&player, item->value);
            } else if (item->type == 'A') {
                equip_armor(&player, item->value);
            } else if (item->type == 'O') {
                add_accessory(&player, item->name);
            }

            map[x][y] = '.';
            original_map[x][y] = '.';

            remove_item_at(i);
            break;
        }
    }
}
