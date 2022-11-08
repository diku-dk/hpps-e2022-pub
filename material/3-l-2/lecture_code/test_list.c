#include "list.h"
#include <stdio.h>
#include <assert.h>

int main() {
  struct list *l = list_new();
  list_insert(l, 1);
  list_insert(l, 2);
  assert(list_remove(l) == 2);

  for (int i = 0; i < 100; i++) {
    list_insert(l, 3);
  }

  list_free(l);
}
