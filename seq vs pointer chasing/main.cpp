#include <atomic>
#include <chrono>
#include <cstdio>
#include <emmintrin.h>
#include <vector>

#define cacheline_size 64

int main() {
  auto arr = new uint32_t[100000000];
  for (auto i = 0u; i < 100000000; i++) {
    arr[i] = i;
  }
  // do a flush of this array from cache before starting the experiment
  // total 100,000,000 elements, size in bytes: 400,000,000 bytes
  // total cache lines = (400,000,000 / 64) = 6,250,000
  for (auto i = 0u; i < (100000000 * sizeof(u_int32_t)) / cacheline_size; i++) {
    _mm_clflush((char *)arr + i * cacheline_size);
  }
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  for (auto i = 0u; i < 100000000; i++) {
    arr[i]++;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
  printf("%lu ms\n", millis1 - millis);
}
