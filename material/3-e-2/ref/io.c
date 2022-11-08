#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

double* read_points(FILE *f, int* n_out, int *d_out) {
  int read;
  int32_t n, d;

  read = fread(&n, sizeof(int32_t), 1, f);
  if (read != 1) {
    return NULL;
  }

  read = fread(&d, sizeof(int32_t), 1, f);
  if (read != 1) {
    return NULL;
  }

  double* data = malloc(n*d*sizeof(double));

  read = fread(data, d*sizeof(double), n, f);

  if (read != n) {
    free(data);
    return NULL;
  } else {
    *n_out = n;
    *d_out = d;
    return data;
  }
}

int* read_indexes(FILE *f, int *n_out, int *k_out) {
  int read;
  int32_t n, k;

  read = fread(&n, sizeof(int32_t), 1, f);
  if (read != 1) {
    return NULL;
  }

  read = fread(&k, sizeof(int32_t), 1, f);
  if (read != 1) {
    return NULL;
  }

  int* data = malloc(n*k*sizeof(int));

  read = fread(data, k*sizeof(int), n, f);

  if (read != n) {
    free(data);
    return NULL;
  } else {
    *n_out = n;
    *k_out = k;
    return data;
  }
}


int write_points(FILE *f, int32_t n, int32_t d, double *data) {
  // Write number of points.
  if (fwrite(&n, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write number of values for each point (dimensionality).
  if (fwrite(&d, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write the raw point data.
  if ((int)fwrite(data, d*sizeof(double), n, f) != n) {
    return 1;
  }

  return 0;
}

int write_indexes(FILE *f, int32_t n, int32_t k, int *data) {
  // Write number of points.
  if (fwrite(&n, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write number of indexes for each point.
  if (fwrite(&k, sizeof(int32_t), 1, f) != 1) {
    return 1;
  }

  // Write the raw point data.
  if ((int)fwrite(data, k*sizeof(int), n, f) != n) {
    return 1;
  }

  return 0;
}
