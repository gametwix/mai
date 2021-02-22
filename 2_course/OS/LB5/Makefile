#Вариант 34
CC = gcc
CFLAGS = -c -Wall
ADDLIB = -lm
# Реализация 1 или 2
REALIZE_STATIC_LIB = 2

all: static 

static: main_static.o libfunc.a
	$(CC) main_static.o -o static -L. -lfunc $(ADDLIB)

main_static.o: main_static.c
	$(CC) $(CFLAGS) main_static.c 

libfunc.a: libfunc.o
	ar cr libfunc.a libfunc.o

libfunc.o: functions_$(REALIZE_STATIC_LIB).c
	$(CC) $(CFLAGS) functions_$(REALIZE_STATIC_LIB).c -o libfunc.o 

clean:
	rm -r *.o *.a static
