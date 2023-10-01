## Experiment Description and Results

1) Asking for all the memory at once
2) Growing the size as required

What is the performance difference between 1) and 2) ? And is there a rate of expansion such that 2)
is comparable in speed to 1) ?

A 10,000,000 and 100,000,000 size array are considered. _main.cpp_ does the full allocation at once.  
_main2.cpp_ does the allocation in multiples of x2, x4 and x8.

## Results

10,000,000 size array, initial size of array 1000 (except for full allocation case) -

| Run | Full allocation | Multiple  allocs (x2) | Multiple allocs (x4) | Multiple allocs (x8) |
|-----|-----------------|-----------------------|----------------------|----------------------|
| 1   | 44ms            | 76ms                  | 47ms                 | 45ms                 |
| 2   | 32ms            | 62ms                  | 34ms                 | 34ms                 |
| 3   | 30ms            | 61ms                  | 34ms                 | 31ms                 |
| 4   | 32ms            | 61ms                  | 34ms                 | 33ms                 |
| 5   | 30ms            | 61ms                  | 34ms                 | 33ms                 |
| 6   | 31ms            | 59ms                  | 34ms                 | 33ms                 |
| 7   | 30ms            | 60ms                  | 34ms                 | 32ms                 |
| 8   | 30ms            | 61ms                  | 35ms                 | 34ms                 |
| 9   | 30ms            | 60ms                  | 34ms                 | 33ms                 |
| 10  | 31ms            | 61ms                  | 35ms                 | 32ms                 |

100,000,000 size array, initial size of array 1000 (except for full allocation case) -

| Run | Full allocation | Multiple  allocs (x2) | Multiple allocs (x4) | Multiple allocs (x8) | Multiple allocs (x16) |
|-----|-----------------|-----------------------|----------------------|----------------------|-----------------------|
| 1   | 301ms           | 535ms                 | 421ms                | 306ms                | 377ms                 |
| 2   | 295ms           | 525ms                 | 414ms                | 295ms                | 369ms                 |
| 3   | 296ms           | 529ms                 | 416ms                | 297ms                | 371ms                 |
| 4   | 299ms           | 532ms                 | 415ms                | 294ms                | 371ms                 |
| 5   | 295ms           | 526ms                 | 415ms                | 294ms                | 370ms                 |
| 6   | 299ms           | 531ms                 | 417ms                | 295ms                | 368ms                 |
| 7   | 298ms           | 527ms                 | 414ms                | 295ms                | 369ms                 |
| 8   | 299ms           | 527ms                 | 416ms                | 294ms                | 371ms                 |
| 9   | 295ms           | 535ms                 | 414ms                | 295ms                | 366ms                 |
| 10  | 297ms           | 545ms                 | 415ms                | 289ms                | 369ms                 |

| Run | Multiple  allocs (x32) | Multiple  allocs (x64) | Multiple  allocs (x128) |
|-----|------------------------|------------------------|-------------------------|
| 1   | 289ms                  | 226ms                  | 257ms                   |
| 2   | 284ms                  | 214ms                  | 241ms                   |
| 3   | 282ms                  | 217ms                  | 245ms                   |
| 4   | 287ms                  | 215ms                  | 246ms                   |
| 5   | 286ms                  | 215ms                  | 246ms                   |
| 6   | 283ms                  | 215ms                  | 244ms                   |
| 7   | 285ms                  | 222ms                  | 245ms                   |
| 8   | 285ms                  | 216ms                  | 251ms                   |
| 9   | 285ms                  | 219ms                  | 245ms                   |
| 10  | 286ms                  | 222ms                  | 254ms                   |

## Discussion

For the 100,000,000 size case, why does expansion at the rate of x64 and x128 give better performance for some reason
compared to full allocation case ? The 10,000,000 case also displayed something similar where x128 was doing better
compared to full allocation initially. This is a bit strange and did not understand why this is happening.

