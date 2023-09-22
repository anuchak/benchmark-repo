## Experiment Description and Results

This is an experiment to determine how much is the estimated cost and overhead
of doing a sequential scan of an array of elements compared to pointer chasing
of same no. of elements using a *next pointer.  
A variation of this is also considered - blocks of size 64 bytes and then a 
*next pointer to the next block. This is done to ensure that a certain no. of
elements fit into a cache line when fetched by the CPU.  


## Results

| Run | Sequential Scan (ms) | Pointer Chasing (ms) | Block based Pointer Chasing (ms) |
|-----|----------------------|----------------------|----------------------------------|
| 1   | 46                   | 374                  |                                  |
| 2   | 46                   | 381                  |                                  |
| 3   | 45                   | 373                  |                                  |
| 4   | 47                   | 371                  |                                  |
| 5   | 46                   | 373                  |                                  |
| 6   | 45                   | 374                  |                                  |
| 7   | 46                   | 428                  |                                  |
| 8   | 45                   | 372                  |                                  |
| 9   | 46                   | 400                  |                                  |
| 10  | 46                   | 387                  |                                  |


## Discussion

 


