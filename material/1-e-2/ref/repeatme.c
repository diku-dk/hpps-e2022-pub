#include <stdio.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("Wrong number of arguments");
    return 1;
  } else {
    puts(argv[1]);
    puts(argv[1]);
  }
}
