# Using OpenMP on macOS

If you try to compile a C program with `gcc -fopenmp` on macOS, you might
get the following error:

```
clang: error: unsupported option '-fopenmp'
```

This is because the `gcc` command on macOS actually runs
[`clang`](https://clang.llvm.org/), a different C compiler, and for
some reason Apple has disabled OpenMP support.  The best way to solve
this problem is to install a proper version of GCC.

* First, [install the Homebrew package manager as discussed
  here](../../unix.md#homebrew).

* Then run `brew install gcc` to install GCC.

This will not change the default `gcc` command.  We don't recommend
you change it, since other Mac software might expect the default to be
in place.  You can use the command `gcc-10` to run the installed
version of GCC (10 as of this writing, maybe it will be `gcc-11` when
you read this in the cool sci-fi future).  That is, to compile a
program, run:

```
$ gcc-10 foo.c -o foo -fopenmp
```

In the Makefiles for the code handout, you should change the
definition of `CC` to be `gcc-10` instead of `gcc` (*now* do you see
the value of defining variables for this?).

## If the above doesn't work

Make sure the X-code command line tools are installed:

```
$ xcode-select --install
```

Then prefix every build command with `xcrun`, e.g.:

```
$ xcrun make
$ xcrun xcode-select --install
```

To compile with `xcrun` + `gcc-10` you can use:

```
$ export CC=gcc-10 
$ xcrun make
```
