#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

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
    int item_num, monster_num;

    if (!fp) {
        printf("Failed to open file: %s\n", filename);
        exit(1);
    }


    if (fscanf(fp, "%d %d %d %d", &N, &M, &monster_num, &item_num) != 4) {
        printf("Failed to read N, M, monster_num, item_num \n");
        exit(1);
    }

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
                map[i][j] = '.';
            }
        }
    }


    for (int i = 0; i < monster_num; i++) {
        int r, c, w, a, h, e;
        char name[11];
        if (fscanf(fp, "%d %d %s %d %d %d %d", &r, &c, name, &w, &a, &h, &e) != 7) {
            printf("Failed to read monster info at %d\n", i);
            exit(1);
        }
        add_monster(r - 1, c - 1, name, w, a, h, e);
    }

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
                set_color(11);
                printf("@");
            } else {
                char cell = map[i][j];
                switch (cell) {
                    case '.': set_color(10); break;
                    case 'B': set_color(14); break;
                    case 'M':
                    case '&': set_color(12); break;
                    case '^': set_color(13); break;
                    case '#': set_color(7);  break;
                    default:  set_color(7);  break;
                }
                printf("%c", cell);
            }
        }
        set_color(7);
        printf("\n");
    }

    set_color(7);
    print_player_status();
}

void print_health_bar(int current_hp, int max_hp) {
    printf("HP: ");
    for (int i = 0; i < max_hp; i++) {
        if (i < current_hp) {
            set_color(12);
            printf("❤️");
        } else {
            set_color(7);
            printf("🤍");
        }
    }
    set_color(7);
    printf(" %d/%d\n", current_hp, max_hp);
}

void print_player_status() {
    extern Player player;

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
