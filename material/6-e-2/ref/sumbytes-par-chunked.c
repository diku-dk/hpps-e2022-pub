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
  unsigned char *bytes;
  long n;
  int *sum_p;
  sem_t *sum_mutex;
};

void* thread_fn(void *p) {
  struct thread_arg *arg = (struct thread_arg*)p;

  int local_sum = compute_sum(arg->n, arg->bytes);

  P(arg->sum_mutex);
  *arg->sum_p = *arg->sum_p + local_sum;
  V(arg->sum_mutex);
  free(arg);

  return NULL;
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
  sem_t sum_mutex;
  Sem_init(&sum_mutex, 0, 1);

  int num_threads = 16;
  pthread_t tids[num_threads];
  int chunk_size = (size + num_threads - 1)/num_threads;

  for (int i = 0; i < num_threads; i++) {
    struct thread_arg *arg = malloc(sizeof(struct thread_arg));
    arg->bytes = &bytes[i*chunk_size];
    if (size - i*chunk_size < chunk_size) {
      arg->n = size - i*chunk_size;
    } else {
      arg->n = chunk_size;
    }
    arg->sum_p = &sum;
    arg->sum_mutex = &sum_mutex;
    Pthread_create(&tids[i], NULL, thread_fn, arg);
  }

  for (int i = 0; i < num_threads; i++) {
    Pthread_join(tids[i], NULL);
  }

  double sum_aft = seconds();

  printf("Summing: %fs\n", sum_aft-sum_bef);
  printf("Result: %d\n", sum);

  free(bytes);
}
