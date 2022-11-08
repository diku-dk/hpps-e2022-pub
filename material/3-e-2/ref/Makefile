CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

all: printpoints verifyindexes genpoints genindexes sortpoints sortindexes readpoints

printpoints: printpoints.c io.o
	$(CC) -o printpoints printpoints.c io.o $(CFLAGS)

verifyindexes: verifyindexes.c io.o
	$(CC) -o verifyindexes verifyindexes.c io.o $(CFLAGS)

genpoints: genpoints.c io.o
	$(CC) -o genpoints genpoints.c io.o $(CFLAGS)

genindexes: genindexes.c io.o
	$(CC) -o genindexes genindexes.c io.o $(CFLAGS)

sortpoints: sortpoints.c io.o sort.o
	$(CC) -o sortpoints sortpoints.c io.o sort.o $(CFLAGS)

sortindexes: sortindexes.c io.o sort.o
	$(CC) -o sortindexes sortindexes.c io.o sort.o $(CFLAGS)

readpoints: readpoints.c io.o sort.o
	$(CC) -o readpoints readpoints.c io.o sort.o $(CFLAGS)

io.o: io.c
	$(CC) -c io.c $(CFLAGS)

sort.o: sort.c
	$(CC) -c sort.c $(CFLAGS)

clean:
	rm -f *.o printpoints verifyindexes genpoints genindexes sortpoints sortindexes
