#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <N> <outfile>\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  const char *fname = argv[2];

  FILE *out = fopen(fname, "w");
  assert(out != NULL);

  for (int i = 0; i < n; i++) {
    unsigned char x = rand();
    fwrite(&x, sizeof(x), 1, out);
  }

  fclose(out);
}
