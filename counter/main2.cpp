#include <atomic>
#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>

int main(int args, char** argv) {
  std::atomic<uint64_t> counter{0u};
  auto total_count = atoi(argv[1]);
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  for(auto i = 0u; i < total_count; i++) {
    counter++;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto nanos1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu ns | counter: %lu\n", nanos1 - nanos, counter.load());
}
