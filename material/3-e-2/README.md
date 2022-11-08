# Dynamic memory and data formats

These exercises are intended to familiarise you with the programming
techniques and tools you will need to solve A2.

Even if you do not finish the lab tasks during the lab hours, it may
still be productive to finish the tasks before starting work on the
assignment, as everything here is directly relevant.

* The [`src`](src/) directory contains the code handout.

* The [`ref`](ref/) directory contains our solutions.  It's best to
  look at them only when you have tried yourself first, or are stuck.
  When you do look at them, make sure you understand why they work
  before moving on.

You should consider writing and extending a `Makefile` during your
work, as you will be creating several different files for htis lab.
The code handout contains the start of one that you can extend as
needed.

## Index functions

In this exercise you must rewrite multidimensional array indexes to
flat array indexes for arrays of various shapes.  For each array and
index, provide the flat index for when the array is in row-major order
and in column-major order, respectively.  Also indicate whether the
original index is out-of-bounds, regardless of whether the flat index
is.

* Array size: 10 x 20

  Element index: (5,11)

* Array size: 20 x 10

  Element index: (5,11)

* Array size: 2 x 3 x 4

  Element index: (1,2,3)

### Inverse

Now you must do the opposite of above, and convert *flat* indexes to
the corresponding *nested* index for a given array.  Again, indicate
whether the flat index is out-of-bounds.

* Array size: 10 x 20

  Flat index: 111

* Array size: 2 x 3

  Flat index: 6

* Array size: 2 x 3 x 4

  Flat index: 5

## Reading data files

In these tasks you will be implementing functions for converting
on-disk data to in-memory data.

### Data formats

We will be working with two kinds of data files.

* *Points files* represent sequences of *d*-dimensional points (note
  that we can view a collection of *n* *d*-dimensional points as an
  *n✕d* matrix).  These files are binary and have the following format:

  1. First, a 32-bit integer representing the number of *rows* (that is, *n*).

  2. Second, 32-bit integer representing the number of *columns* (that is, *d*).

  3. Then *n✕d* `double` values, each 8 bytes in size.

  Example files for testing: [`20_5.points`](20_5.points),
  [`10_2.points`](10_2.points).

* *Index files* are much like points files, but instead of containing
  `double` values, they contain 4-byte `int` values, which are
  supposed to be valid 0-based indexes into the points of some other
  points file (but this is not checked by the file format itself).

  Example files for testing: [`10_3.indexes`](10_3.indexes),
  [`5_5.indexes`](5_5.indexes).

### Functions

The header file `io.h` contains function *prototypes* for reading and
writing these data files. Your task is to write a corresponding
implementation in `io.c` for each of the prototypes.

For example, the function

```C
double* read_points(FILE *f, int *n_out, int* d_out);
```

should read (from a file opened with `fopen()`) an *n✕d* matrix whose
elements are double-precision floats, returning a pointer that points
to the raw data.  The size of the matrix must be written to the
variables pointed to by the `n_out` and `d_out` parameters.  If an
error occurs during reading, the function should return `NULL`.

An example of how to use the function (but here without error
checking) is as follows:

```C
FILE *f = fopen("20_5.points", "r");
int n, d;
double *data = read_points(f, &n, &d);
```

You must also implement the `read_indexes()` function.  The data
format for an indexes file (e.g. `10_3.indexes`) is very similar to a
points file, except that the elements are now 4-byte integers instead
of 8-byte `double`s.

#### Hints

A sketch of the intended implementation:

* Call `fread()` to read *n*.

* Call `fread()` again to read *d*.

* Allocate space for *n✕d* `double`s with `malloc()`.

* Use a final `fread()` call to read data into the memory you just
  allocated.

### Testing point reading

Write a program `printpoints.c` that can be run as

```
$ ./printpoints 20_5.points
```

and which will then print a human-readable description of the data
[that looks like this](20_5.points.txt).

#### Hints

* You will need to link `io.o` (which is produced from `io.c` in the
  handed-out `Makefile`) with `printpoints` - just pass it on the
  command line, or (ideally) in the `Makefile` rule you write for
  `printpoints`.

* The data array produced by the `read_points()` function is
  essentially a two-dimensional *n✕d* array in row-major order.  To
  access position *(i,j)* in a *n✕d* array, we use the formula
  *i✕d+j*.

### Testing index reading

Write a program `verifyindexes.c` that can be run as

```
$ ./verifyindexes 20_5.points 10_3.indexes
```

