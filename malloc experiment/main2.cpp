#include <atomic>
#include <chrono>
#include <cstdio>
#include <emmintrin.h>
#include <vector>
#include <string.h>

#define initial_arr_size 1000
#define final_size 10000000

int main() {
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  auto new_mem = new u_int64_t [initial_arr_size];
  auto curr_size = initial_arr_size;
  for(auto i = 0u; i < final_size; i++) {
    if(i < curr_size) {
      new_mem[i]++;
    } else {
      auto new_size = std::min(final_size, curr_size * 8);
      auto mem = new u_int64_t [new_size];
      memcpy(mem, new_mem, sizeof(u_int64_t) * curr_size);
      delete[] new_mem;
      new_mem = mem;
      new_mem[i]++;
      curr_size = new_size;
    }
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
  printf("%lu ms\n", millis1 - millis);
}
