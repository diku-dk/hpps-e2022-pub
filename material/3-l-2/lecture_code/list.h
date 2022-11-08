struct list;

// Create and return new empty list.
struct list* list_new();

void list_free(struct list*);

void list_insert(struct list*, double x);

// Removes and returns last element of list.
double list_remove(struct list*);
