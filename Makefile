CC=g++
LDFLAGS=-lglfw -lGL -lGLEW -lassimp
CPPFLAGS=-g -Wall -Wextra -pedantic

CPP_FILES=$(shell find src -name "*.cpp")

all: main

main: $(CPP_FILES:.cpp=.o)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f main
	find src -name "*.o" -delete
