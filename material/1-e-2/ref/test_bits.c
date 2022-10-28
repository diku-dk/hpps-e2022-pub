#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bits.h"

void test_bit_and(unsigned int x, unsigned int y) {
  unsigned int got = bit_to_int(bit_and(bit_from_int(x), bit_from_int(y)));
  unsigned int expected = x&y;
  if (got != expected) {
    printf("Input:     %u & %u\n", x, y);
    printf("Got:       %u\n", got);
    printf("Expected:  %u\n", expected);
    exit(1);
  }
}

void test_bit_or(unsigned int x, unsigned int y) {
  unsigned int got = bit_to_int(bit_or(bit_from_int(x), bit_from_int(y)));
  unsigned int expected = x|y;
  if (got != expected) {
    printf("Input:     %u | %u\n", x, y);
    printf("Got:       %u\n", got);
    printf("Expected:  %u\n", expected);
    exit(1);
  }
}

void test_bit_xor(unsigned int x, unsigned int y) {
  unsigned int got = bit_to_int(bit_xor(bit_from_int(x), bit_from_int(y)));
  unsigned int expected = x^y;
  if (got != expected) {
    printf("Input:     %u ^ %u\n", x, y);
    printf("Got:       %u\n", got);
    printf("Expected:  %u\n", expected);
    exit(1);
  }
}

int main() {
  assert(bit_to_int(bit_not(bit_from_int(1))) == 0);
  assert(bit_to_int(bit_not(bit_from_int(0))) == 1);

  test_bit_and(1,1);
  test_bit_and(1,0);
  test_bit_and(0,1);
  test_bit_and(0,0);

  test_bit_or(1,1);
  test_bit_or(1,0);
  test_bit_or(0,1);
  test_bit_or(0,0);

  test_bit_xor(1,1);
  test_bit_xor(1,0);
  test_bit_xor(0,1);
  test_bit_xor(0,0);
}
