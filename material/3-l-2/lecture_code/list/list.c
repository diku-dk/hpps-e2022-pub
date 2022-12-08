#include "list.h"
#include <stdlib.h>
#include <assert.h>

struct node {
  int val;
  struct node* tail; // NULL if no next element;
};

struct list {
  struct node* head; // NULL if empty.
};

struct list* list_new() {
  struct list* l = malloc(sizeof(struct list));
  l->head = NULL;
  return l;
}

void list_free(struct list* l) {
  while (l->head != NULL) {
    list_remove(l);
  }
  free(l);
}

void list_insert(struct list* l, int val) {
  struct node *node = malloc(sizeof(struct node));
  node->val = val;
  node->tail = l->head;
  l->head = node;
}

int list_remove(struct list* l) {
  assert(l->head != NULL);
  int val = l->head->val;
  struct node* new_head = l->head->tail;
  free(l->head);
  l->head = new_head;
  return val;
}

void list_map(struct list* l, map_fn f) {
  struct node *cur = l->head;
  while (cur != NULL) {
    cur->val = f(cur->val);
    cur = cur->tail;
  }
}
