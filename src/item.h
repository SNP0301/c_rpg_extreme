#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM 100

typedef struct {
    int x, y;         
    char type;        
    char name[4];
    int value;
} Item;

extern Item items[MAX_ITEM];
extern int item_count;

void add_item(int x, int y, char type, const char* name, int value);
void open_item_box(int x, int y);

#endif
