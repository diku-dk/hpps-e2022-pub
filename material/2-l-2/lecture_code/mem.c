#include <stdio.h>

void inc(int* px) {
  printf("inc: px: %p\n", (void*)px);
  *px = *px + 1;
}

int main() {
  int x = 754;
  printf("x: %d\n", x);
  int* px = &x;
  printf("px: %p\n", (void*)px);
  printf("*px: %d\n", *px);
  *px = 1337;
  printf("px: %p\n", (void*)px);
  printf("x: %d\n", x);
  inc(px);
  printf("x: %d\n", x);
  int** ppx = &px;
  int*** pppx = &ppx;
}
