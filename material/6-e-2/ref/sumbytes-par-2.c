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

  pthread_t tid1, tid2;
  struct thread_arg arg1, arg2;

  arg1.bytes = bytes;
  arg1.n = size/2;
  arg1.sum_p = &sum;
  arg1.sum_mutex = &sum_mutex;

  arg2.bytes = bytes+size/2;
  arg2.n = size-size/2;
  arg2.sum_p = &sum;
  arg2.sum_mutex = &sum_mutex;

  Pthread_create(&tid1, NULL, thread_fn, &arg1);
  Pthread_create(&tid2, NULL, thread_fn, &arg2);

  Pthread_join(tid1, NULL);
  Pthread_join(tid2, NULL);

  double sum_aft = seconds();

  printf("Summing: %fs\n", sum_aft-sum_bef);
  printf("Result: %d\n", sum);

  free(bytes);
}
