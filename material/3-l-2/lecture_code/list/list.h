struct list;

// Produces a new empty list.  Must eventually be freed with
// list_free().
struct list* list_new();

// Frees the list.
void list_free(struct list* l);

// Prefix new element 'val' to list 'l'.
void list_insert(struct list* l, int val);

// Remove first element in list.  List must be nonempty.
int list_remove(struct list* l);

typedef int (*map_fn)(int);

void list_map(struct list* l, map_fn f);
