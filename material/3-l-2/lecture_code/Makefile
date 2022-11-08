CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g -fsanitize=address

test_list: list.o test_list.o
	$(CC) list.o test_list.o -o test_list $(CFLAGS)

list.o: list.c list.h
	$(CC) list.c -c $(CFLAGS)

test_list.o: test_list.c
	$(CC) test_list.c -c $(CFLAGS)
