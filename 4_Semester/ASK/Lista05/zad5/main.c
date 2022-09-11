/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

long switch_prob(long x, long n);

int main() {
    long x = 5;
    long n = 60;
    printf("prob of n=%ld with x=%ld: %ld\n", n, x, switch_prob(x, n));
    return 0;
}
