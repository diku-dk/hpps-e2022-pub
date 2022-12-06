#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "csapp.h"

int compute_sum(long size, unsigned char *bytes) {
  int res = 0;
  for (long i = 0; i < size; i++) {
    res += bytes[i];
  }
  return res;
}

struct thread_arg {
  // TODO
  int dummy;
};

void* thread_fn(void *p) {
  // TODO
  assert(0);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <infile>\n", argv[0]);
    exit(1);
  }

  const char *fname = argv[1];

  double file_bef = seconds();
  long size;
  unsigned char *bytes = read_file(fname, &size);
  assert(bytes != NULL);
  double file_aft = seconds();

  printf("I/O: %fs\n", file_aft-file_bef);

  double sum_bef = seconds();
  int sum = 0;
  int num_threads = 8; // Arbitrary - play with this!

  for (int i = 0; i < num_threads; i++) {
    // TODO - launch threads
    assert(0);
  }

  for (int i = 0; i < num_threads; i++) {
    // TODO - join threads
    assert(0);
  }

  double sum_aft = seconds();

  printf("Summing: %fs\n", sum_aft-sum_bef);
  printf("Result: %d\n", sum);

  free(bytes);
}
