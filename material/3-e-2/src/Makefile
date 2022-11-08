CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

# When you start adding executable programs, add an 'all' target that
# depends on all those programs, e.g.:
#
# all: genpoints
#
# genpoints: genpoints.c io.o
# 	$(CC) -o genpoints genpoints.c io.o $(CFLAGS)

io.o: io.c
	$(CC) -c io.c $(CFLAGS)

sort.o: sort.c
	$(CC) -c sort.c $(CFLAGS)

clean:
	rm -f *.o

