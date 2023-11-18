#include <math.h>
#include <string.h>
#include <chrono>
#include <iostream>
#include <vector>

enum VisitedState : uint8_t {
  NOT_VISITED_DST = 0x1,
  VISITED_DST = 0x2,
  NOT_VISITED = 0x3,
  VISITED = 0x4,
  VISITED_NEW = 0x5,
  VISITED_DST_NEW = 0x6,
};

int main(int argc, char** argv)
{
  if (argc != 3)
    return -1;
  int N = atoi(argv[1]);
  int destinations = atoi(argv[2]);
  auto vec = std::vector<uint8_t>(N+1);
  auto desVec = std::vector<uint64_t>(destinations);
  for(auto i = 0u; i < destinations; i++) {
    desVec[i] = rand() % (N+1);
  }
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  std::fill(vec.begin(), vec.end(), NOT_VISITED);
  for(auto i = 0; i < destinations; i++) {
    vec[desVec[i]] = NOT_VISITED_DST;
  }
  auto duration1 = std::chrono::system_clock::now().time_since_epoch();
  auto micros1 = std::chrono::duration_cast<std::chrono::microseconds>(duration1).count();
  printf("%lu us\n", micros1 - micros);
}
