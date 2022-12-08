CC=gcc
CFLAGS=-pedantic -Wall -Wextra

all: test_fibs

fibs.o: fibs.c
	$(CC) -c fibs.c $(CFLAGS)

test_fibs.o: test_fibs.c
	$(CC) -c test_fibs.c $(CFLAGS)

test_fibs: fibs.o test_fibs.o
	$(CC) fibs.o test_fibs.o -o test_fibs

clean:
	rm -f test_fibs test_fibs.o fibs.o
