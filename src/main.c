#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "item.h"
#include "monster.h"

int main() {
    load_map();
    init_player(start_x, start_y);

    char cmd;
    while (player.hp > 0) {
        print_map(player.x, player.y);
        print_player_status();

        printf("Enter command (U/D/L/R): ");
        cmd = getchar();
        while (getchar() != '\n');  // 입력 버퍼 비우기

        if (cmd == 'Q' || cmd == 'q') break; // 종료 조건 예시

        if (cmd == 'U' || cmd == 'D' || cmd == 'L' || cmd == 'R') {
            process_command(cmd);
        } else {
            printf("Invalid command!\n");
        }
        
        // 여기서 필요하면 터미널 클리어 코드 추가 (OS별 상이)
        system("cls");
    }

    printf("Game Over!\n");
    return 0;
}
