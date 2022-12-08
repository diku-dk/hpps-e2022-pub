#include <stdio.h>
#include <stdlib.h>

int* fibs(int n) {
  // comment
  int* arr = malloc(sizeof(int)*n);
  arr[0] = 1;
  arr[1] = 1;
  for (int i = 2; i < n; i++) {
    arr[i] = arr[i-1] + arr[i-2];
  }
  return arr;
}
