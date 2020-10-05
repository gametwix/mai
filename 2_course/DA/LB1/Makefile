CC=g++

CFLAGS=--std=c++14 -c -g

all: lb1

lb1: main.o 
	$(CC) main.o -o solution
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
clean:
	rm -rf *.o solution
