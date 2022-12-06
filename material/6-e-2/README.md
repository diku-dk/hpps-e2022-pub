# Lab: concurrent programming with pthreads

This lab contains two directories with source code:

* [src](src/) contains utility code and program skeletons that you
  must finish.  For this lab, you are not required to add new source
  files (or touch the Makefile), but you may do so if you want to
  (experimentation is always encouraged!)

* [ref](ref/) contains my reference solutions.  Feel free to have a
  look, especially if you are stuck, but make sure you understand why
  the programs work before you move on.  These labs are not here to
  test you, but to teach you.

## Parallelising summation

In this task you parallelise a contrived program that sums the numeric
value of all the bytes in a file.  Such a program is mostly limited by
how quickly we can access memory, not by raw compute power, so
parallelisation is not going to provide major speedup, but it's a good
exercise in multithreaded programming.

### Generating random files

The program [mkbytes](src/mkbytes.c) can generate random binary
files of a given size in bytes.  For example, to generate a 16KiB
file:

```
$ ./mkbytes 16384 16384.bytes
```

Or to generate a 1GiB file:

```
$ ./mkbytes 1073741824 1073741824.bytes
```

You can also generate files using any other mechanism, if you wish.

### Sequential implementation

The program [sumbytes-seq](src/sumbytes-seq.c) implements sequential
summation of the bytes in a file.  We run it as follows:

```
$ ./sumbytes-seq 1073741824.bytes
I/O: 0.343138s
Summing: 0.083552s
Result: -538100055
```

The program contains internal instrumentation for measuring how
long it takes to read the file into memory and sum its contents.
These two tasks are measured independently, because parallelisation
will only help speed up the second part, and for this contrived
program, it is actually the file IO that takes most of the time.  The
time measurements are done with a `seconds()` function, as in lab
[3-l-1](../3-l-1).

You should read [the implementation of
sumbytes-seq](src/sumbytes-seq.c) and make sure you understand it,
before moving on.

### Your task: parallelisation!

Your task is to make the summation part of sumbytes faster, by using
multiple threads, but without changing the result.  You will do this
by writing three different multi-threaded implementations.  The first
two will have serious problems, but teach you the basic techniques,
while the third will (hopefully!) be a good implementation.

You are encouraged to use the wrapper functions from the
[csapp.h](src/csapp.h) library for working with threads and
semaphores:

```C
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp,
                    void * (*routine)(void *), void *argp);
void Pthread_join(pthread_t tid, void **thread_return);
void Sem_init(sem_t *sem, int pshared, unsigned int value);
void P(sem_t *sem);
void V(sem_t *sem);
```

#### [`sumbytes-par-2`](src/sumbytes-par-2.c): two threads

This program should launch two threads, each of which sum one half of
the input, and update a shared variable with their partial results.
The main thread waits for the two threads to finish, then reads the
result.  Make sure that your implementation also works on input sizes
that are not divisible by two.

##### Hints

* If you find it difficult to get going, then start by writing a
  sequential program (no threads) that morally does what we want the
  multi-threaded program to do.  That is, use two function calls to
  compute the sum of the first and the last half of the input.

* The `thread_fn` function should take a pointer to a `thread_arg`
  struct as argument.  Add fields to the `thread_arg` struct that you
  believe are necessary.

* Both threads need to eventually update an integer variable
  containing the final sum.  The address of this variable will
  certainly need to be in the `thread_arg` struct.  Use a
  semaphore-based lock to protect it.

* Launch threads with `Pthread_create()` and wait for them to finish
  with `Pthread_join()`.

* This program should run about twice as fast as `sumbytes-par-seq`.
  If it's too slow, then check that you are launching *both* threads
  before joining either of them.

#### [`sumbytes-par-n`](src/sumbytes-par-n.c): one thread per input element

The problem with `sumbytes-par-2` is that it only uses two threads, so
on a machine with *many* threads, most cores will remain idle.  This
program instead *launches one thread per input element*.  Each thread
then reads a single byte from the array, and adds it to a shared
variable.

This implementation will likely be *very slow*, so test it only on
small inputs.

##### Hints

* You will need to use dynamic allocation (`malloc()`) to generate an
  array of `size` `pthread_t` thread handles.

* You will need two separate loops to create and join the threads.

* The `thread_arg` structs will also need to be dynamically allocated.
  Think about who should be responsible for *freeing* them.

#### [`sumbytes-par-chunked`](src/sumbytes-par-chunked.c): constant number of threads

Now we are ready to create a good implementation: one that can take
full advantage of all CPU cores on the system, yet does not create
more threads than strictly necessary.  The idea is to *partition* the
input into *chunks*, and create a thread to process each chunk.  The
number of threads (`num_threads` in the handout) is then a tunable
constant that we can change and see how it affects performance.

The basic structure should be similar to `sumbytes-par-n`, in that we
create `num_threads` threads, and so we must dynamically allocate
space for the `pthread_t` values and the `thread_arg` structs.  The
`thread_arg` structs must contain information about which chunk of the
input the thread is responsible for processing.

##### Hints

* An input of `n` elements can be split into `k` chunks of size
  `(n-k+1)/k` elements each (this is an arithmetic trick for dividing
  *rounding up* with integers).  Note that the last chunk may go beyond
  `n`, which you'll need to detect as a special case.

* Suppose `chunk_size = (size-num_threads+1)/num_threads`, then thread
  `i` should process the chunk starting at offset `i*chunk_size`.

* The `thread_arg` struct should then contain (at least) a pointer to
  the start of the chunk, and the number of elements in the chunk.

## Other tasks

If you manage to finish the above, look at the following exercises
from CSAPP:

* 12.6
* 12.16
* 12.17
