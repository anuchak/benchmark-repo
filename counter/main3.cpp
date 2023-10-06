#include <atomic>
#include <chrono>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <shared_mutex>

int main(int args, char** argv) {
  auto counter = 0u;
  std::shared_mutex mutex;
  auto total_count = atoi(argv[1]);
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  for(auto i = 0u; i < total_count; i++) {
    mutex.lock();
    counter++;
    mutex.unlock();
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto nanos1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu ns | counter: %u\n", nanos1 - nanos, counter);
}
