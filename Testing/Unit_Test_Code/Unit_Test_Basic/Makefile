CFLAGS = `sdl2-config --cflags` -O4 -Wall -pedantic -std=c99 -g -lm -lcunit
INCS = turtle_functions.h neillsdl2.h
TARGET = turtle
SOURCES =  interpret_functions.c parser_functions.c neillsdl2.c testing_functions.c parser_testing_functions.c interpreter_testing_functions.c $(TARGET).c
LIBS =  `sdl2-config --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 