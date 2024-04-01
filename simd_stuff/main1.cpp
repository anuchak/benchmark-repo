#include "emmintrin.h"
#include <chrono>
#include <iostream>
#include <math.h>
#include <string.h>

void normal(float *a, int N) {
  for (int i = 0; i < N; ++i)
    a[i] = sqrt(a[i]);
}

void sse(float *a, int N) {
  // We assume N % 4 == 0.
  int nb_iters = N / 4;
  __m128 *ptr = (__m128 *)a;

  for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)
    _mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;
  int N = atoi(argv[1]);

  float *a;
  posix_memalign((void **)&a, 16, N * sizeof(float));

  for (int i = 0; i < N; ++i)
    a[i] = 3141592.65358;

  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  normal(a, N);
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu nanoseconds\n", millis1 - millis);
  for (int i = 0; i < N; ++i)
    a[i] = 3141592.65358;
  duration = std::chrono::system_clock::now().time_since_epoch();
  millis =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  sse(a, N);
  duration1 = std::chrono::system_clock::now().time_since_epoch();
  millis1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu nanoseconds\n", millis1 - millis);
}
