# Exercises

The main purpose of the following exercises is to give you more experience
with programming in C.  They mostly consist of setting up a working C
development environment (compiler, editor), which you will need today.

For the coding exercises, you should use `make` to build your
programs. To parametrize `make` to build with all the necessary
compiler flags, start by writing down a `Makefile` containing the
following:

```
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -pedantic -g
```

Then when you add a program `foo`, add a rule to `Makefile` as
follows:

```
foo: foo.c
	$(CC) -o foo foo.c $(CFLAGS)
```

**Beware**: the leading whitespace *must* be a single tab character.
Now, to compile `foo`, just run `make foo`. For example:

```
$ make mynameis
```

There are ways to automate parts of this, but we recommend being
explicit until you get a firm grasp on what `make` does.

In the following, we colloquially use "print" as slang for writing to
standard output.

* [Code handout here](src/)
* [Reference solutions here](ref/)

Remember to check the reference solutions once you've written your
own - perhaps they'll show you ways of doing things more concisely.

## Printing in C

Write a C program `mynameis` that prints your name.

## Input arguments in C

Write a C program `repeatme` that given a string as argument, prints
the string twice on separate lines.  (Maybe watch [the video on
reading line
arguments](https://sid.erda.dk/share_redirect/f8RgVGzlET/argv.mp4).)

If the program gets a number of arguments that is different from 1 it
should print "`Wrong number of arguments`".

## Input argument validation

Write a C program `noAs` that given a string as argument, does either
of the following.

  * If the first character of the string is the `char` `A` it
    prints "`No beginning A's are allowed`",

  * otherwise it prints the given string.

Reminder: Consider how strings are formatted in C.

Note: reuse your argument validation from before. You can just as well
learn it from the beginning: _always check your inputs._

## Multiple input formats

Modify the `roll` program from the handout to support `dN` as
a shorthand for `1dN`.  Hint: if one `sscanf()` fails, try another.

## Bits, libraries, and tests in C (A1 warmup)

This exercise is essentially a miniature version of A1.  You will
write a small C library for computing with single bits.  A library is
a set of reusable definitions (types and functions) that can be used
by applications.  To keep things simple, we are ignoring some C
library best practices - we'll rectify that in A2.

Our library consists of a *header file* `bits.h` and a *test program*
`test_bits.c`.  The test program uses the definitions of the header
file and tests their correctness.  Both are part of the [code
handout](src/), but are unfinished.

Use `make test_bits` to compile the test program and, indirectly, the library.

### Finishing the library

We represent a bit as a type `struct bit`:

```C
struct bit {
  bool v;
};
```

#### Implement `bit_from_int`

Where we represent a bit 1 as `true` and 0 as `false`.  Implement a function

```C
struct bit bit_from_int(unsigned int x);
```

that turns an integer 1 into a `true` bit and an integer 0 into a
`false` bit.  Do this by defining a variable

```C
struct bit b;
```

then set `b.v` based on the value of the integer `x`, then return `b`.

#### Implement `bit_to_int`

Implement a function

```
unsigned int bit_to_int(struct bit b);
```

that turns a `struct bit` into a C integer (that is, the inverse of
`bit_from_int`).

#### Implement `bit_print`

Implement a function

```
void bit_print(struct bit b);
```

that prints a `true` bit as 1 and a `false` bit as 0.

#### Implement `bit_not`

Implement a function

```
struct bit bit_not(struct bit a);
```

that given a bit `x` returns a bit `b` that is the logical negation of
`a`.  This can be implemented similarly to `bit_from_int` by declaring
a new variable of type `struct bit` and then returning it.

#### Implement `bit_and`, `bit_or`, `bit_xor`

Implement the functions

```
struct bit bit_and(struct bit a, struct bit b);
struct bit bit_or(struct bit a, struct bit b);
struct bit bit_xor(struct bit a, struct bit b);
```

with the semantics covered in the lectures.

### Writing the test program

For the purpose of this exercise (and A1), a test program is a program
that uses the facilities exposed by a library (here `bits.h`).  When
run, it calls each function in the library, compares the obtained
result with the expected result, and complains loudly if there is a
discrepancy.  Conventionally, if a test program produces no output,
then the test is assumed to have succeeded.  Extend `test_bits.c` to
test all of the functions you added to `bits.h`.

One of the easiest ways to conduct test is to use the `assert` macro
from the standard `<assert.h>` header.  For example, we could test
`bit_from_int` and `bit_to_int` like this:

```C
assert(bit_to_int(bit_from_int(1)) == 1)
```

One downside of using `assert` is that while it will tell you that the
comparison failed, it will not tell you which result was actually
returned.  This is not such a big concern with bits where only two
values are possible, but it might become a problem in A1.  For testing
something like `bit_and`, we can use a function like this:

```C
void test_bit_and(unsigned int x, unsigned int y) {
  unsigned int got = bit_to_int(bit_and(bit_from_int(x), bit_from_int(y)));
  unsigned int expected = x&y;
  if (got != expected) {
    printf("Input:     %u & %u\n", x, y);
    printf("Got:       %u\n", got);
    printf("Expected:  %u\n", expected);
    exit(1);
  }
}
```

Use similar functions for `test_bit_or` and `test_bit_xor`.

## Integer representation

Play the integer representation game linked below. Try to get `0xA`
correct on the different "levels".

http://topps.diku.dk/compsys/integers.html

Next, answer all of the following:

* http://topps.diku.dk/compsys/integers.html#NjdfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#NjFfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MTAzX2ZhbHNlXzFfMl8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MjU1X2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MTUzX2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MjE5X2ZhbHNlXzFfMF8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8wXzE=

## Integer puzzles

Given the following initialization:

```C
int x = foo();
int y = bar();
unsigned ux = x;
unsigned uy = y;
```

Consider whether each of the following statements hold:

* `x < 0` => `((x*2) < 0)`
* `ux >= 0`
* `x & 7 == 7`  => `(x<<30) < 0`
* `ux > -1`
* `x > y`   =>  `-x < -y`
* `x * x >= 0`
* `x > 0 && y > 0`  =>  `x + y > 0`
* `x >= 0`  =>  `-x <= 0`
* `x <= 0`  =>  `-x >= 0`
* `(x|-x)>>31 == -1`
* `ux >> 3 == ux/8`
* `x >> 3 == x/8`
* `x & (x-1) != 0`
