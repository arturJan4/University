/*
 * Matrix transposition with and without blocking.
 *
 * Intel® Core™ i5-6600 CPU @ 3.30GHz
 *
 * $ ./transpose -n 32768 -v 0
 * Time elapsed: 21.528841 seconds.
 * $ ./transpose -n 32768 -v 1
 * Time elapsed: 5.251710 seconds.
 */
#include "transpose.h"

void transpose0(T *dst, T *src, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      dst[j * n + i] = src[i * n + j];
}

void transpose1(T *dst, T *src, int n) {
  for (int i = 0; i < n; i += BLOCK)
    for (int j = 0; j < n; j += BLOCK)         // main.c::33 -> (n % BLOCK == 0)
      for(int i1 = i; i1 < i + BLOCK; ++i1)    // analogicznie do matmult
        for(int j1 = j; j1 < j + BLOCK; ++j1)  
          dst[j1 * n + i1] = src[i1 * n + j1];
}

