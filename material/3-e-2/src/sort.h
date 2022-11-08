#ifndef SORT_H
#define SORT_H

#include <stddef.h>

// We need a sorting function that can also accept some auxiliary
// information - sadly, qsort_r is incompatibly defined on macOS and
// Linux.

void hpps_quicksort(void *base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *, void *),
                    void *arg);

#endif
