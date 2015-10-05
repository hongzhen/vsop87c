SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC)) 

AR=ar

CC=clang-3.6
DEBUG=-g -pg


all: libvsop87c.a

libvsop87c.a: $(OBJS)
	$(AR) rc -o $@ $^


%.o: %.c
	$(CC) $(DEBUG) -c -std=c99 -Wall -Werror -o $@ $^

test: $(OBJS)
	$(CC) -lm -lc -o $@ $^

clean:
	rm -rf *.o *.a

ctags:
	ctags --lang=c *.c *.h
