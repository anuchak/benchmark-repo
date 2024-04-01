#include "immintrin.h"
#include <chrono>
#include <iostream>
#include <math.h>
#include <string.h>

void normal(float *a, int N) {
  for (int i = 0; i < N; ++i)
    a[i] = sqrt(a[i]);
}

void avx512(float *a, int N) {
  // We assume N % 4 == 0.
  int nb_iters = N / 16;
  __m512 *ptr = (__m512 *)a;

  for (int i = 0; i < nb_iters; ++i, ++ptr, a += 16)
    _mm512_store_ps(a, _mm512_sqrt_ps(*ptr));
}

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;
  int N = atoi(argv[1]);

  float *a;
  posix_memalign((void **)&a, 64, N * sizeof(float));

  for (int i = 0; i < N; ++i)
    a[i] = 3141592.65358;

  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  normal(a, N);
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu nanosec | ", millis1 - millis);
  for (int i = 0; i < N; ++i)
    a[i] = 3141592.65358;
  duration = std::chrono::system_clock::now().time_since_epoch();
  millis =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  avx512(a, N);
  duration1 = std::chrono::system_clock::now().time_since_epoch();
  millis1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu nanosec\n", millis1 - millis);
}
