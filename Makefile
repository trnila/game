CC=g++
LDFLAGS=-lglfw -lGL -lGLEW
CPPFLAGS=-g

all: main

main: main.o Shader.o Program.o

clean:
	rm -f main *.o
