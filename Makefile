CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = src/main.c
OBJ = build/main.o
TARGET = build/highway_escape.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
