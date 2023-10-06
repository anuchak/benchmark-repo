#include <atomic>
#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>

int main(int args, char** argv) {
  auto counter = 0u;
  auto total_count = atoi(argv[1]);
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  for(auto i = 0u; i < total_count; i++) {
    auto temp = counter;
    while(!__sync_bool_compare_and_swap(&counter, temp, temp+1)) {
      temp = counter;
    }
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto nanos1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu ns | counter: %u\n", nanos1 - nanos, counter);
}
