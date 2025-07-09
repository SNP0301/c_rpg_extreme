#include <stdio.h>
#include <stdlib.h> 


#include "command.h"
#include "player.h"
#include "map.h"
#include "item.h"
#include "monster.h"

extern Player player;
extern char map[][101];
extern char original_map[][101];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char directions[] = {'U', 'D', 'L', 'R'};

int get_direction_index(char c) {
    for (int i = 0; i < 4; i++) {
        if (directions[i] == c) return i;
    }
    return -1;
}

void process_command(char c) {
    int dir_idx = get_direction_index(c);
    if (dir_idx == -1) return;

    int nx = player.x + dx[dir_idx];
    int ny = player.y + dy[dir_idx];

    if (!can_move(nx, ny)) {
        if (map[player.x][player.y] == '^') {
            player.hp -= 5;
        }
        return;
    }

    map[player.x][player.y] = original_map[player.x][player.y];
    player.x = nx;
    player.y = ny;

    char cell = map[nx][ny];
    if (cell == '^') {
        player.hp -= 5;
    } else if (cell == 'B') {
        open_item_box(nx, ny);
    } else if (cell == '&' || cell == 'M') {
        Monster* m = find_monster_at(nx, ny);
        if (m != NULL) {
            fight_monster(&player, m);
        }
    }

    map[player.x][player.y] = '@';
}
