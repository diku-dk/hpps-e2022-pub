# Exercises

Based on exercises by: Michael Kirkedal Thomsen <kirkedal@acm.org>

Consider the following program taken from the slides.

```
/* You might want to use different values for L,M,N when performing benchmarks. */
#define L 10
#define M 10
#define N 10

long sum_array_3d(long a[L][M][N]) {
  long sum = 0;
  int i, j, k;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < L; k++) {
        sum += a[k][i][j];
      }
    }
  }
  return sum;
}
```

There is a good reference for how to use 3d arrays here on
[stackoverflow](https://stackoverflow.com/questions/40845302/passing-three-dimensional-arrays-to-a-function-in-c).

### Locality

Sketch what the structure of a 3D array will be like in the 1D memory
of the computer. What should be the order of the indices be to achieve
spatial locality?

### Performance

Write the above into a C program that you can run. You can base it on
the previous examples.

Test with different ordering of the indices to very verify your
previous result.

Take care to prevent the compiler from completely optimizing away your
computation.
