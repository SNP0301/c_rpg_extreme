#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM 100

typedef struct {
    int x, y;          // 위치
    char type;         // 'W', 'A', 'O' (무기, 방어구, 액세서리)
    char name[4];      // 장신구 코드 등 (최대 3글자 + null)
    int value;         // 무기/방어구 공격력/방어력 수치
} Item;

extern Item items[MAX_ITEM];
extern int item_count;

void add_item(int x, int y, char type, const char* name, int value);
void open_item_box(int x, int y);

#endif
