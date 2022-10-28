#include <stdio.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("Wrong number of arguments");
    return 1;
  } else {
    if (argv[1][0] == 'A') {
      puts("No beginning A's are allowed");
    } else {
      puts(argv[1]);
    }
  }
}
