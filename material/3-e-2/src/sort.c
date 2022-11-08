#include "sort.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void* idx(void* base, size_t size, int i) {
  return ((unsigned char*)base)+i*size;
}

int partition(void *a, size_t size,
                   int (*compar)(const void *, const void *, void *),
                   void *arg,
                   int p, int r) {
  void *tmp = malloc(size);
  void *pivot = malloc(size);

  // Would be better to pick pivot randomly.
  memcpy(pivot, idx(a, size, p), size);

  int i=p-1;
  int j=r;

  while (1) {
    do { j--; } while (compar(pivot, idx(a, size, j), arg) < 0);
    do { i++; } while (compar(idx(a, size, i), pivot, arg) < 0);
    if (i < j) {
      memcpy(tmp, idx(a, size, i), size);
      memcpy(idx(a, size, i), idx(a, size, j), size);
      memcpy(idx(a, size, j), tmp, size);
    } else {
      free(tmp);
      free(pivot);
      return j+1;
    }
  }
}

static void quicksort(int* a, size_t size,
                      int (*compar)(const void *, const void *, void *),
                      void *arg,
                      int start, int end) {
  if (end-start<2) {
    return;
  }

  int q = partition(a, size, compar, arg, start, end);
  quicksort(a, size, compar, arg, start, q);
  quicksort(a, size, compar, arg, q, end);
}

void hpps_quicksort(void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *, void *),
                    void *arg) {
  quicksort(base, size, compar, arg, 0, nmemb);
}

