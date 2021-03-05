CC = g++
CFLAGS = -c -g -Wall

all: main

main: main.o bignum.o
	$(CC) main.o bignum.o -o solution
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
bignum.o: bignum.cpp
	$(CC) $(CFLAGS) bignum.cpp
clean:
	rm -r *.o solution
