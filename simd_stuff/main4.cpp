#include <iostream>
#include <immintrin.h> // Include Intel Intrinsics header
#include <stdlib.h>
#include <chrono>

void memcpy_simd(const void* src, void* dest, size_t size) {
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
  // Cast the source and destination pointers to the appropriate data types
  const char* src_ptr = static_cast<const char*>(src);
  char* dest_ptr = static_cast<char*>(dest);

  // Iterate over the memory block in 256-bit (32-byte) chunks
  for (size_t i = 0; i < size; i += 32) {
    // Load 256 bits (32 bytes) from source into a SIMD register
    __m256i chunk = _mm256_load_si256(reinterpret_cast<const __m256i*>(src_ptr + i));
    // Store the loaded data to destination
    _mm256_store_si256(reinterpret_cast<__m256i*>(dest_ptr + i), chunk);
  }

  for (size_t i = size - (size % 32); i < size; ++i) {
    dest_ptr[i] = src_ptr[i];
  }

  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto millis1 = std::chrono::duration_cast<std::chrono::nanoseconds>(duration1).count();
  printf("%lu nanoseconds\n", millis1 - millis);
}

int main() {
  uint64_t *src;
  int val = posix_memalign((void **)(&src), 32, 500000 * sizeof(uint64_t));
  for(int i = 0; i < 500000; i++) {
    src[i] = i;
  }
  uint64_t *dst;
  val = posix_memalign((void **)(&dst), 32, 600000 * sizeof(uint64_t));
  memcpy_simd(src, dst, 500000 * sizeof(uint64_t));
  for(int i = 0; i < 25; i++) {
    printf("%lu ", dst[i]);
  }
  printf("\n");
}
