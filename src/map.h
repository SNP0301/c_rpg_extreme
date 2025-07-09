#ifndef MAP_H
#define MAP_H

#define MAX_MAP_SIZE 101

extern int N, M;
extern char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
extern char original_map[MAX_MAP_SIZE][MAX_MAP_SIZE];
extern int start_x, start_y;
extern char command[5001];

void load_map(const char* filename);
int can_move(int x, int y);
void print_map(int px, int py);
void print_player_status(void);


#endif
