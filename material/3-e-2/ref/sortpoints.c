#include "io.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp_points(const double *x, const double *y, int* cp) {
  int c = *cp;

  if (x[c] < y[c]) {
    return -1;
  } else if (x[c] == y[c]) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <points> <c>\n", argv[0]);
    exit(1);
  }

  FILE *points_f = fopen(argv[1], "r");
  assert(points_f != NULL);

  int c = atoi(argv[2]);

  int n_points, d;
  double *points = read_points(points_f, &n_points, &d);
  assert(points != NULL);

  assert(c >= 0 && c < d);

  hpps_quicksort(points, n_points, d*sizeof(double),
                 (int (*)(const void*, const void*, void*))cmp_points,
                 &c);

  for (int i = 0; i < n_points; i++) {
    printf("Point %d: ", i);
    for (int j = 0; j < d; j++) {
      printf("%f ", points[i*d+j]);
    }
    printf("\n");
  }

  free(points);
}
