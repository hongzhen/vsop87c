SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC)) 

CC=clang-3.6

all: test

%.o: %.c
	$(CC) -c -std=c99 -Wall -Werror -o $@ $^

test: $(OBJS)
	$(CC) -lm -lc -o $@ $^

clean:
	rm -rf *.o

