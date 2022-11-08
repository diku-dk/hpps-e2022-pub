#include "list.h"
#include <stdlib.h>

struct list {
  int n;
  int capacity;
  double *values;
};

struct list* list_new() {
  struct list *l = malloc(sizeof(struct list));
  l->n = 0;
  l->capacity = 10;
  l->values = malloc(l->capacity*sizeof(double));
  return l;
}

void list_free(struct list *l) {
  free(l->values);
  free(l);
}

void list_insert(struct list* l, double x) {
  if (l->n == l->capacity) {
    l->capacity *= 2;
    l->values = realloc(l->values, l->capacity * sizeof(double));
  }
  l->values[l->n] = x;
  l->n++;
}

double list_remove(struct list* l) {
  double x = l->values[l->n-1];
  l->n--;
  return x;
}
