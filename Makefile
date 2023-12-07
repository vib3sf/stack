TARGET = stack

CC = g++
CFLAGS = -Wall -g
LIBS = -lncurses

SRCPREFIX = ./src/

SRC = $(wildcard $(SRCPREFIX)*.h)

$(TARGET): $(SRCPREFIX)main.cpp $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf $(TARGET)

