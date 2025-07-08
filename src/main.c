#include <stdio.h>
#include "map.h"
#include "player.h"
#include "monster.h"
#include "item.h"

int main() {
    Player player;

    // 1. 맵 불러오기 및 플레이어 위치 초기화
    load_map();
    init_player(&player, start_x, start_y);

    // 2. 테스트 출력
    printf("===== RPG Extreme Test Start =====\n\n");

    printf("[ 맵 상태 ]\n");
    print_map(player.x, player.y);

    printf("\n[ 플레이어 초기 상태 ]\n");
    printf("LV : %d\n", player.level);
    printf("HP : %d/%d\n", player.hp, player.max_hp);
    printf("ATT : %d+%d\n", player.base_att, player.weapon);
    printf("DEF : %d+%d\n", player.base_def, player.armor);
    printf("EXP : %d/%d\n", player.exp, player.level * 5);

    printf("\n게임 루프는 추후 구현 예정!\n");

    return 0;
}