and checks whether all the indexes in the indexes files refer to a
valid point in the points file (in this case each index must be zero
or greater and less than 20).  For example, the above command [should
finish succesfully with no
output](https://www.linuxtopia.org/online_books/programming_books/art_of_unix_programming/ch11s09.html),
while the following command should fail:

```
$ ./verifyindexes 10_2.points 10_3.indexes
Invalid index: 17
```

#### Hints

As with `printpoints.c` above, the array returned by `read_indexes()` is
essentially a two-dimensional array in row-major order.

## Writing data files

In these task you will be implementing functions for converting
in-memory data to on-disk data.  The files you generate here should be
readable by the programs you just implemented.

### Functions

Similarly to above, you need to implement the `write_points()` and
`write_indexes()` functions declared in `io.h`.

For example, the function

```C
int write_points(FILE *f, int32_t n, int32_t d, double *data);
```

should write (to a file opened with `fopen()`) an *n✕d* matrix whose
elements are double-precision floats, given a pointer that points to
the raw data.  The size of the matrix is passed via the `n` and `d`
parameters.  The function should return 0 if the write succeeds, and
otherwise 1.

An example of how to use the function (but here without error
checking) is as follows:

```C
double *data = malloc(n*d*sizeof(double))
// fill data somehow
FILE *points_f = fopen("n_d.points", "w");
write_points(points_f, n, d, data);
```

You must also implement the `write_indexes()` function, which is very
similar.

### Generating random points files

Write a program `genpoints.c` that can be run as

```
$ ./genpoints n d output.points
```

where *n* and *d* are positive integers, which will then generate a
file `output.points` that contains *n* points of *d* dimensions each,
with each coordinate being in the interval *[0,1]*.

#### Hints

* Determine *m* and *n* from `argv`, then use `malloc` to generate an
  array of *n✕m* `double`s.  You can use the `write_points()` function
  defined above to write such an array to disk.

* Use the `rand()` function as follows to generate a random number `x`
  in the interval *0* to *1*:

  ```C
  double x = ((double)rand())/RAND_MAX;
  ```

* To open a file for writing, use `fopen(filename, "w")`.

### Generating random index files (tricky)

Write a program `genindexes.c` that can be run as

```
$ ./genindexes input.points n k indexes output.indexes
```

where `input.inputs` is a valid points file (such as the ones
generated by `genpoints`) and *n* and *k* are positive integers.  This
should write an indexes file to `output.indexes`, containing `n` rows
of `k` indexes each, with the following additional constraints:

1. Each index must be in the interval `[0, num_points-1]`, where
   `num_points` is the number of points in `input.points`.

2. `k` must not be greater `num_points`.

3. Each index set *must not contain duplicates*.

#### Hints

Constraint 3 is tricky to implement, and you may want to skip it if
you find it too difficult - it's not critical.

* You will need to use `read_points()` to determine `num_points` (but
  you do not otherwise need the point data).

* Use *rejection sampling* to construct each index row:

  1. Generate a random index in the interval `[0, num_points-1]`:

     ```C
     int point_idx = rand() % n_points;
     ```

  2. If `point_idx` is equal to a previously picked index for this
     row, try again with a new random number.

  3. Continue until `k` distinct indexes have been produced.

* Use `write_indexes()` to write the final file, similarly to `genpoints`.

## Function pointers

For the following tasks you will make use of an implementation of
[quicksort](https://en.wikipedia.org/wiki/Quicksort) that permits a
programmer-provided comparison function.  The public interface is in
`sort.h` (function `hpps_quicksort()`) and the implementation is in
`sort.c`.

### Sorting points by given dimension

Write a program `sortpoints.c` that can be run as

```
$ ./sortpoints input.points c
```

and which then behaves as `printpoints`, except that the points are
first sorted according to their `c`th dimension.

#### Hints

* Read the function documentation in `sort.h`.

* It may be simpler to start by ignoring `c` and always sorting by
  each point's 0th coordinate.

* When calling `hpps_quicksort`, the element size is
  `d*sizeof(double)`, where `d` is the number of dimensions per point.

### Sorting indexes by points

Write a program `sortindexes.c` that can be run as

```
$ ./sortindexes input.points input.indexes c
```

and which then sorts *within* each index row by comparing the `c`th
coordinate of their corresponding point, then prints the newly sorted
index rows.  The order of the rows themselves is unchanged.  You may
assume that the indexes file is valid with respect to the given points
file (as determined by the `verifyindexes` program).

#### Hints

* You will be sorting arrays of `k` elements, each of size `sizeof(int)`.

* Your comparison function will need multiple pieces of additional
  information:

  1. `c`, the dimension along which to compare.

  2. `d`, the number of dimensions per point.

  3. `points`, the actual points data.

  Define a `struct sort_env` that contains this information, and
  define the comparison function as

  ```C
  int cmp_indexes(const int *ip, const int *jp, struct sort_env* env) {
    ...
  }
  ```
