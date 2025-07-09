#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>  // 꼭 필요!

#include "map.h"
#include "monster.h"
#include "item.h"
#include "player.h"

int N, M;
char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
char original_map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int start_x, start_y;
char command[5001];

extern void set_color(int color);

void load_map(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filename);
        exit(1);
    }

    int item_num, monster_num;

    // N, M, 아이템 수, 몬스터 수를 한 줄에서 읽음
    if (fscanf(fp, "%d %d %d %d", &N, &M, &monster_num, &item_num) != 4) {
        printf("Failed to read N, M, monster_num, item_num \n");
        exit(1);
    }

    // 맵 정보 N줄 읽기
    for (int i = 0; i < N; i++) {
        if (fscanf(fp, "%s", map[i]) != 1) {
            printf("Failed to read map line %d\n", i);
            exit(1);
        }
        strcpy(original_map[i], map[i]);
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '@') {
                start_x = i;
                start_y = j;
                map[i][j] = '.';  // 시작 위치는 빈 칸으로 변경
            }
        }
    }

    // 몬스터 정보 읽기
    for (int i = 0; i < monster_num; i++) {
        int r, c, w, a, h, e;
        char name[11];
        if (fscanf(fp, "%d %d %s %d %d %d %d", &r, &c, name, &w, &a, &h, &e) != 7) {
            printf("Failed to read monster info at %d\n", i);
            exit(1);
        }
        add_monster(r - 1, c - 1, name, w, a, h, e);
    }

    // 아이템 정보 읽기
    for (int i = 0; i < item_num; i++) {
        int r, c, val = 0;
        char type, s[4];
        int ret = fscanf(fp, "%d %d %c %s", &r, &c, &type, s);
        if (ret != 4) {
            printf("Failed to read item info at %d\n", i);
            exit(1);
        }
        if (type == 'W' || type == 'A') {
            val = atoi(s);
        }
        add_item(r - 1, c - 1, type, s, val);
    }

    fclose(fp);
}

int can_move(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M) return 0;
    if (map[x][y] == '#') return 0;
    return 1;
}

void print_map(int px, int py) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == px && j == py) {
                set_color(11); // 플레이어 위치: 밝은 파랑
                printf("@");
            } else {
                char cell = map[i][j];
                switch (cell) {
                    case '.': set_color(10); break; // 초록
                    case 'B': set_color(14); break; // 노랑
                    case 'M':
                    case '&': set_color(12); break; // 빨강
                    case '^': set_color(13); break; // 보라
                    case '#': set_color(7);  break; // 회색
                    default:  set_color(7);  break; // 기본
                }
                printf("%c", cell);
            }
        }
        set_color(7); // 줄 끝나고 초기화
        printf("\n");
    }

    set_color(7); // 전체 출력 후 초기화
    print_player_status();
}

void print_health_bar(int current_hp, int max_hp) {
    printf("HP: ");
    for (int i = 0; i < max_hp; i++) {
        if (i < current_hp) {
            set_color(12); // 빨간색
            printf("❤️");
        } else {
            set_color(7); // 흰색 또는 기본
            printf("🤍");
        }
    }
    set_color(7); // 색 초기화
    printf(" %d/%d\n", current_hp, max_hp);
}

void print_player_status() {
    extern Player player;  // player는 전역변수로 선언되어 있다고 가정

    print_health_bar(player.hp, player.max_hp);
    printf("EXP: %d  Level: %d\n", player.exp, player.level);
    printf("Weapon: +%d  Armor: +%d\n", player.weapon, player.armor);

    printf("Accessories: ");
    if (player.accessory_count == 0) {
        printf("None");
    } else {
        for (int i = 0; i < player.accessory_count; i++) {
            printf("%s ", player.accessories[i]);
        }
    }
    printf("\n");
}
