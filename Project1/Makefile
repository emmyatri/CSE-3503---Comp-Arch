CC = gcc
CFLAGS = -Wall -g -O2 -I./SDL2/include -I./SDL2_ttf/include -I./SDL2/include/SDL2
LDFLAGS = -L./SDL2/lib -L./SDL2_ttf/lib
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lm

OBJS = bitops.o checkers.o checkers_gui.o main.o
TARGET = checkers.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run