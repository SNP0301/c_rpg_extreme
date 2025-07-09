// item.c
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "player.h"
#include "map.h"

// 전역 player 변수를 직접 사용
extern Player player;

// 아이템 정보가 저장된 구조체나 배열이 있다고 가정 (예시)
typedef struct {
    char type;        // 'W', 'A', 'O' 중 하나
    char name[20];    // 장신구 이름 등
    int value;        // 공격력, 방어력 등 수치
} Item;

// 예: 위치별 아이템 정보가 저장된 2차원 배열 (map 좌표별)
// 실제 구현시 이 부분은 입력 파일이나 초기화 함수에서 채움
extern Item items[MAX_N][MAX_M];

void open_item_box(int x, int y) {
    Item *item = &items[x][y];
    
    if (item->type == 'W') {
        equip_weapon(&player, item->value);
    } else if (item->type == 'A') {
        equip_armor(&player, item->value);
    } else if (item->type == 'O') {
        add_accessory(&player, item->name);
    }
    
    // 아이템 칸을 빈 칸으로 바꾸기
    map[x][y] = '.';
    
    // 아이템 정보 초기화(없음 처리)
    item->type = '\0';
    item->value = 0;
    item->name[0] = '\0';
}
