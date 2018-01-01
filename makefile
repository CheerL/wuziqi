SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o, $(SRCS))
CC = gcc
INCLUDES = -I /head
CCFLAGS = -g -Wall -Og

all: main clean
.PHONY:clean

main : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) -g

%.o : %.c
	$(CC) -c $< $(CCFLAGS)

clean:
	rm *.o