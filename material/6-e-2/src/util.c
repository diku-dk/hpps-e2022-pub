#include "util.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

double seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL); // The null is for timezone information.
  return tv.tv_sec + tv.tv_usec/1000000.0;
}


// Return the size of the given open file, which must be seekable
// (meaning that it's an ordinary file opened with fopen() - you can't
// pass stdin to this).  Also, this must be called just after opening
// the file, as it resets the read position to the initial spot in the
// file.
long file_size(FILE* f) {
  fseek(f, 0, SEEK_END); // Seek to end of file.
  long size = ftell(f); // At which offset is that?
  fseek(f, 0, SEEK_SET); // Now back to the start of the file.
  return size;
}

unsigned char* read_file(const char* fname, long *size) {
  FILE *in = fopen(fname, "r");

  if (in == NULL) {
    return NULL;
  }

  *size = file_size(in);

  unsigned char *bytes = malloc(*size);

  int read = fread(bytes, sizeof(unsigned char), *size, in);

  fclose(in);

  if (read != *size) {
    free(bytes);
    return NULL;
  } else {
    return bytes;
  }
}
