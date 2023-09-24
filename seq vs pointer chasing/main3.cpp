#include <atomic>
#include <chrono>
#include <cstdio>
#include <emmintrin.h>
#include <vector>

struct alignas(64) block_uint32_wrapper {
  u_int32_t *values;
  block_uint32_wrapper* next;

  block_uint32_wrapper(block_uint32_wrapper* next_) {
    values = new u_int32_t[14];
    next = next_;
  }
};

int main() {
  block_uint32_wrapper* start = new block_uint32_wrapper(nullptr);
  block_uint32_wrapper* end = new block_uint32_wrapper(nullptr);
  for(auto i = 0u; i < 14; i++) {
    start->values[i] = i;
  }
  for(auto i = 0u; i < 2; i++) {
    end->values[i] = (i + 99999998);
  }
  auto temp = start;
  for(auto i = 1u; i < 7142857; i++) {
    temp->next = new block_uint32_wrapper(nullptr);
    for(auto j = 0; j < 14; j++) {
      temp->next->values[j] = i*14 + j;
    }
    temp = temp->next;
  }
  temp->next = end;
  // do a flush of the objects from cache before starting the experiment
  block_uint32_wrapper *a = start, *b = start->next;
  while(a) {
    _mm_clflush(a);
    a = b;
    if(b)
      b = b->next;
  }
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  auto temp1 = start;
  while(temp1) {
    for(auto i = 0u; i < 14; i++) {
      temp1->values[i]++;
    }
    temp1 = temp1->next;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
  printf("%lu ms | %u \n", millis1 - millis, end->values[1]);
}
