#include <atomic>
#include <chrono>
#include <cstdio>
#include <emmintrin.h>
#include <vector>

#define arr_size 10000000

int main() {
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  auto new_mem = (u_int64_t *)malloc(arr_size * sizeof(u_int64_t));
  for(auto i = 0u; i < arr_size; i++) {
    new_mem[i]++;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
  printf("%lu ms\n", millis1 - millis);
}
