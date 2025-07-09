#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "player.h"
#include "map.h"
#include "command.h"

extern Player player;
extern int start_x, start_y;
extern int game_over;

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s input.txt\n", argv[0]);
        return 1;
    }
    set_color(8); 
    printf("Loading map from %s\n", argv[1]);
    set_color(8);
    load_map(argv[1]);  // 입력 파일 경로를 load_map에 전달
    init_player(start_x, start_y);
    set_color(10); 
    printf("Load finished\n");
    set_color(8);

    char cmd;
    while (player.hp > 0 && !game_over) {
        print_map(player.x, player.y);
        set_color(6);
        printf("Enter command (U/D/L/R, Q to quit): ");
        set_color(8);
        cmd = getchar();
        while (getchar() != '\n');

        if (cmd == 'Q' || cmd == 'q') break;

        process_command(cmd);
        system("cls");
    }

    if (game_over) {
        set_color(9);
        printf("You defeated the Boss! Game Clear!\n");
        set_color(8);
    } else {
        set_color(4);
        printf("Game Over!\n");
        set_color(8);
    }
    return 0;
}
