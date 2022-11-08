#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <points> <indexes>\n", argv[0]);
    exit(1);
  }

  FILE *points_f = fopen(argv[1], "r");
  assert(points_f != NULL);

  FILE *indexes_f = fopen(argv[2], "r");
  assert(indexes_f != NULL);

  int n_points, d;
  double *points = read_points(points_f, &n_points, &d);
  assert(points != NULL);

  int n_indexes, k;
  int *indexes = read_indexes(indexes_f, &n_indexes, &k);
  assert(points != NULL);

  for (int i = 0; i < n_indexes; i++) {
    for (int j = 0; j < k; j++) {
      int x = indexes[i*k+j];
      if (x < 0 || x >= n_points) {
        printf("Invalid index: %d\n", x);
        exit(1);
      }
    }
  }

  free(points);
  free(indexes);
}
