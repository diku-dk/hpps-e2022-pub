#ifndef UTIL_H
#define UTIL_H

// Return the number of (fractional) seconds since the start of the Unix epoch.
double seconds();

// Read the contents of a file as an array of bytes.  The pointer that
// is returned must eventually be passed to free().  The size is
// returned in an out-parameter.  Returns NULL on any error.
unsigned char* read_file(const char*, long *size);

#endif
