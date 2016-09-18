CC=g++
LDFLAGS=-lglfw -lGL

main: main.o

clean:
	rm -f main *.o
