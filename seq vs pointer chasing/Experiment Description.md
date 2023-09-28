## Experiment Description and Results

This is an experiment to determine how much is the estimated cost and overhead
of doing a sequential scan of an array of elements compared to pointer chasing
of same no. of elements using a *next pointer.  
A variation of this is also considered - blocks of size 64 bytes and then a 
*next pointer to the next block. This is done to ensure that a certain no. of
elements fit into a cache line when fetched by the CPU.  


## Results

| Run | Sequential Scan <br/>[not vectorized] (ms) | Sequential Scan <br/>[vectorized] (ms) | Pointer Chasing <br/>[vectorize / not vectorize same] (ms) | Block Pointer Chasing <br/>[not vectorized] (ms) | Block Pointer Chasing <br/>[vectorized] (ms) |
|-----|--------------------------------------------|----------------------------------------|------------------------------------------------------------|--------------------------------------------------|----------------------------------------------|
| 1   | 173                                        | 42                                     | 374                                                        | 210                                              | 176                                          |
| 2   | 171                                        | 42                                     | 381                                                        | 212                                              | 175                                          |
| 3   | 168                                        | 43                                     | 373                                                        | 213                                              | 178                                          |
| 4   | 169                                        | 44                                     | 371                                                        | 225                                              | 180                                          |
| 5   | 167                                        | 42                                     | 373                                                        | 211                                              | 178                                          |
| 6   | 168                                        | 42                                     | 374                                                        | 217                                              | 176                                          |
| 7   | 168                                        | 42                                     | 428                                                        | 207                                              | 182                                          |
| 8   | 168                                        | 42                                     | 372                                                        | 245                                              | 202                                          |
| 9   | 167                                        | 43                                     | 400                                                        | 243                                              | 185                                          |
| 10  | 168                                        | 42                                     | 387                                                        | 233                                              | 173                                          |


## Discussion

SIMD is king. For sequential scan there is heavy vectorization happening which completely gets missed if you
do pointer chasing operation. Even for block based pointer chasing where each block had 14 elements there was
vectorization happening in the inner loop which slightly improves the performance.
There is also probably CPU data prefetching happening when sequential scan takes place though I don't know a way
to exactly verify this at runtime. 
Increasing the block array size and how much closer we can get to sequential scan operation can be checked later.


