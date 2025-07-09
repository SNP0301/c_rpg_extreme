#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "monster.h"
#include "item.h"

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

    fscanf(fp, "%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s", map[i]);
        strcpy(original_map[i], map[i]);
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '@') {
                start_x = i;
                start_y = j;
            }
        }
    }

    fscanf(fp, "%s", command);

    int monster_num;
    fscanf(fp, "%d", &monster_num);
    for (int i = 0; i < monster_num; i++) {
        int r, c, w, a, h, e;
        char name[11];
        fscanf(fp, "%d %d %s %d %d %d %d", &r, &c, name, &w, &a, &h, &e);
        add_monster(r - 1, c - 1, name, w, a, h, e);
    }

    int item_num;
    fscanf(fp, "%d", &item_num);
    for (int i = 0; i < item_num; i++) {
        int r, c, val = 0;
        char type, s[4];
        fscanf(fp, "%d %d %c %s", &r, &c, &type, s);
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
            if (i == px && j == py) printf("@");
            else printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
