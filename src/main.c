#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "map.h"
#include "command.h"

extern Player player;
extern int start_x, start_y;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s input.txt\n", argv[0]);
        return 1;
    }
    printf("Loading map from %s\n", argv[1]);
    load_map(argv[1]);  // 입력 파일 경로를 load_map에 전달
    init_player(start_x, start_y);
    printf("Load finished\n");

    char cmd;
    while (player.hp > 0 && player.alive) {
        print_map(player.x, player.y);
        // player 상태 출력 함수 필요하면 추가
        printf("Enter command (U/D/L/R, Q to quit): ");
        cmd = getchar();
        while (getchar() != '\n'); // 버퍼 비우기

        if (cmd == 'Q' || cmd == 'q') break;

        process_command(cmd);
        system("cls"); // 윈도우 터미널 클리어, 리눅스는 "clear"
    }

    printf("Game Over!\n");
    return 0;
}
