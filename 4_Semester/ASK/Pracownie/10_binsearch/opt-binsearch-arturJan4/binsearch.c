/*
 * Binary search with linearly placed tree levels.
 *
 * Intel® Core™ i5-6600 CPU @ 3.30GHz
 *
 * $ ./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 0
 * Time elapsed: 7.616777 seconds.
 * $ ./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 1
 * Time elapsed: 2.884369 seconds.
 */
#include "binsearch.h"

bool binsearch0(T *arr, long size, T x) {
  do {
    size >>= 1;
    T y = arr[size];
    if (y == x)
      return true;
    if (y < x)
      arr += size + 1;
  } while (size > 0);
  return false;
}

// every level of BST at own [2^n - 1, 2^(n+1) - 1] range
// similiar to heap implementation
// (2 * n + 1 - left child), (2 * n + 2 - right child)
void linearize(T *dst, T *src, long size) {
  long distance = size + 1;
  long howMany = 1;
  long counter = 0;
  long index = size >> 1;

  while(counter < size) {
    for(int i = 0; i < howMany; ++i, ++counter) {
      dst[counter] = src[index + i * distance];
    } 
    howMany <<= 1;
    distance >>= 1;
    index >>= 1;
  }
}

bool binsearch1(T *arr, long size, T x) {
  long iter = 0;
  while(iter < size) {
    T y = arr[iter];
    //__builtin_prefetch(&arr[(iter << 1) + 1], 0, 3);
    //__builtin_prefetch(&arr[(iter << 1) + 2], 0, 3);
    //__builtin_prefetch(&arr[(iter << 2) + 3], 0, 3);
    //__builtin_prefetch(&arr[(iter << 2) + 4], 0, 3);
    //__builtin_prefetch(&arr[(iter << 2) + 5], 0, 3);
    //__builtin_prefetch(&arr[(iter << 2) + 6], 0, 3);

    if(x == y)
      return true;
    
    iter <<= 1;
    iter += 1 + (y < x);
  }

  return false;
}
