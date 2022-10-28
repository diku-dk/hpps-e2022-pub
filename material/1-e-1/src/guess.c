#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  int x = rand() % 100;

  printf("OK, I am thinking of a number in the range [0,99] - see if you can guess it!\n");
  printf("Type a number and press enter to make a guess.\n");

  int guess;

  while (scanf("%d", &guess) == 1) {
    if (guess < x) {
      printf("Too low!\n");
    } else if (guess > x) {
      printf("Too high!\n");
    } else {
      printf("You got it!  I was thinking of %d!\n", x);
      exit(0);
    }
  }
}
