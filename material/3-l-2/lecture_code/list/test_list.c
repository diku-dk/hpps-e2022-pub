#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int inc2(int x) {
  return x + 2;
}

int main() {
  struct list* l = list_new();
  assert(l != NULL);
  list_insert(l, 1);
  list_insert(l, 2);
  list_insert(l, 3);

  list_map(l, inc2);

  assert(list_remove(l) == 5);
  assert(list_remove(l) == 4);
  assert(list_remove(l) == 3);
  list_insert(l, 4);
  list_free(l);
}
