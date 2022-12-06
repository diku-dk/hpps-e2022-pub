CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -pthread

all: forks

forks: forks.o csapp.o
	$(CC) forks.o csapp.o -o forks $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o forks

