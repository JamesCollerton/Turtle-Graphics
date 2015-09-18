CFLAGS = `sdl2-config --cflags` -O4 -Wall -pedantic -std=c99 -lm -lcunit -g
INCS = turtle_functions.h neillsdl2.h
TARGET = turtle
SOURCES =  interpret_functions.c parser_functions.c whitespace_functions.c neillsdl2.c code_combination_functions.c password_functions.c testing_functions.c $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 