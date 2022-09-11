/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int puzzle4(long *a, long v, uint64_t s, uint64_t e);

int main() {
    long tab[10] = {1, 3, 4, 6, 9, 12, 14, 15, 16, 20};

    long i = 15;
    printf("index of %ld: %d\n", i, puzzle4(tab, i, 0, 9));
    return 0;
}
