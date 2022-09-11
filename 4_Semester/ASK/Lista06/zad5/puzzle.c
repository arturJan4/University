#include <alloca.h>

long aframe(long n, long idx, long *q) {
    long i;
    long **p = alloca(n * sizeof(long *));
    p[n-1] = &i;
    for (i = 0; i < n; i++)
        p[i] = q;
    return *p[idx];
}