#ifndef MONSTER_H
#define MONSTER_H

#include "player.h"  // Player 포인터를 사용하는 함수가 있기 때문에 포함해야 함

#define MAX_MONSTER 100

typedef struct {
    int x, y;
    char name[11];     // 최대 10글자 + NULL 문자
    int att, def;
    int hp, max_hp;
    int exp;
    int alive;
} Monster;

// 몬스터 배열과 카운트 (외부에서 접근 가능)
extern Monster monsters[MAX_MONSTER];
extern int monster_count;

// 함수 선언
void add_monster(int x, int y, const char* name, int att, int def, int hp, int exp);
Monster* find_monster_at(int x, int y);
void fight_monster(Player *p, Monster *m);  // ⚠️ 이거 꼭 추가!

#endif
