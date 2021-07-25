/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int puzzle(long x, unsigned n);

int main() {
    // 15 4
    // 15 3
    // 16 5
    // 16 4
    long x = 16;
    unsigned n = 4; 

    printf("count of x=%ld, n=%u: %d\n", x, n, puzzle(x, n));
    return 0;
}
