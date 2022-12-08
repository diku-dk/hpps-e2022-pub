#include "fibs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
  int* arr = fibs(10);
  assert(arr[0] == 1);
  assert(arr[1] == 1);
  assert(arr[2] == 2);
  free(arr);
}

