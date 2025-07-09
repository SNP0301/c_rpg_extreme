#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM 100

typedef struct {
    int x, y;
    char type; // 'W', 'A', 'O'
    char name[4]; // 장신구 이름 또는 숫자 (문자열로 처리)
    int value; // 무기/방어구는 수치, 장신구는 사용 안함
} Item;

extern Item items[MAX_ITEM];
extern int item_count;

void open_item_box(int x, int y);
void add_item(int x, int y, char type, const char* name, int value);

#endif
