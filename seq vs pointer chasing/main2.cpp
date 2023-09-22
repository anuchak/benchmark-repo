#include <atomic>
#include <chrono>
#include <cstdio>
#include <emmintrin.h>
#include <vector>

#define cacheline_size 64

struct uint32_wrapper {
  uint32_t val;
  uint32_wrapper* next;

  uint32_wrapper(uint32_t val_, uint32_wrapper* next_) {
    val = val_;
    next = next_;
  }
};

int main() {
  uint32_wrapper *start = new uint32_wrapper(0u, nullptr);
  uint32_wrapper *end = new uint32_wrapper(99999999, nullptr);
  uint32_wrapper *temp = start;
  for (auto i = 1u; i < 99999999; i++) {
    temp->next = new uint32_wrapper(i, nullptr);
    temp = temp->next;
  }
  temp->next = end;
  // do a flush of the objects from cache before starting the experiment
  uint32_wrapper *a = start, *b = start->next;
  while(a) {
    _mm_clflush(a);
    a = b;
    if(b)
      b = b->next;
  }
  auto temp1 = start;
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  for (auto i = 0u; i < 100000000; i++) {
    temp1->val++;
    temp1 = temp1->next;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
  printf("%lu ms | %u\n", millis1 - millis, end->val);
}
