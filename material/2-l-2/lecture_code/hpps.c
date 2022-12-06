#include <stdio.h>
#include <assert.h>

int main() {
  FILE *f = fopen("output", "w");
  assert(f != NULL);

  int x = 0x12345678;
  assert(fwrite(&x, sizeof(int), 1, f) == 1);

  fclose(f);
}
