

TARGET = chirp
LIBS = -lfl -lm
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

lex.yy.c: tokenizer.l
	flex tokenizer.l

y.tab.c: parser.y
	yacc -d  parser.y

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) lex.yy.o y.tab.o
HEADERS = $(wildcard *.h)


%.o: %.c lex.yy.c y.tab.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	    $(CC) $(OBJECTS) -Wall $(LIBS) -o $@


clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f lex.yy.c y.tab.c
