#include <iostream>
#include <inttypes.h>
#include <cstdlib>
#include <cstring>
#include <vector>

bool doMSBFS(uint64_t* seen, uint64_t* visit, uint64_t* visitNext, int* csr_e, int* csr_v) {
  for(auto i = 0; i < 1024; i++) {
    seen[i] |= visit[i];
    visitNext[i] = 0llu;
  }
  bool active = false;
  for(auto i = 0; i < 1024; i++) {
    if(visit[i]) {
      for(auto j = csr_e[i]; j < csr_e[i+1]; j++) {
        uint64_t unseen = visit[i] & ~seen[csr_v[j]];
        if(unseen)
          visitNext[csr_v[j]] |= unseen;
        active |= unseen;
      }
    }
  }
  return active;
}

int main() {
  /// CREATION OF THE GRAPH FOR DOING MS-BFS
  int concurrentBFS = 64;
  int totalNodes = 1024;
  int csr_v[1025], csr_e[2048];
  for(auto i = 0; i < totalNodes; i++) {
    csr_v[i] = i*2;
    csr_e[2*i] = (i+1);
    csr_e[2*i + 1] = (i+2);
  }
  csr_v[totalNodes] = 2*totalNodes;
  for(auto i = 0; i < totalNodes; i++) {
    std::cout << "Neighbours of " << i << ": " << std::endl;
    for(auto j = csr_v[i]; j < csr_v[i+1]; j++) {
      std::cout << csr_e[j] << " ";
    }
    std::cout << std::endl;
  }
  /// START BFS, 512 BFS WILL BE STARTED WITH SOURCES = {0, 1, ... 511}
  /// Total 3 vectors being used - visit, seen, next
  /// (1) visit: the nodes whose neighbours need to be explored
  /// (2) seen: the global vector to track the nodes that have been visited already
  /// (3) next: the next nodes that need to be explored, will be swapped with visit
  uint64_t visit[1024] {0lu}, seen[1024] {0lu}, next[1024] {0lu};
  /// LET'S SAY WE WANT TO LAUNCH 64 CONCURRENT BFS WITH {1,3,5,...127} AS SRC
  for(auto i = 0; i < concurrentBFS; i++) {
    auto srcNode = 2*i + 1;
    visit[srcNode] |= (1llu << i);
  }
  uint64_t *temp, *x = visit, *next_ = next;
  while(doMSBFS(seen, x, next_, csr_e, csr_v)) {
    temp = x;
    x = next_;
    next_ = temp;
    printf("completed 1 level ...");
  }
}
