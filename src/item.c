#include <string.h>
#include "item.h"
#include "player.h"
#include "map.h"

Item items[MAX_ITEM];
int item_count = 0;

void add_item(int x, int y, char type, const char* name, int value) {
    if (item_count >= MAX_ITEM) return;
    Item* item = &items[item_count++];
    item->x = x;
    item->y = y;
    item->type = type;
    strcpy(item->name, name);
    item->value = value;
}


void open_item_box(int x, int y) {
    // 상자에 든 아이템 정보를 가져오는 로직이 필요하지만
    // 여기서는 간단히 map[x][y]가 'B'라고 가정

    // 실제로는 아이템 정보 구조체나 배열에서 가져와야 함
    // 예: char item_type = ...; char item_name[4]; int item_value = ...;

    // 임시 예시
    char item_type = 'W';  // 무기
    int item_value = 5;    // 공격력 5짜리 무기

    // 아이템 효과 적용
    if (item_type == 'W') {
        equip_weapon(&player, item_value);
    }
    else if (item_type == 'A') {
        equip_armor(&player, item_value);
    }
    else if (item_type == 'O') {
        add_accessory(&player, "HR");  // 예: 회복 장신구
    }

    // 상자 위치 빈 칸으로 바꾸기
    map[x][y] = '.';
    original_map[x][y] = '.';
}