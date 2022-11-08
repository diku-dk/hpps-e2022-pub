#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  assert(f != NULL);

  int n, d;
  double *arr = read_points(f, &n, &d);

  for (int i = 0; i < n; i++) {
    printf("Point %d: ", i);
    for (int j = 0; j < d; j++) {
      printf("%f ", arr[i*d+j]);
    }
    printf("\n");
  }

  free(arr);
}
