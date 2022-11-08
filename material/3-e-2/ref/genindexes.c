#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char** argv) {
  if (argc != 5) {
    fprintf(stderr, "Usage: %s <points> <n> <k> <indexes>\n", argv[0]);
    exit(1);
  }

  FILE *points_f = fopen(argv[1], "r");
  assert(points_f != NULL);

  FILE *indexes_f = fopen(argv[4], "w");
  assert(indexes_f != NULL);

  int n_points, d;
  double *points = read_points(points_f, &n_points, &d);

  int n = atoi(argv[2]);
  int k = atoi(argv[3]);

  assert(k <= n_points);

  int *indexes = malloc(n * k * sizeof(int));

  srand(time(NULL)); // Seed random number generator.

  for (int i = 0; i < n; i++) {
    int picked = 0;
    while (picked < k) {
      // Randomly select index in [0,n_points-1].
      int point_idx = rand() % n_points;

      int skip = 0;
      // If already used, skip to next iteration of loop.
      for (int j = 0; j < picked; j++) {
        if (indexes[i*k+j] == point_idx) {
          skip = 1;
        }
      }

      if (!skip) {
        indexes[i*k+picked] = point_idx;
        picked++;
      }
    }
  }

  write_indexes(indexes_f, n, k, indexes);

  free(points);
}
