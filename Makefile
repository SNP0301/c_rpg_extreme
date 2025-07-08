CC = gcc
CFLAGS = -Wall -g

SRCS = main.c player.c map.c monster.c item.c
OBJS = $(SRCS:.c=.o)
TARGET = rpg

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)