#ifndef MAP_H
#define MAP_H

#define MAX_N 100
#define MAX_M 100

extern int N, M;
extern char map[MAX_N][MAX_M];
extern char original_map[MAX_N][MAX_M];
extern int start_x, start_y;

void load_map();
void print_map(int px, int py);
int can_move(int x, int y);

#endif
