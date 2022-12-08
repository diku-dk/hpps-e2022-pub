CC=gcc
CFLAGS=-Wall -Wextra -pedantic -fsanitize=address -g

all: test_list

list.o: list.c
	$(CC) -c list.c $(CFLAGS)

test_list.o: test_list.c
	$(CC) -c test_list.c $(CFLAGS)

test_list: list.o test_list.o
	$(CC) list.o test_list.o -o test_list $(CFLAGS)

clean:
	rm -f list.o test_list.o test_list
