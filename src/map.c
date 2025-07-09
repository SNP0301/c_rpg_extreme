#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "monster.h"
#include "item.h"
#include "player.h"

int N, M;
char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
char original_map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int start_x, start_y;
char command[5001];

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
            if (i == px && j == py) printf("P");
            else printf("%c", map[i][j]);
        }
        printf("\n");
    }
    print_player_status();
}

void print_player_status() {
    extern Player player;  // player는 전역변수로 선언되어 있다고 가정

    printf("HP: %d/%d  EXP: %d  Level: %d\n", player.hp, player.max_hp, player.exp, player.level);
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
