CC=g++
LDFLAGS=-lglfw -lGL -lGLEW
CPPFLAGS=-g -Wall -Wextra -pedantic

CPP_FILES=$(wildcard *.cpp)

all: main

main: $(CPP_FILES:.cpp=.o)

clean:
	rm -f main *.o
