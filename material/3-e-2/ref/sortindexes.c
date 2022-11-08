#include "io.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct sort_env {
  int c;
  int d;
  double *points;
};

int cmp_indexes(const int *ip, const int *jp, struct sort_env* env) {
  int i = *ip;
  int j = *jp;
  double *x = &env->points[i*env->d];
  double *y = &env->points[j*env->d];
  int c = env->c;

  if (x[c] < y[c]) {
    return -1;
  } else if (x[c] == y[c]) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <points> <indexes> <c>\n", argv[0]);
    exit(1);
  }

  FILE *points_f = fopen(argv[1], "r");
  assert(points_f != NULL);

  int n_points, d;
  double *points = read_points(points_f, &n_points, &d);
  assert(points != NULL);

  FILE *indexes_f = fopen(argv[2], "r");
  assert(indexes_f != NULL);

  int n_indexes, k;
  int *indexes = read_indexes(indexes_f, &n_indexes, &k);
  assert(indexes != NULL);

  int c = atoi(argv[3]);

  assert(c >= 0 && c < d);

  struct sort_env env;
  env.points = points;
  env.d = d;
  env.c = c;

  for (int i = 0; i < n_indexes; i++) {
    hpps_quicksort(&indexes[i*k], k, sizeof(int),
                   (int (*)(const void*, const void*, void*))cmp_indexes,
                   &env);
    printf("Indexes: ");
    for (int j = 0; j < k; j++) {
      printf("%d ", indexes[i*k+j]);
    }
    printf("\n");
  }

  free(points);
  free(indexes);
}
