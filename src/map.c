#include <stdio.h>
#include "map.h"

int N, M;
char map[MAX_N][MAX_M];
char original_map[MAX_N][MAX_M];
int start_x, start_y;

void load_map() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < M; j++) {
            original_map[i][j] = map[i][j];
            if (map[i][j] == '@') {
                start_x = i;
                start_y = j;
                map[i][j] = '.';  // 플레이어는 실제 맵에서는 제거
            }
        }
    }
}

void print_map(int px, int py) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == px && j == py)
                putchar('@');
            else
                putchar(map[i][j]);
        }
        putchar('\n');
    }
}

int can_move(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && map[x][y] != '#';
}
