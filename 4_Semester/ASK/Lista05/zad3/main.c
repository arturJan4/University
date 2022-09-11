/*
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

uint32_t puzzle3(uint32_t n, uint32_t d);

int main() {

    uint32_t i = 5;
    uint32_t j = 4;
    printf("puzzle(%u,%u) == %u\n", i, j, puzzle3(i,j));
    i = 6; j = 4;
    printf("puzzle(%u,%u) == %u\n", i, j, puzzle3(i,j));
    i = 7; j = 4;
    printf("puzzle(%u,%u) == %u\n", i, j, puzzle3(i,j));
    i = 8; j = 4;
    printf("puzzle(%u,%u) == %u\n", i, j, puzzle3(i,j));
    i = 32; j = 5;
    printf("puzzle(%u,%u) == %u\n", i, j, puzzle3(i,j));
    
    return 0;
}
