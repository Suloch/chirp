LIBS =
CC = gcc
CFLAGS = -Wall

.PHONY: all test clean

all: test_utils

test: test_utils
	./test_utils

test_utils: test_utils.o utils.o
	$(CC) test_utils.o utils.o -Wall $(LIBS) -o $@

test_utils.o: test_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: ../utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f test_utils
