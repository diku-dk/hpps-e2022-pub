#include <stdio.h>

void recurse(int n) {
  printf("&n: %p\n", (void*)&n);
  if (n == 0) {
    return;
  } else {
    recurse(n-1);
  }
}

void fibs(int* array, int n) {
  array[0] = 1;
  array[1] = 1;
  for (int i = 2; i < n; i++) {
    array[i] = array[i-1] + array[i-2];
  }
}

int main() {
  //recurse(100);
  int array[10];
  fibs(array, 10);
  for (int i = 0; i < 10; i++) {
    printf("%d\n", array[i]);
  }
}
