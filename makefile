SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c = .o)
CC = gcc
INCLUDES = -I /head
CCFLAGS = -g -Wall -O0

wuziqi : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES)

%.o : %.c
	$(CC) -c $< $(CCFLAGS)
clean:
	rm *.o
.PHONY:clean