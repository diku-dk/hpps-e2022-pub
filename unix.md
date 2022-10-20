# Unix on HPPS

Many of the practical problems will require access to a Unix shell and
common Unix tools.  This page describes how to do so on your own
machines.
## Linux

If you run Linux, then everything you need will be easily available in
your distribution's package manager, or it may even be installed
already. Congratulations!

Here is a conservative list of the software you'll need for this
course:

  * `apt-get` is the general package manager for your
      Debian/Ubuntu. You can use it to install the following packages.
  * [GCC](https://gcc.gnu.org/) and
    [Binutils](https://www.gnu.org/software/binutils/). On
    Debian/Ubuntu you get these with the `build-essential` package. On
    Arch Linux/Antergos this is called base-devel.
  * [GDB](https://www.gnu.org/software/gdb/). In most package managers
    this is called `gdb`.  You can also use
    [LLDB](https://lldb.llvm.org/) if you wish.
  * `make`. The build tool.  You also get this with the `build-essential` package.

Further, the following tools are recommended:

  * [Valgrind](http://www.valgrind.org/) for detecting memory errors
    in C programs.  Available as `valgrind` in most package managers.

## Windows

You will need to use the Windows Subsystem for Linux.  [Click here for
Microsoft's own
instructions](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

After this, follow the Linux instruction given above.

## macOS

macOS is a Unix system, but the necessary tools are not quite as
accessible as on Linux.

### Homebrew

Homebrew is a package manager (similar to `apt` on Linux) that contain
ports of many Unix programs. When you get a new Mac, this should be
the first program to install, as it is the most useful.

* Install Homebrew ([http://brew.sh/](http://brew.sh/))

You can install most things you need through Homebrew.

### Use LLDB instead of GDB

GDB (a C debugger) is tricky to get working on macOS.  Instead, you
should use LLDB (`lldb`), which has equivalent functionality for our
purposes, and almost the same commands.  [See this GDB to LLDB command
map](https://lldb.llvm.org/use/map.html), and note that you likely
need only a small fraction of these commands for HPPS.

### Valgrind

The `valgrind` tool unfortunately does not work on macOS, and we know
of no fix or substitute.  Since this is not a *requirement*, merely a
very useful tool, the most pragmatic workaround is to ensure that each
group has at least one group member with a non-macOS system.
