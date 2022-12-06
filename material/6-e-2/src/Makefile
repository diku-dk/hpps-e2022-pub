CC=gcc
CFLAGS=-Wall -Wextra -pedantic -pthread -O3
EXECUTABLES=mkbytes sumbytes-seq sumbytes-par-2 sumbytes-par-n sumbytes-par-chunked

all: $(EXECUTABLES)

mkbytes: mkbytes.o
	$(CC) -o $@ $^ $(CFLAGS)

sumbytes-seq: sumbytes-seq.o util.o
	$(CC) -o $@ $^ $(CFLAGS)

sumbytes-par-2: sumbytes-par-2.o util.o csapp.o
	$(CC) -o $@ $^ $(CFLAGS)

sumbytes-par-n: sumbytes-par-n.o util.o csapp.o
	$(CC) -o $@ $^ $(CFLAGS)

sumbytes-par-chunked: sumbytes-par-chunked.o util.o csapp.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o $(EXECUTABLES)
